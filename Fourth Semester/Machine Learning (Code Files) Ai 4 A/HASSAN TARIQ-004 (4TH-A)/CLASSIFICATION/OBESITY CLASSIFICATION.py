#!/usr/bin/env python
# coding: utf-8

# # Import necessary libraries

# In[54]:


import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.decomposition import PCA
from sklearn.ensemble import RandomForestClassifier
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import confusion_matrix, classification_report, accuracy_score
import seaborn as sns
import matplotlib.pyplot as plt


# # Load the dataset

# In[55]:


data = pd.read_csv("C:/Users/Ayaan/Desktop/Obesity Classification.csv")


# # 1. Data Exploration

# In[44]:


print("Data Info:")
print(data.info())
print("\nSummary Statistics:")
print(data.describe())
print("\nMissing Values:")
print(data.isnull().sum())


# # 2. Cleanse Data (remove ID column)

# In[56]:


if 'ID' in data.columns:
    data.drop('ID', axis=1, inplace=True)


# # 3. Outlier Detection & Removal using IQR

# In[57]:


numeric_cols = data.select_dtypes(include=['number']).columns
Q1 = data[numeric_cols].quantile(0.25)
Q3 = data[numeric_cols].quantile(0.75)
IQR = Q3 - Q1
data_cleaned = data[~((data[numeric_cols] < (Q1 - 1.5 * IQR)) | (data[numeric_cols] > (Q3 + 1.5 * IQR))).any(axis=1)]


# # 4. Convert Categorical to Numerical

# In[58]:


label_encoder_gender = LabelEncoder()
data_cleaned['Gender'] = label_encoder_gender.fit_transform(data_cleaned['Gender'])

label_encoder_label = LabelEncoder()
data_cleaned['Label'] = label_encoder_label.fit_transform(data_cleaned['Label'])


# # 5. Separate Features and Target

# In[60]:


X = data_cleaned.drop('Label', axis=1)
y = data_cleaned['Label']
y = y.astype('int')


# # 6. Data Transformation (Standardization)

# In[61]:


scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)


# # 7. Dimensionality Reduction (PCA)

# In[62]:


pca = PCA(n_components=0.95)
X_pca = pca.fit_transform(X_scaled)


# # 8. Data Splitting

# In[63]:


X_train, X_test, y_train, y_test = train_test_split(X_pca, y, test_size=0.2, random_state=42)


# # Random forest classifier

# In[64]:


rf_model = RandomForestClassifier(random_state=42)
rf_model.fit(X_train, y_train)
y_pred_rf = rf_model.predict(X_test)


# # ANN (MLP Classifier)

# In[65]:


ann_model = MLPClassifier(hidden_layer_sizes=(50, 30), max_iter=1000, random_state=42)
ann_model.fit(X_train, y_train)
y_pred_ann = ann_model.predict(X_test)


# # Plot Confusion Matrix Heatmaps

# In[66]:


plt.figure(figsize=(14, 6))


# # Random Forest Confusion Matrix

# In[67]:


plt.subplot(1, 2, 1)
cm_rf = confusion_matrix(y_test, y_pred_rf)
sns.heatmap(cm_rf, annot=True, fmt='d', cmap='Blues')
plt.title("Random Forest Confusion Matrix")
plt.xlabel("Predicted")
plt.ylabel("Actual")


# # ANN Confusion Matrix

# In[68]:


plt.subplot(1, 2, 2)
cm_ann = confusion_matrix(y_test, y_pred_ann)
sns.heatmap(cm_ann, annot=True, fmt='d', cmap='Greens')
plt.title("ANN (MLP Classifier) Confusion Matrix")
plt.xlabel("Predicted")
plt.ylabel("Actual")


# In[69]:


plt.tight_layout()
plt.show()


# # Classification report

# In[70]:


print("\nRandom Forest Classification Report:")
print(classification_report(y_test, y_pred_rf))

print("\nANN (MLP Classifier) Classification Report:")
print(classification_report(y_test, y_pred_ann))


# In[ ]:




