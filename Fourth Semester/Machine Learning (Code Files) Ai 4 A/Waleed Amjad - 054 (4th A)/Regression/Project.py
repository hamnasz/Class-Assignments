#!/usr/bin/env python
# coding: utf-8

# # Problem Description: Preprocessing of a student data set to find the hours of studying and other activities which effect the overall performance of the student.

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

# In[12]:


import matplotlib.pyplot as plt
import seaborn as sns 
color = sns.color_palette()

import numpy as np 
import pandas as pd 


# # 1: Reading Data

# In[13]:


data = pd.read_csv('Student_Performance.csv')

data.head()


# In[14]:


data.head(2)


# In[15]:


data.head(30)


# In[16]:


data.tail()


# In[17]:


data.shape


# In[18]:


data.tail(20)


# In[19]:


data.sample()


# In[20]:


data.sample(30)


# In[21]:


data.info()


# In[22]:


data.describe()


# # 2: Data Cleaning

# Handling Missing Values
# -
# - Imputation: Filling missing values with mean.

# In[23]:


import pandas as pd



# In[24]:


data.isnull().sum()


# In[25]:


import pandas as pd
import numpy as np


numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])


numeric_cols.fillna(numeric_cols.mean(), inplace=True)   




data = pd.concat([numeric_cols, non_numeric_cols], axis=1)


missing_values = data.isnull().sum()
print(missing_values)


# In[26]:


import pandas as pd
import numpy as np


numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])


numeric_cols.fillna(numeric_cols.mean(), inplace=True)   

for col in non_numeric_cols.columns:
    non_numeric_cols[col].fillna(non_numeric_cols[col].mode()[0], inplace=True)  


data = pd.concat([numeric_cols, non_numeric_cols], axis=1)


missing_values = data.isnull().sum()
print(missing_values)


# In[27]:


data.shape


# Removal: Deleting rows with missing values.
# -

# In[28]:


data.isnull().sum()


# In[29]:


data.shape


# In[30]:


data.dropna(inplace=True)


missing_values = data.isnull().sum()
print(missing_values)


# In[31]:


data.shape


# In[ ]:





# Removing Duplicates
# -

# In[32]:


data.shape


# In[33]:


data.drop_duplicates(inplace=True)
data.shape


# # 3: Outlier Detection and Removal

# In[34]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt




data.describe()


# In[35]:


0.25-1.5*0.5


# In[36]:


0.75 + 1.5 * 0.5


# In[37]:


numeric_cols = data.select_dtypes(include=[np.number])


Q1 = numeric_cols.quantile(0.25)
Q3 = numeric_cols.quantile(0.75)
IQR = Q3 - Q1

# Filter out outliers        # 0.25-1.5*0.5 = -0.5                      #  0.75 + 1.5 * 0.5 = 1.5

data_cleaned = data[~((numeric_cols < (Q1 - 1.5 * IQR)) | (numeric_cols > (Q3 + 1.5 * IQR))).any(axis=1)]


plt.figure(figsize=(20, 6))


plt.subplot(1, 2, 1)
numeric_cols.boxplot()
plt.title("Before Outlier Removal")



plt.tight_layout()
plt.show()


# In[38]:


plt.figure(figsize=(20, 6))


plt.subplot(1, 2, 2)
data_cleaned.select_dtypes(include=[np.number]).boxplot()
plt.title("After Outlier Removal")

plt.tight_layout()
plt.show()


# In[39]:


data_cleaned.shape


# In[40]:


data_cleaned.head()


# In[ ]:





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

# In[41]:


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

# In[42]:


import pandas as pd
import numpy as np
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


# In[ ]:





# # 5: One-Hot Encoding
# 

# In[43]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler



data.head(2)


# In[44]:


data["Hours Studied"].unique()


# In[45]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler





cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']


data1 = pd.get_dummies(cat_features)
data1


# In[46]:


data1.info()


# In[47]:


cat_features


# In[48]:


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


# In[49]:


data.columns


# In[50]:


scaled_data.columns


# In[ ]:





# In[51]:


data1.head()


# In[ ]:





# # 6: Data Reduction

# Dimensionality Reduction
# -
# PCA (Principal Component Analysis)

# In[52]:


scaled_data.shape


# In[53]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA





cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']
numeric_features = [feature for feature in data.columns if data[feature].dtype != 'O']


numeric_means = data[numeric_features].mean()
data[numeric_features] = data[numeric_features].fillna(numeric_means)


data = pd.get_dummies(data, columns=cat_features)


scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features])


pca_2 = PCA(n_components=2)
data_pca_2 = pca_2.fit_transform(data)


plt.figure(figsize=(14, 6))


plt.subplot(1, 2, 1)
plt.scatter(data[numeric_features[0]], data[numeric_features[1]], alpha=0.5)
plt.title('Original Data')
plt.xlabel(numeric_features[0])
plt.ylabel(numeric_features[1])


plt.subplot(1, 2, 2)
plt.scatter(data_pca_2[:, 0], data_pca_2[:, 1], alpha=0.5)
plt.title('PCA Transformed Data')
plt.xlabel('Principal Component 1')
plt.ylabel('Principal Component 2')

plt.tight_layout()
plt.show()


# In[54]:


type(data_pca_2)


# In[55]:


data_pca_2.ndim


# In[56]:


data_pca_2.shape


