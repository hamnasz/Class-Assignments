#!/usr/bin/env python
# coding: utf-8

# # 1. Import Libraries
# 
# 
# 

# In[2]:


import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split 
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout


# # 2. Load and Preprocess the Dataset

# In[18]:


df = pd.read_csv("Insurance claims data.csv")
df.head(30)


# In[21]:


df.tail()


# In[23]:


df.shape


# In[25]:


df.sample(5)


# In[26]:


df.info()


# In[27]:


df.describe()


# # MISSING VALUES

# In[28]:


df.isnull().sum()


# In[20]:


import pandas as pd
from sklearn.preprocessing import LabelEncoder


df = pd.read_csv("Insurance claims data.csv")


df.drop(columns=["policy_id"], inplace=True)

binary_cols = df.columns[df.isin(["Yes", "No"]).any()]
df[binary_cols] = df[binary_cols].replace({'Yes': 1, 'No': 0})

cat_cols = df.select_dtypes(include=['object']).columns
label_encoders = {}

for col in cat_cols:
    le = LabelEncoder()
    df[col] = le.fit_transform(df[col])
    label_encoders[col] = le

X = df.drop('claim_status', axis=1)
y = df['claim_status']



# # 3. Train-Test Split and Standardization

# In[7]:


from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split


scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

X_train, X_test, y_train, y_test = train_test_split(
    X_scaled, y, test_size=0.2, random_state=42, stratify=y
)


# # Imbalance data

# In[8]:


import pandas as pd


df = pd.read_csv("Insurance claims data.csv")


label_counts = df['claim_status'].value_counts(normalize=True) * 100


print("Class distribution (%):")
print(label_counts)


df['claim_status'] = df['claim_status'].astype(int) 


# In[21]:


from imblearn.over_sampling import SMOTE
from collections import Counter


smote = SMOTE(random_state=42)
X_train_bal, y_train_bal = smote.fit_resample(X_train, y_train)


print("Original training target distribution:", Counter(y_train))
print("Balanced training target distribution:", Counter(y_train_bal))


# # 4. Baseline Classifier (Logistic Regression)

# In[22]:


from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report
from imblearn.over_sampling import SMOTE
from collections import Counter
import numpy as np


X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)


smote = SMOTE(random_state=42)
X_train_bal, y_train_bal = smote.fit_resample(X_train, y_train)

print("Before balancing:", Counter(y_train))
print("After balancing:", Counter(y_train_bal))


model = LogisticRegression(max_iter=1000, class_weight='balanced')  
model.fit(X_train_bal, y_train_bal)


y_pred = model.predict(X_test)

print("\nClassification Report:\n")
print(classification_report(y_test, y_pred, zero_division=0))


# #  5. Artificial Neural Network (ANN)

# In[14]:


from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout


ann = Sequential()
ann.add(Dense(64, input_dim=X_train.shape[1], activation='relu'))
ann.add(Dropout(0.3))
ann.add(Dense(32, activation='relu'))
ann.add(Dropout(0.2))
ann.add(Dense(1, activation='sigmoid'))


ann.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

history = ann.fit(X_train, y_train, epochs=20, batch_size=64, validation_split=0.2, verbose=1)


# #  6. Evaluate ANN

# In[24]:


from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report, confusion_matrix
from imblearn.over_sampling import SMOTE
from collections import Counter
import numpy as np


X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, stratify=y, random_state=42
)


smote = SMOTE(random_state=42)
X_train_bal, y_train_bal = smote.fit_resample(X_train, y_train)

print("Before SMOTE:", Counter(y_train))
print("After SMOTE:", Counter(y_train_bal))

model = LogisticRegression(max_iter=1000, class_weight='balanced', random_state=42)
model.fit(X_train_bal, y_train_bal)


y_pred = model.predict(X_test)

print("\nClassification Report:")
print(classification_report(y_test, y_pred, zero_division=0))

print("\nConfusion Matrix:")
print(confusion_matrix(y_test, y_pred))


# In[15]:


loss, accuracy = ann.evaluate(X_test, y_test)
print(f"Test Accuracy: {accuracy:.4f}")


y_pred_ann = (ann.predict(X_test) > 0.5).astype("int32")
print("ANN Classification Report:\n")
print(classification_report(y_test, y_pred_ann))


# # confusion matrix 

# In[16]:


from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
import matplotlib.pyplot as plt


y_pred_ann = (ann.predict(X_test) > 0.5).astype("int32")


cm = confusion_matrix(y_test, y_pred_ann)

disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=[0, 1])
disp.plot(cmap=plt.cm.Blues)
plt.title("Confusion Matrix - ANN")
plt.show()


# # random forest

# In[17]:


from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix, ConfusionMatrixDisplay
import matplotlib.pyplot as plt


rf_model = RandomForestClassifier(n_estimators=100, random_state=42)
rf_model.fit(X_train, y_train)

y_pred_rf = rf_model.predict(X_test)


print("Random Forest Classification Report:\n")
print(classification_report(y_test, y_pred_rf))


cm_rf = confusion_matrix(y_test, y_pred_rf)
disp_rf = ConfusionMatrixDisplay(confusion_matrix=cm_rf, display_labels=[0, 1])
disp_rf.plot(cmap=plt.cm.Greens)
plt.title("Confusion Matrix - Random Forest")
plt.show()


# In[ ]:




