#!/usr/bin/env python
# coding: utf-8

# # IMPORT LIBRARIES

# In[4]:


import matplotlib.pyplot as plt 
import seaborn as sns 
color = sns.color_palette()

import numpy as np
import pandas as pd 


# # READ DATA

# In[5]:


data = pd.read_csv("C:/Users/ideal/Downloads/linear/train.csv")


data.head()


# In[6]:


data.head(30)


# In[7]:


data.tail()


# In[8]:


data.shape


# In[9]:


data.sample(5)


# In[10]:


data.info()


# In[12]:


data.describe()


# # DATA CLEANING

# # CHECKING NULL VALUE

# In[43]:


data.isnull().sum()


# In[48]:


numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])


numeric_cols.fillna(numeric_cols.mean(), inplace=True)   



data = pd.concat([numeric_cols, non_numeric_cols], axis=1)




# In[50]:


numeric_cols.fillna(numeric_cols.mean(), inplace=True)   
for col in non_numeric_cols.columns:
    non_numeric_cols[col].fillna(non_numeric_cols[col].mode()[0], inplace=True)  
data = pd.concat([numeric_cols, non_numeric_cols], axis=1)


# # DROP MISSING VALUES

# In[19]:


data.dropna(inplace=True)

missing_values = data.isnull().sum()
print(missing_values)


# In[20]:


data.drop_duplicates(inplace=True)
data.shape


# # CHECKING SHAPE OF DATA

# In[44]:


data.shape


# # CHECKING OUTLIERS

# In[24]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Assuming `data` is your original DataFrame
numeric_cols = data.select_dtypes(include=[np.number])


plt.figure(figsize=(20, 6))
plt.subplot(1, 2, 1)
numeric_cols.boxplot()
plt.title("Before Outlier Removal")

Q1 = numeric_cols.quantile(0.25)
Q3 = numeric_cols.quantile(0.75)
IQR = Q3 - Q1

data_cleaned = data[~((numeric_cols < (Q1 - 1.5 * IQR)) | (numeric_cols > (Q3 + 1.5 * IQR))).any(axis=1)]


plt.subplot(1, 2, 2)
data_cleaned.select_dtypes(include=[np.number]).boxplot()
plt.title("After Outlier Removal")

plt.tight_layout()
plt.show()



# # DATA TRANSFORMATION

# In[45]:


numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])


scaler = MinMaxScaler()
scaled_numeric_data = scaler.fit_transform(numeric_cols)


scaled_numeric_df = pd.DataFrame(scaled_numeric_data, columns=numeric_cols.columns)


scaled_data = pd.concat([scaled_numeric_df, non_numeric_cols.reset_index(drop=True)], axis=1)


print(scaled_data.shape)
print()
print('*' * 60)
scaled_data.head()


# # STANDARIZATION

# In[51]:


from sklearn.preprocessing import StandardScaler




numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])


scaler = StandardScaler()
scaled_numeric_data = scaler.fit_transform(numeric_cols)


scaled_numeric_df = pd.DataFrame(scaled_numeric_data, columns=numeric_cols.columns)


scaled_data = pd.concat([scaled_numeric_df, non_numeric_cols.reset_index(drop=True)], axis=1)

print(scaled_data.shape)
print()
print('*' * 60)
scaled_data.head()
(133, 13)


# In[27]:


data["x"].unique()


# In[28]:


data.x.unique()


# In[47]:


cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']


data1 = pd.get_dummies(cat_features)
data1


# In[30]:


data1.info()


# # LINEAR REGRESSION

# In[52]:


from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error


# In[32]:


np.random.seed(42)
X = 2 * np.random.rand(100, 1)
y = 4 + 3 * X + np.random.randn(100, 1)


# In[33]:


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


# In[34]:


model = LinearRegression()
model.fit(X_train, y_train)


# In[35]:


y_pred = model.predict(X_test)


# In[36]:


mse = mean_squared_error(y_test, y_pred)
print(f'Mean Squared Error: {mse}')


# In[37]:


plt.scatter(X_test, y_test, color='blue', label='Actual data')
plt.plot(X_test, y_pred, color='red', linewidth=2, label='Regression line')
plt.xlabel('X')
plt.ylabel('y')
plt.legend()
plt.title('Linear Regression Model')
plt.show()


# In[38]:


from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score


# In[39]:


np.random.seed(42)
X = 2 * np.random.rand(100, 1)
y = 4 + 3 * X + np.random.randn(100, 1)


# In[40]:


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)

y_pred = model.predict(X_test)


# In[41]:


mse = mean_squared_error(y_test, y_pred)
mae = mean_absolute_error(y_test, y_pred)
rmse = np.sqrt(mse)
r2 = r2_score(y_test, y_pred)


# In[42]:


print(f'Mean Squared Error (MSE): {mse}')
print(f'Mean Absolute Error (MAE): {mae}')
print(f'Root Mean Squared Error (RMSE): {rmse}')
print(f'R² Score: {r2}')


# In[ ]:




