#!/usr/bin/env python
# coding: utf-8

# # Data preporocessing

# # Description
# This is a simulated dataset exploring how lifestyle habits affect academic performance in students. With 1,000 synthetic student records and 15+ features including study hours, sleep patterns, social media usage, diet quality, mental health, and final exam scores, it’s perfect for ML projects, regression analysis, clustering, and data viz. Created using realistic patterns for educational practice.
# 
# Ever wondered how much Netflix, sleep, or TikTok scrolling affects your grades? 👀 This dataset simulates 1,000 students' daily habits—from study time to mental health—and compares them to final exam scores. It's like spying on your GPA through the lens of lifestyle. Perfect for EDA, ML practice, or just vibing with data while pretending to be productive.

# In[1]:


import matplotlib.pyplot as plt 
import seaborn as sns 
color = sns.color_palette()

import numpy as np
import pandas as pd 
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OneHotEncoder
from sklearn.impute import SimpleImputer
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score


# # Reading Data

# In[3]:


data = pd.read_csv('student_habits_performance.csv')
data.head()


# In[4]:


data.head(2)


# In[5]:


data.shape


# In[6]:


data.sample()


# In[7]:


data.info()


# In[8]:


data.describe()


# # Data Cleaning

# Handling Missing Values
# -
# - Imputation: Filling missing values with mean.

# In[11]:


import pandas as pd


# In[20]:


data.isnull().sum()


# In[22]:


data.shape


# # Drop student_id

# In[25]:


df = pd.DataFrame(data)
df = df.drop('student_id', axis=1)
df = pd.DataFrame(data)

print(df)


# # Separate target and features

# In[28]:


X = df.drop('exam_score', axis=1)
y = df['exam_score']
print(X)
print(y)


# 
# # Separate categorical and numerical columns

# In[31]:


categorical_cols = X.select_dtypes(include=['object']).columns.tolist()
numerical_cols = X.select_dtypes(include=['int64', 'float64']).columns.tolist()


# In[33]:


categorical_cols


# In[35]:


numerical_cols


# # Create preprocessing for numerical and categorical data
# 

# In[38]:


numerical_transformer = SimpleImputer(strategy='mean')
categorical_transformer = Pipeline(steps=[
    ('imputer', SimpleImputer(strategy='most_frequent')),
    ('onehot', OneHotEncoder(handle_unknown='ignore'))
])


# 
# # Combine both transformers

# In[41]:


preprocessor = ColumnTransformer(
    transformers=[
        ('num', numerical_transformer, numerical_cols),
        ('cat', categorical_transformer, categorical_cols)
    ])


# In[43]:


preprocessed_data = preprocessor.fit_transform(data)
print("Transformed data:")
print(preprocessed_data)


# # Create a pipeline with preprocessor and linear regression
# 

# In[46]:


model = Pipeline(steps=[
    ('preprocessor', preprocessor),
    ('regressor', LinearRegression())
])


# In[48]:


model


# # Split data into train and test sets

# In[51]:


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


# In[53]:


model.fit(X_train, y_train)


# # Make predictions

# In[56]:


y_pred = model.predict(X_test)


# # Evaluate the model

# In[59]:


mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

print("Mean Squared Error:", mse)
print("R^2 Score:", r2)


# # Part II

# In[62]:


import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.pipeline import Pipeline
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.impute import SimpleImputer
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

df = pd.DataFrame(data)


# # Drop student_id

# In[65]:


df = df.drop(columns=['student_id'])


# 
# # Handle missing values early (for safety in full dataset)

# In[68]:


df.fillna(df.mode().iloc[0], inplace=True)


# # Outlier detection using IQR method on numerical columns

# In[71]:


def remove_outliers(df, cols):
    for col in cols:
        Q1 = df[col].quantile(0.25)
        Q3 = df[col].quantile(0.75)
        IQR = Q3 - Q1
        lower = Q1 - 1.5 * IQR
        upper = Q3 + 1.5 * IQR
        df = df[(df[col] >= lower) & (df[col] <= upper)]
    return df


# # Define numerical columns

# In[74]:


numerical_cols = df.select_dtypes(include=['int64', 'float64']).drop(columns=['exam_score']).columns.tolist()


# 
# # Remove outliers

# In[77]:


df = remove_outliers(df, numerical_cols)


# # Separate features and target

# In[80]:


X = df.drop('exam_score', axis=1)
y = df['exam_score']


# 
# # Categorical columns

# In[83]:


categorical_cols = X.select_dtypes(include=['object']).columns.tolist()


# # Preprocessing for numerical features

# In[86]:


numerical_pipeline = Pipeline(steps=[
    ('imputer', SimpleImputer(strategy='mean')),
    ('scaler', StandardScaler())
])


# 
# # Preprocessing for categorical features

# In[89]:


categorical_pipeline = Pipeline(steps=[
    ('imputer', SimpleImputer(strategy='most_frequent')),
    ('onehot', OneHotEncoder(handle_unknown='ignore'))
])


# # Combine both into ColumnTransformer

# In[92]:


preprocessor = ColumnTransformer(transformers=[
    ('num', numerical_pipeline, numerical_cols),
    ('cat', categorical_pipeline, categorical_cols)
])


# # Full pipeline with Linear Regression

# In[95]:


model = Pipeline(steps=[
    ('preprocessor', preprocessor),
    ('regressor', LinearRegression())
])


# 
# # Train/test split

# In[98]:


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


# # Train the model

# In[101]:


model.fit(X_train, y_train)


# # Predictions
# 

# In[104]:


y_pred = model.predict(X_test)


# 
# # Evaluation
# 

# In[107]:


mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)


# In[ ]:





# In[ ]:





# In[ ]:




