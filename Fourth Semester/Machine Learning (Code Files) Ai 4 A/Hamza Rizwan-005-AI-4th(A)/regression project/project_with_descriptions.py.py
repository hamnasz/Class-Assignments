#!/usr/bin/env python
# coding: utf-8

# ### Importing necessary libraries
# This cell imports essential Python libraries for data manipulation, model building, and evaluation.

# In[3]:


import pandas as pd
import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score


# ### Loading the dataset
# This cell reads the power consumption data from a CSV file and prints its shape.

# In[5]:


df = pd.read_csv('power_consumption.csv', low_memory=False)
print("Data Loaded. Shape:", df.shape)


# ### Displaying the first few rows
# This cell shows a preview of the dataset using the `head()` function.

# In[7]:


df.head()


# ### Show Last Few Rows
# Displaying the last five rows of the dataset.

# In[9]:


df.tail()


# ### Dataset Information
# Checking the structure, data types, and non-null values.

# In[11]:


df.info()


# ### Descriptive Statistics
# Getting statistical summary of the dataset's numerical features.

# In[13]:


df.describe()


# ### Date Parsing and Feature Engineering
# Converting 'Date' to datetime and extracting day, month, year, and weekday.

# In[15]:


df['Date'] = pd.to_datetime(df['Date'], format='%d/%m/%Y', errors='coerce')
df = df.dropna(subset=['Date'])  

df['Day'] = df['Date'].dt.day
df['Month'] = df['Date'].dt.month
df['Year'] = df['Date'].dt.year
df['Weekday'] = df['Date'].dt.weekday

df = df.drop(columns=['Date', 'Time'])


# ### Data Cleaning
# Replacing placeholders, removing nulls, and converting data types.

# In[17]:


df = df.replace('?', np.nan)
df = df.dropna()
df = df.astype(float)
print("Data cleaned. Shape after cleaning:", df.shape)


# ### Feature and Target Selection
# Separating input features from the target variable for prediction.

# In[19]:


target = 'Global_active_power'
features = df.drop(columns=[target]).columns.tolist()

X = df[features]
y = df[target]


# ### Split Data
# Splitting the dataset into training and test sets for evaluation.

# In[21]:


X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)


# ### Train Random Forest Model
# Initializing and fitting a Random Forest Regressor model.

# In[23]:


model = RandomForestRegressor(n_estimators=100, random_state=42, n_jobs=-1)

model.fit(X_train, y_train)
y_pred = model.predict(X_test)


# ### Evaluate the Model
# Calculating evaluation metrics: MAE, RMSE, and R² score.

# In[25]:


mse = mean_squared_error(y_test, y_pred)
rmse = np.sqrt(mse)
mae = mean_absolute_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

print("\nModel Evaluation:")
print(f"Mean Absolute Error (MAE): {mae:.4f}")
print(f"Root Mean Squared Error (RMSE): {rmse:.4f}")
print(f"R² Score: {r2:.4f}")


# ### Compare Actual vs Predicted
# Displaying predictions and calculating percentage error for the first 10 records.

# In[27]:


comparison_df = pd.DataFrame({
    'Actual': y_test.values,
    'Predicted': y_pred
})
comparison_df['Error (%)'] = 100 * abs(comparison_df['Actual'] - comparison_df['Predicted']) / comparison_df['Actual']

print("\nSample Predictions (first 10):")
print(comparison_df.head(10).to_string(index=False))


# ### Error Summary
# Calculating average, maximum, and minimum error percentages.

# In[29]:


avg_error = comparison_df['Error (%)'].mean()
max_error = comparison_df['Error (%)'].max()
min_error = comparison_df['Error (%)'].min()

print("\nPrediction Error Summary:")
print(f"Average Error: {avg_error:.2f}%")
print(f"Max Error: {max_error:.2f}%")
print(f"Min Error: {min_error:.2f}%")


# ### Accuracy Extremes
# Identifying the top 3 most and least accurate predictions.

# In[31]:


most_accurate = comparison_df.sort_values(by='Error (%)').head(3)
least_accurate = comparison_df.sort_values(by='Error (%)', ascending=False).head(3)

print("\nMost Accurate Predictions:")
print(most_accurate.to_string(index=False))

print("\nLeast Accurate Predictions:")
print(least_accurate.to_string(index=False))


# ### Average Power Consumption
# Calculating the average power consumption in kW and converting it to Watts.

# In[33]:


average_consumption_kw = df['Global_active_power'].mean()
average_consumption_wh = average_consumption_kw * 1000  # Convert kW to Watts

print(f"\nOn average, each household consumes {average_consumption_kw:.4f} kW or {average_consumption_wh:.2f} Watts of power.")

