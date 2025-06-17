#!/usr/bin/env python
# coding: utf-8

# # DATASET DESCRIPTION

# - This dataset contains food delivery records, capturing key factors influencing delivery times. It includes attributes such as distance traveled, weather conditions, traffic level, time of day, and vehicle type, all of which impact delivery efficiency. Additionally, courier experience and preparation time are recorded, offering insights into operational factors affecting service speed. The target variable, Delivery_Time_min, represents the actual time taken for each order's delivery. Given your proficiency in preprocessing and model training, this dataset is well-suited for regression analysis or predictive modeling
# - [Food Delivery Time Prediction Dataset](https://www.kaggle.com/datasets/denkuznetz/food-delivery-time-prediction)
# 

# # IMPORTING LIBRARIES
# - pandas (pd): Used for data manipulation and analysis.
# - numpy (np): Provides numerical operations and array handling.
# - matplotlib.pyplot (plt): Enables data visualization through plots and graphs.
# 
#  

# In[1]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


# # LOADING DATASET

# In[2]:


df = pd.read_csv("C:/Users/Ayaan/Desktop/Food_Delivery_Times.csv")
df.head()


# # DATA EXPLORATION

# In[3]:


df.sample()


# In[4]:


df.tail()


# In[5]:


df.shape


# In[6]:


df.columns


# In[7]:


df.isnull().any()


# In[8]:


df.describe()


# In[9]:


df.info()


# # DATA CLEANING

# In[10]:


numeric_cols = df.select_dtypes(include=[np.number])
non_numeric_cols = df.select_dtypes(exclude=[np.number])


# In[11]:


numeric_cols.fillna(numeric_cols.mean(), inplace=True)
non_numeric_cols.fillna(non_numeric_cols.mode().iloc[0], inplace=True)


# In[12]:


df = pd.concat([numeric_cols, non_numeric_cols], axis=1)


# In[13]:


print(df.isnull().sum())


# # REMOVING DUBLICATES

# In[14]:


df.drop_duplicates(inplace=True)

df = df.loc[:, ~df.columns.str.contains("Unnamed")]

df.info()


# # OUTLIER DETECTION AND REMOVAL

# In[15]:


numeric_cols = df.select_dtypes(include=['float64', 'int64']).columns
mask = pd.Series(True, index=df.index)

for col in numeric_cols:
    Q1 = df[col].quantile(0.25)
    Q3 = df[col].quantile(0.75)
    IQR = Q3 - Q1
    lower_bound = Q1 - 1.5 * IQR
    upper_bound = Q3 + 1.5 * IQR
    mask &= df[col].between(lower_bound, upper_bound)

df_cleaned = df[mask]


# In[16]:


plt.figure(figsize=(20,6))
plt.subplot(1,2,1)
df.boxplot()
plt.title("Before Outliers Removal")
plt.tight_layout()
plt.show()


# In[17]:


plt.figure(figsize=(30,6))
plt.subplot(1,2,1)
df_cleaned.boxplot()
plt.title("After Outliers Removal")
plt.tight_layout()
plt.show()


# # DATA TRANSFORMATION

# - NORMALIZATION

# In[18]:


from sklearn.preprocessing import MinMaxScaler

numeric_cols = df.select_dtypes(include=['float64']).columns
numeric_data = df[numeric_cols]
scaler = MinMaxScaler()
scaled_numeric_data = scaler.fit_transform(numeric_data)
scaled_numeric_data = pd.DataFrame(scaled_numeric_data, columns=numeric_cols)
non_numeric_data = df.drop(columns=numeric_cols).reset_index(drop=True)
scaled_data = pd.concat((scaled_numeric_data, non_numeric_data), axis=1)

print(scaled_data.shape)
print()
print('*' * 60)
scaled_data.head()


# - STANDARDIZATION

# In[19]:


from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
import pandas as pd

scaler = StandardScaler()

numeric_cols = ["Distance_km", "Preparation_Time_min", "Courier_Experience_yrs"]
df[numeric_cols] = scaler.fit_transform(df[numeric_cols])

data_scaled = pd.DataFrame(scaler.fit_transform(df[numeric_cols]), columns=numeric_cols)  

plt.figure(figsize=(16, 6))
data_scaled.boxplot()
plt.title("Boxplot After Outlier Removal and Standardization")
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()


# # LINAER REGRESSION

# In[20]:


df = pd.get_dummies(df, columns=['Weather', 'Traffic_Level', 'Time_of_Day', 'Vehicle_Type'], drop_first=True)


# In[21]:


from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, mean_squared_error


# ### TEST TRAIN SPLIT

# In[22]:


X = df.drop('Delivery_Time_min', axis=1)
y = df['Delivery_Time_min']
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


# ### MODEL FIT

# In[23]:


model = LinearRegression()
model.fit(X_train, y_train)


# # ACTUAL VS PREDICTED GRAPGH

# In[24]:


y_pred = model.predict(X_test)
plt.scatter(y_test, y_pred)
plt.plot([y.min(), y.max()], [y.min(), y.max()], 'k--')
plt.xlabel('Actual Delivery Time')
plt.ylabel('Predicted Delivery Time')
plt.title('Actual vs Predicted Delivery Time')
plt.show()


# ## COEFFICIENT

# In[25]:


model_coef = model.coef_
model_coef.round(2)


# ## INTERCEPT

# In[26]:


model_intercept = model.intercept_
model_intercept.round(2)


# ## ACTUAL AND PREDICTED DELIVERY TIMES

# In[27]:


df_preds = pd.DataFrame({'Actual': y_test.squeeze(), 'Predicted': y_pred.squeeze()})
print("\nActual vs Predicted Delivery Times:")
print(df_preds.head(10))


# In[ ]:




