#!/usr/bin/env python
# coding: utf-8

# # Problem Description: Model to find the Best seller Supplements based on various features.
# 

# # Data Preprocessing Steps

# In[1]:


import matplotlib.pyplot as plt 
import seaborn as sns 

color = sns.color_palette()

import numpy as np 
import pandas as pd


# # 1: Reading Data

# In[2]:


data = pd.read_csv('Supplement.csv')

data.head()


# In[3]:


data.head(2)


# In[4]:


data.head(10)


# In[5]:


data.tail()


# In[6]:


data.shape


# In[7]:


data.tail(10)


# In[8]:


data.sample()


# In[9]:


data.sample(10)


# In[10]:


data.info()


# In[11]:


data.describe()


# # 2: Data Cleaning

# Handling Missing Values
# -
# - Imputation: Filling missing values with mean.

# In[12]:


data.isnull().sum()


# In[13]:


import pandas as pd
import numpy as np

numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])

numeric_cols.fillna(numeric_cols.mean(), inplace=True)   

data = pd.concat([numeric_cols, non_numeric_cols], axis=1)

missing_values = data.isnull().sum()
print(missing_values)



# In[14]:


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


# In[15]:


data.shape


# Removal: Deleting rows with missing values.
# -

# In[16]:


data.isnull().sum()


# In[17]:


data.shape


# In[18]:


data.dropna(inplace=True)

missing_values = data.isnull().sum()
print(missing_values)


# In[19]:


data.shape


# In[ ]:





# Removing Duplicates
# -

# In[20]:


data.drop_duplicates(inplace=True)
data.shape


# # 3: Outlier Detection and Removal

# In[21]:


data.describe()


# In[22]:


0.25-1.5*0.5


# In[23]:


0.75 + 1.5 * 0.5


# In[24]:


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


# In[25]:


plt.figure(figsize=(20, 6))

plt.subplot(1, 2, 2)
data_cleaned.select_dtypes(include=[np.number]).boxplot()
plt.title("After Outlier Removal")

plt.tight_layout()
plt.show()


# In[26]:


data_cleaned.shape


# In[27]:


data_cleaned.head()


# In[ ]:





# # 4. Data Transformation
# 

# In[28]:


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

# In[29]:


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

# In[30]:


data.head(2)


# In[31]:


data["Best Seller"].unique()


# In[ ]:





# In[32]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']

data1 = pd.get_dummies(cat_features)
data1


# In[33]:


data1.info()


# In[34]:


cat_features


# In[35]:


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


# In[36]:


data.columns


# In[37]:


scaled_data.columns


# In[38]:


data1.head()


# In[ ]:





# # 6: Data Reduction

# Dimensionality Reduction
# -
# PCA (Principal Component Analysis)

# In[39]:


scaled_data.shape


# In[40]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA

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


# In[41]:


type(data_pca)


# In[42]:


data_pca.ndim


# In[43]:


data_pca.shape


# In[ ]:





# # 7: Handling Imbalanced Data
#     
# - Resampling Techniques
# - Oversampling

# In[44]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.decomposition import PCA
from imblearn.over_sampling import SMOTE
import matplotlib.pyplot as plt

data.fillna(data.mean(numeric_only=True), inplace=True)

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']
numeric_features = [feature for feature in data.columns if data[feature].dtype != 'O']

data = pd.get_dummies(data, columns=cat_features)

scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features].values)

if data['Best Seller'].dtype != 'int64' and data['Best Seller'].dtype != 'bool':
    
    data['Best Seller'] = (data['Best Seller'] > 0.5).astype(int)

X = data.drop(columns=['Best Seller'])  
y = data['Best Seller']

if y.dtype == 'O':
    le = LabelEncoder()
    y = le.fit_transform(y)

print(X.shape, y.shape)

smote = SMOTE(random_state=42)
X_resampled, y_resampled = smote.fit_resample(X, y)

data_resampled = pd.concat([pd.DataFrame(X_resampled, columns=X.columns), pd.DataFrame(y_resampled, columns=['Best Seller'])], axis=1)
data_resampled.head()


# In[45]:


data_resampled['Best Seller'].value_counts(True)


# In[46]:


data_resampled.shape


# Undersampling
# -

# In[47]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.decomposition import PCA
from imblearn.over_sampling import SMOTE
import matplotlib.pyplot as plt

data.fillna(data.mean(numeric_only=True), inplace=True)

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']
numeric_features = [feature for feature in data.columns if data[feature].dtype != 'O']

data = pd.get_dummies(data, columns=cat_features)

scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features].values)

if data['Best Seller'].dtype != 'int64' and data['Best Seller'].dtype != 'bool':

    data['Best Seller'] = (data['Best Seller'] > 0.5).astype(int)

X = data.drop(columns=['Best Seller'])  
y = data['Best Seller']  

if y.dtype == 'O':
    le = LabelEncoder()
    y = le.fit_transform(y)

print(X.shape, y.shape)

from imblearn.under_sampling import RandomUnderSampler

rus = RandomUnderSampler()
X_resampled, y_resampled = rus.fit_resample(X, y)

data_resampled = pd.concat([pd.DataFrame(X_resampled, columns=X.columns), pd.DataFrame(y_resampled, columns=['Best Seller'])], axis=1)
data_resampled.head()


# In[48]:


data_resampled['Best Seller'].value_counts()


# In[49]:


data_resampled.shape


# # Target Encoder

# In[50]:


import pandas as pd

target = 'Best Seller'  
categorical_cols = data.select_dtypes(include=['object']).columns  

for col in categorical_cols:
    target_mean = data.groupby(col)[target].mean()
    data[col + '_target_enc'] = data[col].map(target_mean)

data = data.drop(columns=categorical_cols)

print(data.head())


# In[ ]:





# # 8: Splitting Data

# In[51]:


from sklearn.model_selection import train_test_split
import pandas as pd

print(data.columns)
 
X = data.drop('Best Seller', axis=1)
y = data['Best Seller']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)


# In[52]:


X_train.shape, X_test.shape, y_train.shape, y_test.shape


# # Classification

# ## Loading Libraries

# In[53]:


# **DATA PROCESSING**

import pandas as pd # Data Processing
import numpy as np # Array Processing
import os # Data Importing

# **DATA ANALYSIS**

import matplotlib.pyplot as plt # Plots 
import seaborn as sns # Graphs

# **PRE PROCESSING**

from sklearn.preprocessing import FunctionTransformer  # Transforming of Data
from sklearn.preprocessing import OneHotEncoder # Data Encoding
from sklearn.preprocessing import StandardScaler # Data Scaling
from imblearn.over_sampling import RandomOverSampler # Data OverSampling
from sklearn.decomposition import PCA # Principal Component Analysis

# **MODELS** 

from sklearn.neighbors import KNeighborsClassifier 
from sklearn.linear_model import LogisticRegression
from sklearn.naive_bayes import GaussianNB
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier

# **NERURAL NETWORKS**

import tensorflow
from tensorflow import keras
from tensorflow.keras import Sequential
from tensorflow.keras.layers import Dense

# **METRICS**

from sklearn.metrics import accuracy_score # Model Classification Report



# # Reading Data

# In[58]:


import pandas as pd 
import numpy as np 
import os

Supplement = pd.read_csv("Supplement.csv")


# In[60]:


Supplement.head()


# # Exploring Data

# In[18]:


Supplement.shape


# In[19]:


Supplement.ndim


# In[64]:


Supplement["Best Seller"].value_counts().rename("count"),
Supplement["Best Seller"].value_counts(True).rename('%').mul(100)


# In[66]:


Supplement["Best Seller"].value_counts()


# In[67]:


sns.countplot(data=stroke_data , x='Best Seller')
plt.title('Price')


# In[69]:


Supplement.info()


# In[70]:


Supplement.describe()


# # Features name

# In[71]:


Supplement.columns


# In[72]:


Supplement["Best Seller"].value_counts()


# # Missing Values

# In[73]:


print('Missing data sum :')
print(Supplement.isnull().sum())

print('\nMissing data percentage (%):')
print(Supplement.isnull().sum()/Supplement.count()*100)


# # Seperate Categorical and Numerical Features

# In[74]:


cat_features = [feature for feature in Supplement.columns if Supplement[feature].dtypes == 'O']
print('Number of categorical variables: ', len(cat_features))
print('*'*80)
print('Categorical variables column name:',cat_features)


# In[75]:


numerical_features = [feature for feature in Supplement.columns if Supplement[feature].dtypes != 'O']
print('Number of numerical variables: ', len(numerical_features))
print('*'*80)
print('Numerical Variables Column: ',numerical_features)


# # Checking Duplicating Values

# In[30]:


Supplement.duplicated().sum()


# In[76]:


Supplement['Price'].unique()


# In[77]:


Supplement['Price'].nunique()


# In[78]:


Supplement['Price'].sample(10)


# In[79]:


Supplement['Revenue'].unique()


# In[81]:


Supplement['Discount'].unique()


# In[82]:


Supplement['Units Sold'].unique()


# In[83]:


Supplement['Date'].unique()


# In[84]:


Supplement['Units Returned'].unique()


# In[86]:


Supplement['Best Seller'].unique()


# In[87]:


Supplement.columns


# In[88]:


Supplement['Best Seller'].nunique()


# In[89]:


Supplement['Best Seller'].unique()


# In[90]:


corr = Supplement.select_dtypes(include='number').corr()
Supplement.dtypes
plt.figure(figsize=(10, 8))
sns.heatmap(data=corr, annot=True, cmap='Spectral').set(title="Correlation Matrix")
plt.show()


# In[91]:


corr_matrix = Supplement.select_dtypes(include='number').corr().round(2)
corr_matrix


# In[92]:


mask = np.triu(np.ones_like(corr_matrix, dtype=bool))

plt.figure(figsize=(10,10))
sns.heatmap(corr_matrix, center=0, vmin=-1, vmax=1, mask=mask, annot=True, cmap='BrBG')
plt.show()


# In[93]:


cat_features = [feature for feature in Supplement.columns if Supplement[feature].dtypes == 'O']
print('Number of categorical variables: ', len(cat_features))
print('*'*80)
print('Categorical variables column name:',cat_features)


# In[94]:


numerical_features = [feature for feature in Supplement.columns if Supplement[feature].dtypes != 'O']
print('Number of numerical variables: ', len(numerical_features))
print('*'*80)
print('Numerical Variables Column: ',numerical_features)


# # Visualizing Categorical Features

# In[95]:


for col in numerical_features:
    plt.figure(figsize=(6, 3), dpi=100)
    sns.barplot(data=Supplement, x='Best Seller', y=col, hue='Best Seller', palette='gist_rainbow_r')
    plt.title(f'{col} by Supplement')
    plt.xlabel('Supplement')
    plt.ylabel(col)
    plt.tight_layout()
    plt.show()


# # Barplot of numerical features:

# In[97]:


## Plotting barplots of numerical features grouped by salary
for col in numerical_features:
    plt.figure(figsize=(6, 3), dpi=100)
    sns.barplot(data=Supplement, x='Best Seller', y=col, hue='Best Seller', palette='gist_rainbow_r')
    plt.title(f'{col} by Supplement')
    plt.xlabel('Supplement')
    plt.ylabel(col)
    plt.tight_layout()
    plt.show()



# # Handling Missing Values

# In[98]:


Supplement.head()


# In[99]:


Supplement.isnull().sum()


# In[100]:


Supplement["Price"] = Supplement["Price"].fillna(Supplement["Price"].mode()[0])


# In[101]:


Supplement.isnull().sum()


# # Dropping 

# In[102]:


train  = Supplement.drop(['Date'],axis=1)
train


# In[103]:


train.columns


# In[104]:


train.shape


# In[105]:


train.info()


# In[106]:


train_data_cat = train.select_dtypes("object")
train_data_num = train.select_dtypes("number")


# In[107]:


train_data_cat.head(3)


# In[108]:


train_data_num.head(3)


# # Converting categorical features into numerical

# In[109]:


train_data_cata_encoded=pd.get_dummies(train_data_cat, columns=train_data_cat.columns.to_list())
train_data_cata_encoded.head()


# In[110]:


data=pd.concat([train_data_cata_encoded,train_data_num],axis=1,join="outer")
data.head()


# # seperate dependant and independant feature

# In[112]:


# Create a target column from one-hot encoded salary columns
data['Best Seller'] = data['Best Seller']  # This will be 1 if >50K, else 0

# Now separate features and target
y = data['Best Seller']
X = data.drop(['Best Seller'], axis=1)


# In[113]:


print(y.shape)
print(X.shape)


# # scailing the data

# In[114]:


from sklearn.preprocessing import StandardScaler

sc = StandardScaler()
X_scaled = sc.fit_transform(X)


# In[115]:


X


# # Splitting data into Training and Testing

# In[117]:


#Importing our ML toolkit
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.pipeline import Pipeline
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, confusion_matrix,classification_report
from sklearn.svm import SVC
import pickle

from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import AdaBoostClassifier
from sklearn.ensemble import GradientBoostingClassifier
from xgboost import XGBClassifier, plot_importance
from sklearn.model_selection import GridSearchCV, cross_val_score, StratifiedKFold, learning_curve


# # Splitting the dataset
# training data 70%
# testing data 30%

# In[118]:


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=7)


# In[119]:


X_train.shape, X_test.shape


# # Building Classifiers

# In[120]:


accuracy = {}


# # Logistic Regression

# In[121]:


scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# train the model
lr = LogisticRegression(max_iter=200)
lr.fit(X_train_scaled, y_train)
y_pred1 = lr.predict(X_test_scaled)

# evaluate
accuracy = {}
print(accuracy_score(y_test, y_pred1))
accuracy[str(lr)] = accuracy_score(y_test, y_pred1)*100


# # Confusion Matrix

# In[122]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred1)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# # Classification Report

# In[123]:


print(classification_report(y_test,y_pred1))


# In[124]:


from sklearn.metrics import classification_report
print(classification_report(y_test,y_pred1, zero_division=1))  # sets precision/recall to 1 instead of 0


# # Predicting

# In[125]:


y_pred_test = lr.predict(X_test)

test = pd.DataFrame({
    'Actual':y_test,
    'Y test predicted':y_pred_test
})


# In[126]:


test.sample(10)


# # DecisionTreeClassifier

# In[127]:


dtc = DecisionTreeClassifier(max_depth=3)
dtc.fit(X_train, y_train)
y_pred2 = dtc.predict(X_test)
print(accuracy_score(y_test, y_pred2))
accuracy[str(dtc)] = accuracy_score(y_test, y_pred2)*100


# In[128]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred2)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# In[129]:


print(classification_report(y_test,y_pred2))


# In[130]:


y_pred_test = dtc.predict(X_test)

test = pd.DataFrame({
    'Actual':y_test,
    'Y test predicted':y_pred_test
})


# In[131]:


test.head(5)


# In[132]:


rfc = RandomForestClassifier(max_depth=5)
rfc.fit(X_train, y_train)
y_pred3 = rfc.predict(X_test)
print(accuracy_score(y_test, y_pred3))
accuracy[str(rfc)] = accuracy_score(y_test, y_pred3)*100


# In[133]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred3)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# In[134]:


gbc = GradientBoostingClassifier(n_estimators=100, learning_rate=0.1)
gbc.fit(X_train, y_train)
y_pred4 = gbc.predict(X_test)
print(accuracy_score(y_test, y_pred4))
accuracy[str(gbc)] = accuracy_score(y_test, y_pred4)*100


# In[135]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred4)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# # SVM

# In[136]:


svc = SVC()
svc.fit(X_train, y_train)
y_pred5 = svc.predict(X_test)
print(accuracy_score(y_test, y_pred5))
accuracy[str(svc)] = accuracy_score(y_test, y_pred5)*100


# In[137]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred5)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# In[138]:


accuracy


# # Conclusion

# In this project, a Support Vector Machine (SVM) classifier was applied to predict the target classes. The confusion matrix reveals that the model correctly predicted 943 out of 944 negative class instances (class 0), showing exceptionally high accuracy for this category. However, for the positive class (class 1), the model only correctly predicted 26 instances, while it misclassified 346 as negative.
# 
# This indicates that while the SVM model performs very well in identifying the majority class (class 0), it struggles significantly with the minority class (class 1). This imbalance is a common challenge in classification tasks involving skewed datasets.
# 
# From the confusion matrix:
# 
# True Positives (TP): 26
# 
# True Negatives (TN): 943
# 
# False Positives (FP): 1
# 
# False Negatives (FN): 346
# 
# These results suggest:
# 
# High precision for predicting class 1 (since FP is low),
# 
# But very low recall for class 1 (most actual positives are missed).

# # Handling this data using SMOTE

# In[139]:


from imblearn.over_sampling import SMOTE


# In[140]:


smote = SMOTE()

X1, y1 = smote.fit_resample(X, y)

X1.shape, y1.shape 

#print(y_oversample.value_counts())


# In[141]:


df=pd.DataFrame(X1)
df.head()


# # Splitting the oversampling data

# In[142]:


X_train, X_test, y_train, y_test = train_test_split(X1,y1, test_size=0.3 ,shuffle = True,random_state = 3)


# In[143]:


print(X_train.shape)
print(X_test.shape)
print(y_train.shape)
print(y_test.shape)


# In[ ]:





# In[144]:


lr = LogisticRegression(max_iter=200)
lr.fit(X_train, y_train)
y_pred1 = lr.predict(X_test)
print(accuracy_score(y_test, y_pred1))
accuracy[str(lr)] = accuracy_score(y_test, y_pred1)*100


# In[145]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred1)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# In[146]:


print(classification_report(y_test,y_pred1))


# In[147]:


y_pred_test = lr.predict(X_test)

test = pd.DataFrame({
    'Actual':y_test,
    'Y test predicted':y_pred_test
})


# In[148]:


test.head()


# In[149]:


knn_model = KNeighborsClassifier(n_neighbors=3)
knn_model.fit(X_train,y_train)
knn_predict = knn_model.predict(X_test)
print(accuracy_score(y_test, knn_predict))
accuracy[str(lr)] = accuracy_score(y_test, knn_predict)*100


# In[150]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,knn_predict)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# In[151]:


print(classification_report(y_test,knn_predict))


# In[152]:


y_pred_test = knn_model.predict(X_test)

test = pd.DataFrame({
    'Actual':y_test,
    'Y test predicted':y_pred_test
})


# In[153]:


test.sample(10)


# # Deep Learning

# In[154]:


import tensorflow as tf
from tensorflow import keras

#es=tf.keras.callbacks.EarlyStopping(
#    min_delta=0.001,
#    patience=10,
#    restore_best_weights=True)


# # Create Neural Network
# 
# 
# 
# 
# 
# 
# Creating sequnetial ANN Network
# Creating 5 layers Network
# Activation is "Relu"
# Last layer is output layer
# Problem is binary classification thats way output node is 1 and activation is "sigmoid"

# In[183]:


model=keras.Sequential([
    keras.layers.Dense(4800,input_shape=[37], activation='relu'),
    keras.layers.Dense(2000, activation='relu'),
    keras.layers.Dense(1000, activation='relu'),
    keras.layers.Dense(1000, activation='relu'), 
    keras.layers.Dense(1,activation="sigmoid")
])
model.summary()


# compile method takes three arguments
# loss >> binary crossentropy
# optimizer >> adam
# matrix >> accuracy

# In[184]:


model.compile(loss='binary_crossentropy', optimizer='adam',metrics=['accuracy'])


# 
# epochs = 100
# batch size = 100

# In[185]:


from keras.models import Sequential
from keras.layers import Dense

input_dim = X_train.shape[1]  # This will be 99 in your case

model = Sequential()
model.add(Dense(64, input_shape=(input_dim,), activation='relu'))
model.add(Dense(32, activation='relu'))
model.add(Dense(1, activation='sigmoid'))  # use softmax if multi-class


# In[186]:


import numpy as np

X_train = X_train.astype(np.float32)
X_test = X_test.astype(np.float32)

y_train = y_train.astype(np.float32)
y_test = y_test.astype(np.float32)

model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
model.fit(X_train, y_train, epochs=10, batch_size=100)


# In[187]:


model.evaluate(X_test, y_test)


# In[188]:


y_pred=model.predict(X_test).flatten()
y_pred=np.round(y_pred)

y_pred[:11]
y_test[:11]

from sklearn.metrics import classification_report

print(classification_report(y_test, y_pred))


# In[189]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test, y_pred)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# .Creating sequnetial ANN Network
# .Creating 5 layers Network
# .Activation is "Relu"
# .Adding Dropout layer
# .Last layer is output layer
# .Problem is binary classification thats way output node is 1 and activation is "sigmoid"

# from keras.models import Sequential
# from keras.layers import Dense,Dropout
# from tensorflow.keras.optimizers import Adam
# from tensorflow.keras.losses import BinaryCrossentropy
# model = Sequential()
# model.add(Dense(512,activation='relu',input_shape=(21,)))
# model.add(Dense(512,activation='relu'))
# model.add(Dropout(0.5))
# model.add(Dense(256,activation='relu'))
# model.add(Dense(256,activation='relu'))
# model.add(Dropout(0.5))
# model.add(Dense(128,activation='relu'))
# model.add(Dense(128,activation='relu'))
# model.add(Dropout(0.5))
# model.add(Dense(1,activation = 'sigmoid'))
# model.summary()

# In[190]:


from tensorflow.keras.optimizers import Adam

model.compile(loss="binary_crossentropy", optimizer=Adam(learning_rate=0.0001), metrics=['accuracy'])




# In[191]:


from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

# Clear previous model
model = Sequential()

# Fix input shape to match your data
model.add(Dense(64, activation='relu', input_shape=(37,)))
model.add(Dense(32, activation='relu'))
model.add(Dense(1, activation='sigmoid'))  # Use sigmoid for binary classification

model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])


# In[192]:


from tensorflow.keras.callbacks import EarlyStopping

# Define callback (you can adjust patience and monitor as needed)
cb = EarlyStopping(monitor='val_loss', patience=3, restore_best_weights=True)

model.fit(X_train, y_train, epochs=10, batch_size=100, validation_split=0.30, callbacks=cb)


# In[193]:


print(X_train.shape)


# # Testing the model

# In[194]:


model.evaluate(X_test, y_test)


# In[195]:


y_pred=model.predict(X_test).flatten()
y_pred=np.round(y_pred)

y_pred[:11]
y_test[:11]

from sklearn.metrics import classification_report

print(classification_report(y_test, y_pred))


# # Confusion Matrix

# In[196]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test, y_pred)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# # THE END.

# In[ ]:




