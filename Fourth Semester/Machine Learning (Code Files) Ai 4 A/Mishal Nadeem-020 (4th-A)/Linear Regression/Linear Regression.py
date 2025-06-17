#!/usr/bin/env python
# coding: utf-8

# # LINEAR REGRESSION PROJECT

# ## Dataset: Customer Lifetime Value

# ## DATA PREPROCESSING

# ### Importing Libraries

# In[1]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
import seaborn as sns
import matplotlib.pyplot as plt
from scipy import stats
from sklearn.model_selection import learning_curve

from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

from sklearn.feature_selection import RFE


# ### Reading Data

# In[3]:


df = pd.read_csv('clv.csv')


# ### Exporing Data

# In[5]:


df.head()


# In[6]:


df.tail()


# In[296]:


df.info()


# In[299]:


df.describe()


# ### Cleansing Data

# #### Before Cleansing Data

# In[303]:


df.isnull().sum()


# #### After Cleansing Data

# In[306]:


df.fillna(df.mean(numeric_only=True), inplace=True)


# In[308]:


df.isnull().sum()


# ### Outlier Detection and Removal

# In[311]:


numeric_cols = df.select_dtypes(include=[np.number])
Q1 = numeric_cols.quantile(0.25)
Q3 = numeric_cols.quantile(0.75)
IQR = Q3 - Q1
data_cleaned = df[~((numeric_cols < (Q1 - 1.5 * IQR)) | (numeric_cols > (Q3 + 1.5 * IQR))).any(axis=1)]

print("Before Outlier Removal: ", df.shape)
print("After Outlier Removal: ", data_cleaned.shape)

plt.figure(figsize=(40, 5))
plt.subplot(1, 2, 1)
numeric_cols.boxplot()
plt.title("Before Outlier Removal")
plt.tight_layout()
plt.show()

plt.figure(figsize=(40, 6))
plt.subplot(1, 2, 2)
data_cleaned.select_dtypes(include=[np.number]).boxplot()
plt.title("After Outlier Removal")
plt.tight_layout()
plt.show()


# ### Seperate Target column

# In[313]:


target_column = 'CLV'
y = data_cleaned[target_column]         
df = data_cleaned.drop(columns=[target_column, 'CustomerID'])
X = df


# ### Data Transformation (Standardization)

# #### Before Standardization

# In[316]:


df


# #### After Standardization

# In[321]:


scaler = StandardScaler()
numerical_cols = df.select_dtypes(include=np.number).columns
df[numerical_cols] = scaler.fit_transform(df[numerical_cols])


# In[323]:


df


# ### Categorical into Numerical (One-Hot Encoding)

# #### Before One-Hot Encoding

# In[327]:


df.shape


# In[329]:


df.info()


# #### After One-Hot Encoding

# In[332]:


cat_cols = df.select_dtypes(include=['object']).columns
df = pd.get_dummies(df, columns=cat_cols, drop_first=False)


# In[334]:


df.shape


# In[336]:


df.info()


# ### Feature Selection

# In[339]:


df_with_target = df.copy()
df_with_target['target'] = y 

correlation = df_with_target.corr()['target'].abs()
correlation = correlation.drop('target')

N = 7
top_features = correlation.sort_values(ascending=False).head(N).index
X_selected = df[top_features.tolist()]

print("Selected Features based on correlation:", top_features.tolist())


# ### Data Splitting

# In[342]:


X_train, X_test, y_train, y_test = train_test_split(X_selected, y, test_size=0.2, random_state=42)


# In[344]:


X_train.shape, X_test.shape, y_train.shape, y_test.shape


# ## LINEAR REGRESSION

# ### Display the first few values of selected features and target

# ### Train the model

# In[349]:


model = LinearRegression()
model.fit(X_train, y_train)


# ### Make predictions

# In[352]:


y_pred_test = model.predict(X_test)


# ### Evaluate the model

# In[355]:


mse = mean_squared_error(y_test, y_pred_test)
print("Mean Squared Error:", mse)

rmse = np.sqrt(mse)
print("Root Mean Squared Error:", rmse)

r2 = r2_score(y_test, y_pred_test)
print("R² Score:", r2)


# ### Feature Importance

# In[358]:


features = top_features 

importance = model.coef_ 
importance_df = pd.DataFrame({'Feature': features, 'Importance': importance})

importance_df = importance_df.sort_values(by='Importance', ascending=False)

importance_df.plot(kind='bar', x='Feature', y='Importance', legend=False, title='Feature Importance', color='pink')
plt.show()


# ### Model Performance Visualization

# In[360]:


plt.figure(figsize=(8, 5))

plt.scatter(y_test, y_pred_test, color='purple', alpha=0.6)

plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], 'r--', lw=2) 

plt.xlabel('Actual values of Y')
plt.ylabel('Predicted values of Y')
plt.title('Actual vs Predicted')
plt.grid(True)
plt.show()


# ### Assessing Error Patterns in Predictions

# In[364]:


residuals = y_test - y_pred_test
plt.figure(figsize=(8, 5))
plt.scatter(y_pred_test, residuals, alpha=0.6, color='teal')
plt.axhline(y=0, color='red', linestyle='--')
plt.xlabel('Predicted values of Y')
plt.ylabel('Residuals')
plt.title('Residuals Plot')
plt.grid(True)
plt.show()


# ### Training vs Cross-Validation Performance

# In[367]:


train_sizes, train_scores, test_scores = learning_curve(
    model, X_train, y_train, cv=5, scoring='r2'
)

train_mean = np.mean(train_scores, axis=1)
test_mean = np.mean(test_scores, axis=1)

plt.figure(figsize=(8, 5))
plt.plot(train_sizes, train_mean, label='Training Score', color='blue', marker='o')
plt.plot(train_sizes, test_mean, label='Cross-Validation Score', color='red', marker='s')
plt.xlabel('Training Set Size')
plt.ylabel('R² Score')
plt.title('Learning Curve: Training vs Testing Performance')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