# # 7: Handling Imbalanced Data
#     
# - Resampling Techniques
# - Oversampling

# In[81]:


import pandas as pd
import numpy as np
import imblearn
import category_encoders
import packaging.version
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.decomposition import PCA
from imblearn.over_sampling import SMOTE
import matplotlib.pyplot as plt


data = pd.read_csv('Student_Performance.csv')


data.fillna(data.mean(numeric_only=True), inplace=True)


target = data['Hours Studied']
data = data.drop(columns=['Hours Studied'])

cat_features = [col for col in data.columns if data[col].dtype == 'O']
numeric_features = [col for col in data.columns if data[col].dtype != 'O']

data = pd.get_dummies(data, columns=cat_features)


scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features])


if target.dtype == 'O':
    le = LabelEncoder()
    target = le.fit_transform(target)
elif target.dtype == 'float':
    target = (target > 0.5).astype(int)


print("Before SMOTE:", data.shape, target.shape)


smote = SMOTE(random_state=42)
X_resampled, y_resampled = smote.fit_resample(data, target)


resampled_df = pd.concat([
    pd.DataFrame(X_resampled, columns=data.columns),
    pd.DataFrame(y_resampled, columns=['Hours Studied'])
], axis=1)

print("After SMOTE:", resampled_df.shape)
resampled_df.head()


# In[82]:


resampled_df['Hours Studied'].value_counts(True)


# In[83]:


resampled_df.shape


# In[84]:


print(resampled_df.columns)
print(list(resampled_df.columns))


# In[85]:


print(data.columns)
print(list(data.columns))


# Undersampling
# -

# In[86]:


import pandas as pd
import numpy as np
import imblearn
import category_encoders
import packaging.version
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.decomposition import PCA
from imblearn.over_sampling import SMOTE
from imblearn.under_sampling import RandomUnderSampler
import matplotlib.pyplot as plt


data = pd.read_csv('Student_Performance.csv')


data.fillna(data.mean(numeric_only=True), inplace=True)


target = data['Hours Studied']
data = data.drop(columns=['Hours Studied'])

cat_features = [col for col in data.columns if data[col].dtype == 'O']
numeric_features = [col for col in data.columns if data[col].dtype != 'O']

data = pd.get_dummies(data, columns=cat_features)


scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features])


if target.dtype == 'O':
    le = LabelEncoder()
    target = le.fit_transform(target)
elif target.dtype == 'float':
    target = (target > 0.5).astype(int)


print("Before undersampling:", data.shape, target.shape)


rus = RandomUnderSampler(random_state=42)
X_resampled, y_resampled = rus.fit_resample(data, target)


resampled_df = pd.concat([
    pd.DataFrame(X_resampled, columns=data.columns),
    pd.DataFrame(y_resampled, columns=['Hours Studied'])
], axis=1)

print("After undersampling:", resampled_df.shape)
resampled_df.head()


# In[88]:


resampled_df['Hours Studied'].value_counts()


# In[89]:


resampled_df.shape


# # Target Encoder

# In[90]:


import pandas as pd
from category_encoders import TargetEncoder

# Example dataset
data = {'animal': ['cat', 'dog', 'mouse', 'dog', 'cat'], 'target': [1, 0, 1, 0, 1]}
df = pd.DataFrame(data)

target_encoder = TargetEncoder(cols=['animal'])
target_encoded = target_encoder.fit_transform(df['animal'], df['target'])
print(target_encoded)


# # 8: Splitting Data

# In[93]:


from sklearn.model_selection import train_test_split


X = resampled_df.drop('Hours Studied', axis=1)
y = resampled_df['Hours Studied']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)


# In[94]:


X_train.shape, X_test.shape, y_train.shape, y_test.shape


# # 9.Regression
# 
# 

# In[96]:


from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score
import pandas as pd

# Assuming 'data' is your fully preprocessed DataFrame
X = resampled_df.drop('Performance Index', axis=1)
y = resampled_df['Performance Index']

# Train/test split


# Initialize and train model
lr_model = LinearRegression()
lr_model.fit(X_train, y_train)

# Predict on test set
y_pred = lr_model.predict(X_test)

# Evaluation
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

print("📊 Linear Regression Evaluation:")
print(f"Mean Squared Error: {mse:.2f}")
print(f"R² Score: {r2:.2f}")

# Show coefficients
coeff_df = pd.DataFrame({'Feature': X.columns, 'Coefficient': lr_model.coef_})
print("\n🔍 Feature Coefficients:")
print(coeff_df)


# # Prediction

# In[102]:


# Correct feature and target separation
X = resampled_df.drop('Performance Index', axis=1)  # features
y = resampled_df['Performance Index']               # target
from sklearn.model_selection import train_test_split

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
from sklearn.linear_model import LinearRegression

lr_model = LinearRegression()
lr_model.fit(X_train, y_train)
# This must match the feature columns used in X
new_data = pd.DataFrame({
    'Previous Scores': [75],
    'Sleep Hours': [6],
    'Sample Question Papers Practiced': [5],
    'Extracurricular Activities_No': [0],
    'Extracurricular Activities_Yes': [1],
    'Hours Studied': [3],
})

# Ensure same column order
new_data = new_data[X.columns]

# Predict
prediction = lr_model.predict(new_data)
print(f"🎯 Predicted Performance Index: {prediction[0]:.2f}")


# In[ ]:




