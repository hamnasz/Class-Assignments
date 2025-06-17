#!/usr/bin/env python
# coding: utf-8

# # Bitcoin Price Prediction Project
# ## Muhammad Faisal Kamran 2023-BS-AI-025

# ## About Dataset
# The dataset contains historical Bitcoin price data from September 17, 2014 to February 19, 2022 (2,713 daily observations) with the following features:
# - Date: The date of the observation (YYYY-MM-DD format)
# - Open: Opening price of Bitcoin on that day
# - High: Highest price of Bitcoin during that day
# - Low: Lowest price of Bitcoin during that day
# - Close: Closing price of Bitcoin on that day
# - Adj Close: Adjusted closing price (accounts for corporate actions)
# - Volume: Trading volume of Bitcoin for that day
# 

# ## Introduction to Python and Libraries for Machine Learning, Environmental Setup

# ### Importing Libraries

# In[33]:


import pandas as pd
import numpy as np
from sklearn.model_selection import TimeSeriesSplit
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score
from xgboost import XGBRegressor
import matplotlib.pyplot as plt
import seaborn as sns
from matplotlib.dates import DateFormatter
import warnings
warnings.filterwarnings("ignore")


# ## Reading Dataset

# In[34]:


df = pd.read_csv("bitcoin.csv")
df


# ## Exploring Dataset

# In[35]:


df.head()


# In[36]:


df.tail()


# In[37]:


df.describe()


# In[38]:


df.sample()


# ## Handling missing values, data normalization, standardization, Data visualization using Matplotlib and Seaborn

# ### Handling Missing Values

# In[39]:


df.isnull()


# In[40]:


df.isnull().sum()


# In[41]:


for col in df.columns:
    if df[col].dtype == 'object':
        df[col] = df[col].replace(['', 'NA', 'NaN'], np.nan)
        df[col].fillna(df[col].mode()[0], inplace=True)
    else:
        df[col].replace(['', 'NA', 'NaN'], np.nan, inplace=True)
        df[col] = pd.to_numeric(df[col], errors='coerce')
        df[col].fillna(df[col].mean(), inplace=True)


# ### Data Normalization and standardization

# In[42]:


from sklearn.preprocessing import MinMaxScaler, StandardScaler

numerical_cols = ['Open', 'High', 'Low', 'Close', 'Adj Close', 'Volume']

min_max_scaler = MinMaxScaler()
df_normalized = df.copy()
df_normalized[numerical_cols] = min_max_scaler.fit_transform(df[numerical_cols])

print("Normalized Data:")
print(df_normalized.head())

standard_scaler = StandardScaler()
df_standardized = df.copy()
df_standardized[numerical_cols] = standard_scaler.fit_transform(df[numerical_cols])

print("\nStandardized Data:")
print(df_standardized.head())


# ### Visualization

# In[43]:


plt.figure(figsize=(14, 7))
plt.plot(df['Date'], df['Close'])
plt.title('Bitcoin Price Over Time', fontsize=16)
plt.xlabel('Date', fontsize=14)
plt.ylabel('Price (USD)', fontsize=14)
plt.grid(True)
date_format = DateFormatter("%Y-%m")
plt.gca().xaxis.set_major_formatter(date_format)
plt.show()

plt.figure(figsize=(10, 6))
sns.histplot(df['Close'], kde=True, bins=50)
plt.title('Distribution of Bitcoin Closing Prices', fontsize=16)
plt.xlabel('Price (USD)', fontsize=14)
plt.ylabel('Frequency', fontsize=14)
plt.show()


# ## Data preprocessing

# ### Outlier Detection and Removal

# In[44]:


import pandas as pd
def remove_outliers_iqr(df):
    numeric_cols = df.select_dtypes(include=['number']).columns
    df_clean = df.copy()

    for col in numeric_cols:
        Q1 = df_clean[col].quantile(0.25)
        Q3 = df_clean[col].quantile(0.75)
        IQR = Q3 - Q1
        lower_bound = Q1 - 1.5 * IQR
        upper_bound = Q3 + 1.5 * IQR

        df_clean = df_clean[(df_clean[col] >= lower_bound) & (df_clean[col] <= upper_bound)]

    return df_clean
df_cleaned = remove_outliers_iqr(df)
print("Original shape:", df.shape)
print("Cleaned shape:", df_cleaned.shape)


# ### Convert 'Date' to datetime format and Sort by Date

# In[45]:


df['Date'] = pd.to_datetime(df['Date'])
df = df.sort_values('Date')
df.drop(columns=['Adj Close'], inplace=True)  


# ### Feature engineering

# In[46]:


df['Daily_Return'] = df['Close'].pct_change()
df['MA_7'] = df['Close'].rolling(window=7).mean()
df['MA_30'] = df['Close'].rolling(window=30).mean()
df['Lag_1'] = df['Close'].shift(1)
df['Lag_7'] = df['Close'].shift(7)
df['Lag_30'] = df['Close'].shift(30)

delta = df['Close'].diff(1)
gain = delta.where(delta > 0, 0)
loss = -delta.where(delta < 0, 0)
avg_gain = gain.rolling(window=14).mean()
avg_loss = loss.rolling(window=14).mean()
rs = avg_gain / avg_loss
df['RSI'] = 100 - (100 / (1 + rs))

df['MA_20'] = df['Close'].rolling(window=20).mean()
df['Upper_Band'] = df['MA_20'] + (2 * df['Close'].rolling(window=20).std())
df['Lower_Band'] = df['MA_20'] - (2 * df['Close'].rolling(window=20).std())

df['Volatility_7'] = df['Daily_Return'].rolling(window=7).std()
df['Volatility_30'] = df['Daily_Return'].rolling(window=30).std()

df_clean = df.dropna()


# ### Features and Targets

# In[47]:


features = [
    'Open', 'High', 'Low', 'Volume', 
    'Daily_Return', 'MA_7', 'MA_30',
    'Lag_1', 'Lag_7', 'Lag_30',
    'RSI', 'Upper_Band', 'Lower_Band',
    'Volatility_7', 'Volatility_30'
]
X = df_clean[features]
y = np.log1p(df_clean['Close']) 


# ### TIme Series Cross Validation

# In[48]:


tscv = TimeSeriesSplit(n_splits=5)
r2_scores = []
rmse_scores = []

for train_idx, test_idx in tscv.split(X):
    X_train, X_test = X.iloc[train_idx], X.iloc[test_idx]
    y_train, y_test = y.iloc[train_idx], y.iloc[test_idx]

    model = XGBRegressor(
        n_estimators=200,
        learning_rate=0.05,
        max_depth=5,
        subsample=0.9,
        colsample_bytree=0.7,
        random_state=42
    )
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    rmse = np.sqrt(mean_squared_error(np.expm1(y_test), np.expm1(y_pred)))
    r2 = r2_score(np.expm1(y_test), np.expm1(y_pred))

    rmse_scores.append(rmse)
    r2_scores.append(r2)


# ## Linear Regression

# In[49]:


from sklearn.linear_model import LinearRegression
import numpy as np
import matplotlib.pyplot as plt

df['Date'] = pd.to_datetime(df['Date'])
df['Date_ordinal'] = df['Date'].map(pd.Timestamp.toordinal)

X = df[['Date_ordinal']] 
y = df['Close']         

model = LinearRegression()
model.fit(X, y)

df['Predicted_Close'] = model.predict(X)

plt.figure(figsize=(10, 5))
plt.plot(df['Date'], df['Close'], label='Actual Close Price')
plt.plot(df['Date'], df['Predicted_Close'], label='Predicted Close Price', linestyle='--')
plt.xlabel('Date')
plt.ylabel('Close Price')
plt.title('Linear Regression on Bitcoin Close Price')
plt.legend()
plt.grid(True)
plt.show()


# ## Decision Trees

# In[50]:


from sklearn.tree import DecisionTreeRegressor
import matplotlib.pyplot as plt


df['Date'] = pd.to_datetime(df['Date'])
df['Date_ordinal'] = df['Date'].map(pd.Timestamp.toordinal)

X = df[['Date_ordinal']]
y = df['Close']

tree_model = DecisionTreeRegressor(max_depth=5) 
tree_model.fit(X, y)


df['DT_Predicted_Close'] = tree_model.predict(X)

plt.figure(figsize=(10, 5))
plt.plot(df['Date'], df['Close'], label='Actual Close Price')
plt.plot(df['Date'], df['DT_Predicted_Close'], label='Decision Tree Prediction', linestyle='--')
plt.xlabel('Date')
plt.ylabel('Close Price')
plt.title('Decision Tree Regression on Bitcoin Close Price')
plt.legend()
plt.grid(True)
plt.show()


# ## Support Vector Machine

# In[51]:


from sklearn.svm import SVR
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt

df['Date'] = pd.to_datetime(df['Date'])
df['Date_ordinal'] = df['Date'].map(pd.Timestamp.toordinal)

X = df[['Date_ordinal']]
y = df['Close']

scaler_X = StandardScaler()
scaler_y = StandardScaler()
X_scaled = scaler_X.fit_transform(X)
y_scaled = scaler_y.fit_transform(y.values.reshape(-1, 1)).flatten()

svr_model = SVR(kernel='rbf', C=100, gamma=0.1, epsilon=0.1)
svr_model.fit(X_scaled, y_scaled)

y_svr_pred_scaled = svr_model.predict(X_scaled)
df['SVR_Predicted_Close'] = scaler_y.inverse_transform(y_svr_pred_scaled.reshape(-1, 1))

plt.figure(figsize=(10, 5))
plt.plot(df['Date'], df['Close'], label='Actual Close Price')
plt.plot(df['Date'], df['SVR_Predicted_Close'], label='SVM Prediction', linestyle='--')
plt.xlabel('Date')
plt.ylabel('Close Price')
plt.title('Support Vector Machine Regression on Bitcoin Close Price')
plt.legend()
plt.grid(True)
plt.show()


# ## Evaluating Metrics

# In[52]:


print("\n=== Cross-Validated Performance ===")
print(f"Avg RMSE: {np.mean(rmse_scores):.2f}")
print(f"Avg R²: {np.mean(r2_scores):.4f}")


# ## Model Training

# In[53]:


final_model = XGBRegressor(
    n_estimators=200,
    learning_rate=0.05,
    max_depth=5,
    subsample=0.9,
    colsample_bytree=0.7,
    random_state=42
)
final_model.fit(X, y)


# ## Prediction

# In[54]:


latest_input = X.iloc[[-1]]
predicted_price_log = final_model.predict(latest_input)[0]
predicted_price = predicted_price_log

print("\n=== Latest Price Prediction ===")
print(f"Actual Price: ${df_clean.iloc[-1]['Close']:.2f}")
print(f"Predicted Price: ${predicted_price:.2f}")


# In[ ]:




