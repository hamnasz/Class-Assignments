#!/usr/bin/env python
# coding: utf-8

# In[93]:


import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder


df = pd.read_csv("Diabetes Classification.csv")

df.shape


# In[94]:


df.columns


# In[95]:


df.info()


# In[96]:


df.describe()


# In[97]:


df.head()


# # Encode categorical features

# In[99]:


label_encoders = {}
categorical_cols = ['Gender', 'Blood Pressure', 'Family History of Diabetes',
                    'Smoking', 'Diet', 'Exercise', 'Diagnosis']

for col in categorical_cols:
    le = LabelEncoder()
    df[col] = le.fit_transform(df[col])
    label_encoders[col] = le


# # Split features and target

# In[101]:


X = df.drop('Diagnosis', axis=1)
y = df['Diagnosis']


# # Train-test split

# In[103]:


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


# # Standardize numerical features
# 

# In[105]:


scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)


# # Random Forest Classifier

# In[107]:


from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
import matplotlib.pyplot as plt


rf_model = RandomForestClassifier(random_state=42)
rf_model.fit(X_train_scaled, y_train)
y_pred_rf = rf_model.predict(X_test_scaled)


cm_rf = confusion_matrix(y_test, y_pred_rf)
disp_rf = ConfusionMatrixDisplay(cm_rf, display_labels=label_encoders['Diagnosis'].classes_)
disp_rf.plot(cmap=plt.cm.Blues)
plt.title("Random Forest - Confusion Matrix")
plt.show()


# # Logistic Regression

# In[109]:


from sklearn.linear_model import LogisticRegression


lr_model = LogisticRegression()
lr_model.fit(X_train_scaled, y_train)
y_pred_lr = lr_model.predict(X_test_scaled)


cm_lr = confusion_matrix(y_test, y_pred_lr)
disp_lr = ConfusionMatrixDisplay(cm_lr, display_labels=label_encoders['Diagnosis'].classes_)
disp_lr.plot(cmap=plt.cm.Oranges)
plt.title("Logistic Regression - Confusion Matrix")
plt.show()


#  # Artificial Neural Network (ANN)

# In[111]:


import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
import matplotlib.pyplot as plt

ann_model = Sequential([
    Dense(10, activation='relu', input_shape=(X_train_scaled.shape[1],)),
    Dense(10, activation='relu'),
    Dense(1, activation='sigmoid')  
])

ann_model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

ann_model.fit(X_train_scaled, y_train, epochs=20, batch_size=32, validation_split=0.2)

y_pred_ann_prob = ann_model.predict(X_test_scaled)
y_pred_ann = (y_pred_ann_prob > 0.5).astype(int).flatten()

cm_ann = confusion_matrix(y_test, y_pred_ann)
disp_ann = ConfusionMatrixDisplay(confusion_matrix=cm_ann, display_labels=label_encoders['Diagnosis'].classes_)
disp_ann.plot(cmap=plt.cm.Greens)
plt.title("ANN - Confusion Matrix")
plt.show()


# In[23]:


import pandas as pd
from imblearn.over_sampling import SMOTE
from sklearn.model_selection import train_test_split


print("Columns:", df.columns)


X = df.drop('Diagnosis', axis=1)
y = df['Diagnosis']


X = pd.get_dummies(X, drop_first=True)


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)


smote = SMOTE(random_state=42)


X_train_smote, y_train_smote = smote.fit_resample(X_train, y_train)


print("Before SMOTE:")
print(y_train.value_counts())
print("\nAfter SMOTE:")
print(y_train_smote.value_counts())




# In[ ]:




