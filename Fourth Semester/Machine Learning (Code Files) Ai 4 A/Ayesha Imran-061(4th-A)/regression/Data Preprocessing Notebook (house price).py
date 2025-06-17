#!/usr/bin/env python
# coding: utf-8

# # Data Preprocessing Steps

# 1. Reading Data
# 2. Exploring Data / Data Insight
# 3. Cleansing Data
# 4. Outlier Detection and Removing
# 5. Data Transformation (Normalize Data / Rescale Data)
# 6. Categorical into Numerical 
# 7. Dimensionality Reduction(PCA)
# 8. Handling Imbalanced Data
# 9. Feature Selection
# 10. Data Splitting

# In[8]:


import matplotlib.pyplot as plt 
import seaborn as sns 
color = sns.color_palette()

import numpy as np 
import pandas as pd 


# # 1: Reading Data

# In[9]:


data = pd.read_csv('house_price_regression_dataset.csv')

data.head()


# In[10]:


data.head(2)


# In[11]:


data.head(30)


# In[12]:


data.tail()


# In[13]:


data.shape


# In[14]:


data.tail(20)


# In[15]:


data.sample()


# In[16]:


data.sample(30)


# In[17]:


data.info()


# In[18]:


data.describe()


# # 2: Data Cleaning

# Handling Missing Values
# -
# - Imputation: Filling missing values with mean.

# In[19]:


data.isnull().sum()


# In[20]:


import pandas as pd
import numpy as np

numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])

numeric_cols.fillna(numeric_cols.mean(), inplace=True)   


data = pd.concat([numeric_cols, non_numeric_cols], axis=1)

missing_values = data.isnull().sum()
print(missing_values)


# In[21]:


numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])

numeric_cols.fillna(numeric_cols.mean(), inplace=True)   
for col in non_numeric_cols.columns:
    non_numeric_cols[col].fillna(non_numeric_cols[col].mode()[0], inplace=True)  

data = pd.concat([numeric_cols, non_numeric_cols], axis=1)


missing_values = data.isnull().sum()
print(missing_values)


# In[22]:


data.shape


# Removal: Deleting rows with missing values.
# -

# In[23]:


data.isnull().sum()


# In[24]:


data.shape


# In[25]:


data.dropna(inplace=True)

missing_values = data.isnull().sum()
print(missing_values)


# In[26]:


data.shape


# In[ ]:





# Removing Duplicates
# -

# In[27]:


data.shape


# In[28]:


data.drop_duplicates(inplace=True)
data.shape


# # 3: Outlier Detection and Removal

# In[29]:


data.describe()


# In[30]:


0.25-1.5*0.5


# In[31]:


0.75 + 1.5 * 0.5


# In[32]:


numeric_cols = data.select_dtypes(include=[np.number])

Q1 = numeric_cols.quantile(0.25)
Q3 = numeric_cols.quantile(0.75)
IQR = Q3 - Q1

data_cleaned = data[~((numeric_cols < (Q1 - 1.5 * IQR)) | (numeric_cols > (Q3 + 1.5 * IQR))).any(axis=1)]

plt.figure(figsize=(20, 6))

plt.subplot(1, 2, 1)
numeric_cols.boxplot()
plt.title("Before Outlier Removal")

plt.tight_layout()
plt.show()


# In[35]:


plt.figure(figsize=(20, 6))

plt.subplot(1, 2, 2)
data_cleaned.select_dtypes(include=[np.number]).boxplot()
plt.title("After Outlier Removal")

plt.tight_layout()
plt.show()


# In[ ]:


data_cleaned.head()


# # 4. Data Transformation
# 

# Key Differences
# -
# Range of Values:
# 
# Normalization: Values are scaled to a fixed range, typically [0, 1].
# Standardization: Values are rescaled to have a mean of 0 and a standard deviation of 1.
# Effect on Distribution:
# 
# Normalization: Compresses or stretches the data to fit within the specified range, potentially altering the original distribution.
# Standardization: Preserves the shape of the original distribution but changes the scale.
# Use Cases:
# 
# Normalization: Suitable for distance-based algorithms, like k-nearest neighbors and neural networks.
# Standardization: Suitable for algorithms that assume a normal distribution, like linear regression and logistic regression.
# 

# Normalization/Standardization
# -
# - Normalization
# Definition:
# Normalization rescales the data to a fixed range, typically [0, 1] or [-1, 1].

# In[ ]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler

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


# In[ ]:





# Standardization
# -
# Definition:
# Standardization rescales the data so that it has a mean of 0 and a standard deviation of 1.

# In[ ]:


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


# # 5: One-Hot Encoding
# 
# 

# In[ ]:


from sklearn.preprocessing import StandardScaler

data.head(2)


# In[ ]:


data["Num_Bedrooms"].unique()


# In[ ]:


data.Year_Built.unique()


# In[ ]:


from sklearn.preprocessing import StandardScaler

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']

data1 = pd.get_dummies(cat_features)
data1


# In[ ]:


data1.info()


# In[ ]:


cat_features


# In[ ]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler


cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']

data1 = pd.get_dummies(data, columns=cat_features)

scaled_data = pd.concat([data, data1], axis=1)

print(scaled_data.shape)
print()
print('*' * 70)

scaled_data.head()


# In[ ]:


data.columns


# In[ ]:


scaled_data.columns


# In[ ]:





# In[ ]:


data1.head()


# In[ ]:





# # 6: Data Reduction

# Dimensionality Reduction
# -
# PCA (Principal Component Analysis)

# In[ ]:


scaled_data.shape


# In[ ]:


from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA

data.fillna(data.mean(numeric_only=True), inplace=True)

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']
numeric_features = [feature for feature in data.columns if data[feature].dtype != 'O']

data = pd.get_dummies(data, columns=cat_features)

scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features].values)


pca = PCA(n_components=8)
data_pca = pca.fit_transform(data)

print(data_pca.shape)
print(data_pca[:5])  


plt.figure(figsize=(14, 6))

plt.subplot(1, 2, 1)
plt.scatter(data[numeric_features[0]], data[numeric_features[1]], alpha=0.5)
plt.title('Original Data')
plt.xlabel(numeric_features[0])
plt.ylabel(numeric_features[1])

pca = PCA(n_components=8)  
data_pca = pca.fit_transform(data)

plt.subplot(1, 2, 2)
plt.scatter(data_pca[:, 0], data_pca[:, 1], alpha=0.5)
plt.title('PCA Transformed Data')
plt.xlabel('Principal Component 1')
plt.ylabel('Principal Component 2')

plt.tight_layout()
plt.show()


# In[ ]:


type(data_pca)


# In[ ]:


data_pca.ndim


# In[ ]:


data_pca.shape


# In[ ]:





# # 7: Handling Imbalanced Data
#     
# - Resampling Techniques
# - Oversampling

# In[ ]:


data.House_Price.value_counts(True)


# In[ ]:


data.shape


# # 8: Splitting Data

# In[ ]:


from sklearn.model_selection import train_test_split

X = data.drop('Year_Built', axis=1)
y = data['House_Price']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)
X_train.shape, X_test.shape, y_train.shape, y_test.shape


# In[ ]:


from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

X = data.drop(['Year_Built', 'House_Price'], axis=1)
y = data['House_Price']

# Train-test split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# Model training
model = LinearRegression()
model.fit(X_train, y_train)

# Predictions
y_pred = model.predict(X_test)

# Evaluation
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

print(f"Mean Squared Error: {mse}")
print(f"R² Score: {r2}")


# In[ ]:




