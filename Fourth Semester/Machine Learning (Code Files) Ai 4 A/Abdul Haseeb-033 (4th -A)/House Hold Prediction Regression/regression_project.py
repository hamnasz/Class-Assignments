#!/usr/bin/env python
# coding: utf-8

# # Importing Necessory Libraries

# In[12]:


import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

from sklearn.impute import SimpleImputer
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
from sklearn.svm import SVR
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score


# ## Importing Dataset

# In[13]:


df = pd.read_csv("house.csv")


# ## Preprocessing Steps and Exploring Dataset

# In[21]:


df


# In[22]:


df.head()


# In[23]:


df.tail()


# In[24]:


df.info()


# In[25]:


df.describe()


# In[31]:


df.columns


# In[30]:


df.shape


# In[32]:


df['Num_Bedrooms']


# In[35]:


df['Num_Bedrooms'].unique()


# In[36]:


df['Num_Bedrooms'].nunique()


# In[37]:


df['Num_Bathrooms'].nunique()


# In[38]:


df['Num_Bathrooms'].unique()


# In[34]:


df.nunique()


# In[29]:


df.isnull().sum()


# In[41]:


print(df.loc[5])
print(" ")
type(df.loc[5])


# # Handle missing values

# In[55]:


imputer = SimpleImputer(strategy='mean')
df_imputed = pd.DataFrame(imputer.fit_transform(df), columns=df.columns)


# # Removing Outliers

# In[56]:


numeric_cols = df_imputed.select_dtypes(include=[np.number])

Q1 = numeric_cols.quantile(0.25)
Q3 = numeric_cols.quantile(0.75)
IQR = Q3 - Q1

df_cleaned = df[~((numeric_cols < (Q1 - 1.5 * IQR)) | (numeric_cols > (Q3 + 1.5 * IQR))).any(axis=1)]

plt.figure(figsize=(20, 6))

plt.subplot(1, 2, 1)
numeric_cols.boxplot()
plt.title("Before Outlier Removal")

plt.subplot(1, 2, 2)
df_cleaned.select_dtypes(include=[np.number]).boxplot()
plt.title("After Outlier Removal")

plt.tight_layout()
plt.show()


# ## Standardize data

# In[57]:


scaler = StandardScaler()
scaled_features = scaler.fit_transform(df_cleaned.drop('House_Price', axis=1))
X = pd.DataFrame(scaled_features, columns=df.columns[:-1])
y = df_cleaned['House_Price']


# ## Spliting dataset

# In[58]:


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


# ## Model Training

# ### Linear Regression

# In[59]:


lr_model = LinearRegression()
lr_model.fit(X_train, y_train)
lr_preds = lr_model.predict(X_test)


# ### DesicionTree Regression

# In[60]:


dt_model = DecisionTreeRegressor(random_state=42)
dt_model.fit(X_train, y_train)
dt_preds = dt_model.predict(X_test)


# ### Model Evaluation

# In[61]:


def evaluate_model(name, y_true, y_pred):
    print(f"{name} Evaluation:")
    print(f"  MAE:  {mean_absolute_error(y_true, y_pred):.2f}")
    print(f"  MSE:  {mean_squared_error(y_true, y_pred):.2f}")
    print(f"  RMSE: {np.sqrt(mean_squared_error(y_true, y_pred)):.2f}")
    print(f"  R2:   {r2_score(y_true, y_pred):.2f}")
    print("-" * 40)

evaluate_model("Linear Regression", y_test, lr_preds)
evaluate_model("Decision Tree", y_test, dt_preds)


# ### Final Output

# In[62]:


sample_input = X_test.iloc[[0]]
predicted_price = lr_model.predict(sample_input)[0]
print(f"Predicted House Price: ${predicted_price:.2f}")

