#!/usr/bin/env python
# coding: utf-8

# # Data description 

# This dataset provides salary data based on years of experience, education level, and job role. It can be used for salary prediction models, regression analysis, and workforce analytics. The dataset includes realistic salary variations based on industry trends.

# # Data Preprocessing Steps

# In[3]:


import matplotlib.pyplot as plt 
import seaborn as sns 

color = sns.color_palette()

import numpy as np 
import pandas as pd


# # 1: Reading Data

# In[7]:


data = pd.read_csv('salary_prediction_updated_dataset.csv')

data.head()


# In[9]:


data.head(2)


# In[13]:


data.Salary.nunique()


# In[9]:


data.head(10)


# In[9]:


data.tail()


# In[11]:


data.shape


# In[11]:


data.tail(10)


# In[15]:


data.sample()


# In[17]:


data.sample(10)


# In[19]:


data.info()


# In[21]:


data.describe()


# # 2: Data Cleaning

# Handling Missing Values
# -
# - Imputation: Filling missing values with mean.

# In[15]:


data.isnull().sum()


# In[27]:


import pandas as pd
import numpy as np

numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])

numeric_cols.fillna(numeric_cols.mean(), inplace=True)   

data = pd.concat([numeric_cols, non_numeric_cols], axis=1)

missing_values = data.isnull().sum()
print(missing_values)


# In[29]:


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


# In[31]:


data.shape


# Removal: Deleting rows with missing values.
# -

# In[33]:


data.isnull().sum()


# In[35]:


data.shape


# In[37]:


data.dropna(inplace=True)

missing_values = data.isnull().sum()
print(missing_values)


# In[39]:


data.shape


# In[ ]:





# Removing Duplicates
# -

# In[43]:


data.drop_duplicates(inplace=True)
data.shape


# # 3: Outlier Detection and Removal

# In[45]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv('salary_prediction_updated_dataset.csv')

data.describe()


# In[47]:


0.25-1.5*0.5


# In[49]:


0.75 + 1.5 * 0.5


# In[51]:


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


# In[53]:


plt.figure(figsize=(20, 6))

plt.subplot(1, 2, 2)
data_cleaned.select_dtypes(include=[np.number]).boxplot()
plt.title("After Outlier Removal")

plt.tight_layout()
plt.show()


# In[55]:


data_cleaned.shape


# In[57]:


data_cleaned.head()


# In[ ]:





# # 4. Data Transformation
# 

# In[123]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler

data = pd.read_csv('salary_prediction_updated_dataset.csv')

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

# In[61]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler

data = pd.read_csv('salary_prediction_updated_dataset.csv')

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

# In[63]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler

data = pd.read_csv('salary_prediction_updated_dataset.csv')
data.head(2)


# In[65]:


data["Education Level"].unique()


# In[ ]:





# In[67]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler

data = pd.read_csv('salary_prediction_updated_dataset.csv')

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']

data1 = pd.get_dummies(cat_features)
data1


# In[69]:


data1.info()


# In[71]:


cat_features


# In[73]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler

data = pd.read_csv('salary_prediction_updated_dataset.csv')

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']

data1 = pd.get_dummies(data, columns=cat_features)

scaled_data = pd.concat([data, data1], axis=1)

print(scaled_data.shape)
print()
print('*' * 70)

scaled_data.head()


# In[75]:


data.columns


# In[77]:


scaled_data.columns


# In[79]:


data1.head()


# In[ ]:





# # 6: Data Reduction

# Dimensionality Reduction
# -
# PCA (Principal Component Analysis)

# In[81]:


scaled_data.shape


# In[83]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA

data = pd.read_csv('salary_prediction_updated_dataset.csv')

data.fillna(data.mean(numeric_only=True), inplace=True)

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']
numeric_features = [feature for feature in data.columns if data[feature].dtype != 'O']

data = pd.get_dummies(data, columns=cat_features)

scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features].values)

pca = PCA(n_components=4)
data_pca = pca.fit_transform(data)

print(data_pca.shape)
print(data_pca[:5])  

plt.figure(figsize=(14, 6))

plt.subplot(1, 2, 1)
plt.scatter(data[numeric_features[0]], data[numeric_features[1]], alpha=0.5)
plt.title('Original Data')
plt.xlabel(numeric_features[0])
plt.ylabel(numeric_features[1])

pca = PCA(n_components=4) 
data_pca = pca.fit_transform(data)

plt.subplot(1, 2, 2)
plt.scatter(data_pca[:, 0], data_pca[:, 1], alpha=0.5)
plt.title('PCA Transformed Data')
plt.xlabel('Principal Component 1')
plt.ylabel('Principal Component 2')

plt.tight_layout()
plt.show()


# In[91]:


type(data_pca)


# In[93]:


data_pca.ndim


# In[95]:


data_pca.shape


# In[ ]:





# # 7: Handling Imbalanced Data
#     
# - Resampling Techniques
# - Oversampling

# In[99]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.decomposition import PCA
from imblearn.over_sampling import SMOTE
import matplotlib.pyplot as plt

data = pd.read_csv('salary_prediction_updated_dataset.csv')

data.fillna(data.mean(numeric_only=True), inplace=True)

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']
numeric_features = [feature for feature in data.columns if data[feature].dtype != 'O']

data = pd.get_dummies(data, columns=cat_features)

scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features].values)

if data['Education Level_PhD'].dtype != 'int64' and data['Education Level_PhD'].dtype != 'bool':

    data['Education Level_PhD'] = (data['Education Level_PhD'] > 0.5).astype(int)

X = data.drop(columns=['Education Level_PhD'])  
y = data['Education Level_PhD']

if y.dtype == 'O':
    le = LabelEncoder()
    y = le.fit_transform(y)

print(X.shape, y.shape)

smote = SMOTE(random_state=42)
X_resampled, y_resampled = smote.fit_resample(X, y)

data_resampled = pd.concat([pd.DataFrame(X_resampled, columns=X.columns), pd.DataFrame(y_resampled, columns=['Education Level_PhD'])], axis=1)
data_resampled.head()


# In[101]:


data_resampled['Education Level_PhD'].value_counts(True)


# In[103]:


data_resampled.shape


# Undersampling
# -

# In[105]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.decomposition import PCA
from imblearn.over_sampling import SMOTE
import matplotlib.pyplot as plt
data = pd.read_csv('salary_prediction_updated_dataset.csv')

data.fillna(data.mean(numeric_only=True), inplace=True)

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']
numeric_features = [feature for feature in data.columns if data[feature].dtype != 'O']

data = pd.get_dummies(data, columns=cat_features)

scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features].values)

if data['Education Level_PhD'].dtype != 'int64' and data['Education Level_PhD'].dtype != 'bool':

    data['Education Level_PhD'] = (data['Education Level_PhD'] > 0.5).astype(int)

X = data.drop(columns=['Education Level_PhD'])  
y = data['Education Level_PhD']  

if y.dtype == 'O':
    le = LabelEncoder()
    y = le.fit_transform(y)

print(X.shape, y.shape)

from imblearn.under_sampling import RandomUnderSampler

rus = RandomUnderSampler()
X_resampled, y_resampled = rus.fit_resample(X, y)

data_resampled = pd.concat([pd.DataFrame(X_resampled, columns=X.columns), pd.DataFrame(y_resampled, columns=['Education Level_PhD'])], axis=1)
data_resampled.head()


# In[107]:


data_resampled['Education Level_PhD'].value_counts()


# In[109]:


data_resampled.shape


# # Target Encoder

# In[113]:


import pandas as pd

df = pd.read_csv('salary_prediction_updated_dataset.csv')

target = 'Salary'  
categorical_cols = df.select_dtypes(include=['object']).columns  

for col in categorical_cols:
    target_mean = df.groupby(col)[target].mean()
    df[col + '_target_enc'] = df[col].map(target_mean)

df = df.drop(columns=categorical_cols)

print(df.head())


# In[ ]:





# # 8: Splitting Data

# In[117]:


from sklearn.model_selection import train_test_split
import pandas as pd

data = pd.read_csv('salary_prediction_updated_dataset.csv')

print(data.columns)

X = data.drop('Education Level', axis=1)
y = data['Education Level']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)


# In[119]:


X_train.shape, X_test.shape, y_train.shape, y_test.shape


# # 9: Regression

# In[4]:


import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score

data = pd.read_csv('salary_prediction_updated_dataset.csv')

data_encoded = pd.get_dummies(data, drop_first=True)

X = data_encoded.drop('Education Level_PhD', axis=1)
y = data_encoded['Education Level_PhD']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

lr_model = LinearRegression()
lr_model.fit(X_train, y_train)

y_pred = lr_model.predict(X_test)

mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

print("📊 Linear Regression Evaluation:")
print(f"Mean Squared Error: {mse:.2f}")
print(f"R² Score: {r2:.2f}")

coeff_df = pd.DataFrame({'Feature': X.columns, 'Coefficient': lr_model.coef_})
print("\n🔍 Feature Coefficients:")
print(coeff_df)


# # 10:Prediction

# In[7]:


import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression

data = pd.read_csv("salary_prediction_updated_dataset.csv")

data_encoded = pd.get_dummies(data, drop_first=True)

if 'Education Level_PhD' not in data_encoded.columns:
    raise ValueError("Target column 'Education Level_PhD' does not exist after encoding.")

X = data_encoded.drop('Education Level_PhD', axis=1)
y = data_encoded['Education Level_PhD']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

lr_model = LinearRegression()
lr_model.fit(X_train, y_train)

new_data = pd.DataFrame([{
    'YearsExperience': 7,
    'Salary': 60000,
    'Job Role_Data Scientist': 1,
    'Job Role_Product Manager': 0,
    'Job Role_Software Engineer': 0,
    'Education Level_High School': 0,

}])

for col in X.columns:
    if col not in new_data.columns:
        new_data[col] = 0

new_data = new_data[X.columns]

prediction = lr_model.predict(new_data)
print(f"🎯 Predicted Probability of PhD Education Level: {prediction[0]:.2f}")


# In[ ]:




