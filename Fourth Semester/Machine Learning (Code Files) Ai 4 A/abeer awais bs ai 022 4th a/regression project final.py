#!/usr/bin/env python
# coding: utf-8

# # Importing libraries and loading dataset

# In[8]:


import matplotlib.pyplot as plt


# In[9]:


import seaborn as sns
color =sns.color_palette()


# In[10]:


import numpy as np


# In[11]:


import pandas as pd


# In[12]:


data = pd.read_csv("C://Users//ADMIN//MACHINE LEARNING//archive (1)//Salary_dataset.csv")


# # Preview of the Dataset

# In[13]:


data.head()


# # First 30 Rows 

# In[14]:


data.head(30)


# # Preview of the Last Rows 

# In[15]:


data.tail()


# # Dimensions of the salary Dataset

# In[16]:


data.shape


# # Preview of the Last 20 Rows 

# In[17]:


data.tail(20)


# # Random Sample of 30 Rows

# In[18]:


data.sample(30)


# # DataFrame Info Summary

# In[19]:


data.info()


# # Descriptive Statistics of the salary Dataset

# In[20]:


data.describe()


# In[21]:


import pandas as pd


# # Count of Missing Values per Column in the Dataset

# In[22]:


data.isnull().sum()


# In[23]:


import pandas as pd


# In[24]:


import numpy as np


# In[25]:


numeric_cols =data.select_dtypes(include=[np.number])


# In[26]:


non_numeric_cols =data.select_dtypes(exclude=[np.number])


# In[27]:


numeric_cols.fillna(numeric_cols.mean(),inplace= True )


# In[28]:


for col in non_numeric_cols.columns:
    non_numeric_cols[col].fillna(non_numeric_cols[col].mode()[0], inplace=True)


# In[29]:


data = pd.concat([numeric_cols,non_numeric_cols], axis=1)


# In[30]:


missing_values=data.isnull().sum()


# In[31]:


print(missing_values)


# In[32]:


data.isnull().sum()


# # Missing Values After Dropping Rows with Nulls

# In[33]:


data.dropna(inplace=True)
missing_values= data.isnull().sum()
print(missing_values)


# In[34]:


data.shape


# In[35]:


data.drop_duplicates(inplace=True)
data.shape


# In[36]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


# In[37]:


data.describe()


# # Comparison of Numeric Features Before and After Outlier Removal Using IQR Method

# In[41]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Step 1: Select numeric columns
numeric_cols = data.select_dtypes(include=[np.number])

# Step 2: Calculate IQR for each numeric column
Q1 = numeric_cols.quantile(0.25)
Q3 = numeric_cols.quantile(0.75)
IQR = Q3 - Q1

# Step 3: Remove outliers using IQR method
data_cleaned = data[~((numeric_cols < (Q1 - 1.5 * IQR)) | (numeric_cols > (Q3 + 1.5 * IQR))).any(axis=1)]

# Step 4: Plot before outlier removal
plt.figure(figsize=(20, 6))

plt.subplot(1, 2, 1)
numeric_cols.boxplot()
plt.title("Before Outlier Removal")

# Optional: Plot after outlier removal
plt.subplot(1, 2, 2)
data_cleaned.select_dtypes(include=[np.number]).boxplot()
plt.title("After Outlier Removal")

plt.tight_layout()
plt.show()


# In[1]:


from sklearn.preprocessing import MinMaxScaler 


# # Dataset After Min-Max Scaling of Numeric Features and Combining with Non-Numeric Features

# In[8]:


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


# # Dataset After Standard Scaling of Numeric Features and Integration with Non-Numeric Columns

# In[9]:


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

