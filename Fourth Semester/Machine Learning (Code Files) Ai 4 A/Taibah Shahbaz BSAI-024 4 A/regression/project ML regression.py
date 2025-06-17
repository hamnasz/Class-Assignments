#!/usr/bin/env python
# coding: utf-8

# # Importing libraries

# In[2]:


import matplotlib.pyplot as plt
import seaborn as sns
color = sns.color_palette()

import numpy as np
import pandas as pd
        
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.decomposition import PCA
from sklearn.feature_selection import SelectKBest, f_regression
from sklearn.model_selection import train_test_split


# # Reading data

# In[4]:


data = pd.read_csv('car data.csv')
data.head()


# In[5]:


data.tail()


# In[6]:


data.shape


# In[7]:


data.sample()


# In[8]:


data.info()


# In[9]:


data.describe()


# # Checking missing values

# In[11]:


data.isnull().sum()


# # Checking unique values

# In[13]:


data.nunique()


# # Cleansing Data

# In[55]:


data_cleaned = data.drop(columns=['Car_Name'])

data_cleaned['Car_Age'] = 2025 - data_cleaned['Year']

data_cleaned.drop(columns=['Year'], inplace=True)

data_cleaned.to_csv("car_data_cleaned.csv", index=False)

print("Data cleaning complete. File saved as 'car_data_cleaned.csv'")


# # Dropping missing values if any

# In[16]:


data.dropna()


# # Removing duplicate rows

# In[18]:


data.drop_duplicates()


# # Outlier Detection and Removing

# In[20]:


0.25-1.5*0.5


# In[21]:


0.75 + 1.5 * 0.5


# In[22]:


numerical_cols = data.select_dtypes(include=[np.number]).columns.tolist()

for col in numerical_cols:
    plt.figure(figsize=(6, 2))
    sns.boxplot(x=data[col], color='skyblue')
    plt.title(f'Boxplot of {col}')
    plt.show()


# In[23]:


for col in numerical_cols:
    Q1 = data[col].quantile(0.25)
    Q3 = data[col].quantile(0.75)
    IQR = Q3 - Q1
    lower_bound = Q1 - 1.5 * IQR
    upper_bound = Q3 + 1.5 * IQR
    data = data[(data[col] >= lower_bound) & (data[col] <= upper_bound)]

data.shape


# # Normalization

# In[64]:


numeric_cols = data.select_dtypes(include=['number']).columns

scaler = StandardScaler()

scaled_numeric_data = scaler.fit_transform(data[numeric_cols])

scaled_numeric_df = pd.DataFrame(scaled_numeric_data, columns=numeric_cols)

non_numeric_data = data.drop(columns=numeric_cols).reset_index(drop=True)

scaled_data = pd.concat([scaled_numeric_df, non_numeric_data], axis=1)

print(scaled_data.shape)
print('*' * 60)
print(scaled_data.head())


# # Categorical into Numerical

# In[35]:


categorical_cols = data.select_dtypes(include='object').columns.tolist()
categorical_cols


# In[37]:


le = LabelEncoder()
for col in categorical_cols:
    data[col] = le.fit_transform(data[col])


# # Dimensionality Reduction (PCA)

# In[40]:


X = data.drop('Selling_Price', axis=1)
y = data['Selling_Price']


# In[42]:


pca = PCA(0.95)
X_pca = pca.fit_transform(X)


# In[44]:


X_pca.shape


# In[46]:


plt.figure(figsize=(6,4))
sns.histplot(y, kde=True, color='green')
plt.title('Distribution of Selling Price')
plt.show()


# # Data Splitting

# In[57]:


X_selected = X 
X_train, X_test, y_train, y_test = train_test_split(X_selected, y, test_size=0.2, random_state=42)

print("Training Set Shape:", X_train.shape)
print("Test Set Shape:", X_test.shape)


# # regression model

# In[59]:


import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error

np.random.seed(42)
X = 2 * np.random.rand(100, 1)
y = 4 + 3 * X + np.random.randn(100, 1)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)

y_pred = model.predict(X_test)

mse = mean_squared_error(y_test, y_pred)
print(f'Mean Squared Error: {mse}')

plt.scatter(X_test, y_test, color='blue', label='Actual data')
plt.plot(X_test, y_pred, color='red', linewidth=2, label='Regression line')
plt.xlabel('X')
plt.ylabel('y')
plt.legend()
plt.title('Linear Regression Model')
plt.show()


# # evaluation matrices

# In[61]:


import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score

np.random.seed(42)
X = 2 * np.random.rand(100, 1)
y = 4 + 3 * X + np.random.randn(100, 1)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)

y_pred = model.predict(X_test)

mse = mean_squared_error(y_test, y_pred)
mae = mean_absolute_error(y_test, y_pred)
rmse = np.sqrt(mse)
r2 = r2_score(y_test, y_pred)

print(f'Mean Squared Error (MSE): {mse}')
print(f'Mean Absolute Error (MAE): {mae}')
print(f'Root Mean Squared Error (RMSE): {rmse}')
print(f'R² Score: {r2}')


# In[66]:


df_preds = pd.DataFrame({
    'Actual': y_test.squeeze(),
    'Predicted': y_pred.squeeze()
})

print("\nActual vs Predicted prices:")
print(df_preds.head(10))


# In[ ]:




