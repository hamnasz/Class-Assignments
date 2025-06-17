#!/usr/bin/env python
# coding: utf-8

# # DATASET DESCRIPTION
# - This dataset contains patient records related to heart disease, with features such as age, gender, chest pain type, resting blood pressure, cholesterol levels, and more. It includes key indicators like maximum heart rate, ST depression, and thalassemia, making it suitable for predictive modeling in medical diagnostics. The target variable specifies whether a patient has heart disease, enabling classification tasks using models like Decision Tree, Random Forest, and ANN. With your expertise in data preprocessing and model training, you can apply feature selection techniques, scaling methods, and optimization strategies to enhance predictive accuracy
# - [Heart Disease Classification Dataset](https://www.kaggle.com/datasets/sumaiyatasmeem/heart-disease-classification-dataset)
# 

# # IMPORTING LIBRARIES

# In[54]:


import pandas as pd 
import numpy as np 
import os 
import matplotlib.pyplot as plt 
import seaborn as sns 
from sklearn.preprocessing import FunctionTransformer  
from sklearn.preprocessing import OneHotEncoder 
from sklearn.preprocessing import StandardScaler 
from imblearn.over_sampling import RandomOverSampler 
from sklearn.decomposition import PCA 
from sklearn.neighbors import KNeighborsClassifier 
from sklearn.linear_model import LogisticRegression
from sklearn.naive_bayes import GaussianNB
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier
import tensorflow
from tensorflow import keras
from tensorflow.keras import Sequential
from tensorflow.keras.layers import Dense
from sklearn.metrics import accuracy_score 


# # 2: Reading Data

# In[55]:


heart_data = pd.read_csv("C:/Users/Ayaan/Desktop/heart-2.csv")


# # EXPLORING DATA

# In[56]:


heart_data.head()


# In[57]:


heart_data.tail()


# In[58]:


heart_data.sample(3)


# In[59]:


heart_data.dtypes


# In[60]:


heart_data.info()


# In[61]:


heart_data.describe()


# In[62]:


heart_data.shape


# In[63]:


heart_data.columns


# In[64]:


heart_data["target"].unique()


# In[65]:


heart_data["target"].value_counts(normalize=True)


# In[66]:


heart_data["target"].value_counts().rename("count"),
heart_data["target"].value_counts(normalize=True).rename("%").mul(100)


# In[67]:


sns.countplot(data=heart_data, x="target")
plt.title("Heart Disease Target Distribution")


# # FEATURE NAME

# In[68]:


heart_data.columns


# # MISSING VALUES

# In[69]:


heart_data.isnull()


# In[70]:


heart_data.isnull().any()


# In[71]:


heart_data.isnull().sum()


# In[72]:


print("Missing data sum :")
print(heart_data.isnull().sum())

print("\nMissing data percentage (%):")
print(heart_data.isnull().sum() / heart_data.count() * 100)


# # SEPRATE CATEGORICAL AND NUMERICAL FEATURES

# In[73]:


cat_features = [feature for feature in heart_data.columns if heart_data[feature].nunique() < 10]
print("Number of categorical variables: ", len(cat_features))
print()
print("Categorical variables column name:", cat_features)


# In[74]:


cd = pd.DataFrame(cat_features)
cd.head()


# In[75]:


numerical_features = [feature for feature in heart_data.columns if heart_data[feature].dtypes != "O"]
print("Number of numerical variables: ", len(numerical_features))
print()
print("Numerical Variables Column: ", numerical_features)


# In[76]:


numerical_features


# In[77]:


cat_features


# # CHECKING DUBLICATE VALUES

# In[78]:


heart_data.duplicated()


# In[79]:


heart_data.duplicated().sum()


# In[80]:


heart_data["chol"].nunique()


# In[81]:


heart_data["chol"].unique()


# # VISUALIZUNG CATEGORICAL FEATURES

# In[82]:


for col in cat_features:
    plt.figure(figsize=(6, 3), dpi=100)
    sns.countplot(data=heart_data, x=col, hue="target", palette="gist_rainbow_r")
    plt.legend(loc=(1.05, 0.5))


# # Outlier Detection and Removal

# In[83]:


numeric_cols = heart_data.select_dtypes(include=[np.number])

Q1 = numeric_cols.quantile(0.25)
Q3 = numeric_cols.quantile(0.75)
IQR = Q3 - Q1

heart_data_cleaned = heart_data[~((numeric_cols < (Q1 - 1.5 * IQR)) | (numeric_cols > (Q3 + 1.5 * IQR))).any(axis=1)]

plt.figure(figsize=(20, 6))

plt.subplot(1, 2, 1)
numeric_cols.boxplot()
plt.title("Before Outlier Removal")

plt.subplot(1, 2, 2)
heart_data_cleaned.select_dtypes(include=[np.number]).boxplot()
plt.title("After Outlier Removal")

plt.tight_layout()
plt.show()


# # Data Transformation

# - Normalization

# In[85]:


from sklearn.preprocessing import MinMaxScaler
numeric_cols = heart_data.select_dtypes(include=[np.number])
non_numeric_cols = heart_data.select_dtypes(exclude=[np.number])

scaler = MinMaxScaler()
scaled_numeric_data = scaler.fit_transform(numeric_cols)

scaled_numeric_df = pd.DataFrame(scaled_numeric_data, columns=numeric_cols.columns)

scaled_data = pd.concat([scaled_numeric_df, non_numeric_cols.reset_index(drop=True)], axis=1)

print(scaled_data.shape)
print()
scaled_data.head()


# - Standardization

# In[86]:


from sklearn.preprocessing import StandardScaler

numeric_cols = heart_data.select_dtypes(include=[np.number])
non_numeric_cols = heart_data.select_dtypes(exclude=[np.number])

scaler = StandardScaler()
scaled_numeric_data = scaler.fit_transform(numeric_cols)

scaled_numeric_df = pd.DataFrame(scaled_numeric_data, columns=numeric_cols.columns)

scaled_data = pd.concat([scaled_numeric_df, non_numeric_cols.reset_index(drop=True)], axis=1)

print(scaled_data.shape)
print()
scaled_data.head()


# # FEATURE SELECTION

# In[87]:


from sklearn.feature_selection import SelectKBest, f_classif
from sklearn.model_selection import train_test_split

X = heart_data.drop(columns=["target"])
y = heart_data["target"]
selector = SelectKBest(score_func=f_classif, k=5)
X_selected = selector.fit_transform(X, y)


# # SPLITTING

# In[88]:


X_train, X_test, y_train, y_test = train_test_split(X_selected, y, test_size=0.2, random_state=42)


# # DECISION TREE

# In[89]:


from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import classification_report, confusion_matrix
import seaborn as sns
import matplotlib.pyplot as plt

clf = DecisionTreeClassifier(random_state=42)
clf.fit(X_train, y_train)
y_pred = clf.predict(X_test)


# ### CLASSIFICATION REPORT

# In[90]:


print(classification_report(y_test, y_pred))


# ### Confusion Matrix

# In[91]:


conf_matrix = confusion_matrix(y_test, y_pred)

plt.figure(figsize=(6, 4))
sns.heatmap(conf_matrix, annot=True, fmt="d", cmap="coolwarm")
plt.xlabel("Predicted")
plt.ylabel("Actual")
plt.title("Decision Tree Confusion Matrix")
plt.show()


# In[92]:


y_pred_test = clf.predict(X_test)

test = pd.DataFrame({
    "Actual": y_test,
    "Y test predicted": y_pred_test
})


# In[93]:


test.head(5)


# # RANDOM FOREST

# In[94]:


from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix
import seaborn as sns
import matplotlib.pyplot as plt
rf_clf = RandomForestClassifier(random_state=42)
rf_clf.fit(X_train, y_train)

y_pred_rf = rf_clf.predict(X_test)


# ### CLASSIFICATION REPORT

# In[95]:


print(classification_report(y_test, y_pred_rf))


# ### Confusion Matrix

# In[96]:


conf_matrix_rf = confusion_matrix(y_test, y_pred_rf)

plt.figure(figsize=(6, 4))
sns.heatmap(conf_matrix_rf, annot=True, fmt="d", cmap="coolwarm")
plt.xlabel("Predicted")
plt.ylabel("Actual")
plt.title("Random Forest Confusion Matrix")
plt.show()


# In[97]:


y_pred_test_rf = rf_clf.predict(X_test)

test_rf = pd.DataFrame({
    "Actual": y_test,
    "Y test predicted": y_pred_test_rf
})


# In[98]:


test.head(5)


# # ANN

# In[99]:


from tensorflow import keras
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from sklearn.metrics import classification_report, confusion_matrix
import seaborn as sns
import matplotlib.pyplot as plt

model = Sequential([
    Dense(64, activation="relu", input_shape=(X_train.shape[1],)),
    Dense(32, activation="relu"),
    Dense(16, activation="relu"),
    Dense(1, activation="sigmoid")
])

model.compile(optimizer="adam", loss="binary_crossentropy", metrics=["accuracy"])

model.summary()


# In[100]:


history = model.fit(X_train, y_train, epochs=50, batch_size=32, validation_data=(X_test, y_test), verbose=1)

y_pred_ann = (model.predict(X_test) > 0.5).astype("int32")


# ### CLASSIFICATION REPORT

# In[101]:


print(classification_report(y_test, y_pred_ann))


# ### Confusion Matrix

# In[102]:


conf_matrix_ann = confusion_matrix(y_test, y_pred_ann)

plt.figure(figsize=(6, 4))
sns.heatmap(conf_matrix_ann, annot=True, fmt="d", cmap="coolwarm")
plt.xlabel("Predicted")
plt.ylabel("Actual")
plt.title("ANN Confusion Matrix")
plt.show()


# In[ ]:





# In[ ]:




