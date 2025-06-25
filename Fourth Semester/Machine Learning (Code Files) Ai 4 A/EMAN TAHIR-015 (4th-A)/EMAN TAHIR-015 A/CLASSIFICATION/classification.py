#!/usr/bin/env python
# coding: utf-8

# # import libraries

# In[1]:


import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, accuracy_score


# # load the dataset

# In[2]:


df = pd.read_csv("Obesity Classification.csv")


# # explore the data set

# In[5]:


df.head()


# In[7]:


df.info()


# In[9]:


df.describe()


# # encode categorical columns

# In[11]:


le_gender = LabelEncoder()
df['Gender'] = le_gender.fit_transform(df['Gender'])


# In[13]:


le_label = LabelEncoder()
df['Label'] = le_label.fit_transform(df['Label'])


# # prepare features and target

# In[15]:


X = df[['Age', 'Gender', 'Height', 'Weight', 'BMI']]
y = df['Label']


# # splitting into training and testing sets

# In[17]:


X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42)


# # train the randomforest classifier

# In[19]:


clf = RandomForestClassifier(n_estimators=100, random_state=42)
clf.fit(X_train, y_train)


# # make predictions and evaluate the model

# In[21]:


y_pred = clf.predict(X_test)
print("Accuracy:", accuracy_score(y_test, y_pred))
print("\nClassification Report:\n", classification_report(y_test, y_pred))


# # visualize class distribution

# In[12]:


import seaborn as sns
import matplotlib.pyplot as plt

df['Label_Names'] = le_label.inverse_transform(df['Label'])

plt.figure(figsize=(8, 5))
sns.countplot(data=df, x='Label_Names', palette='viridis')
plt.title('Class Distribution of Obesity Categories')
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()


# # plot confusion matrix

# In[13]:


from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay

cm = confusion_matrix(y_test, y_pred)
disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=le_label.classes_)
disp.plot(cmap='Blues')
plt.title('Confusion Matrix')
plt.show()


# # feature importance

# In[14]:


import pandas as pd

feature_names = X_train.columns
feature_importances = clf.feature_importances_

importance_df = pd.DataFrame({
    'Feature': feature_names,
    'Importance': feature_importances
}).sort_values(by='Importance', ascending=False)


# In[15]:


import seaborn as sns
import matplotlib.pyplot as plt

plt.figure(figsize=(10, 6))
sns.barplot(
    x='Importance',
    y='Feature',
    data=importance_df,
    palette='coolwarm'
)
plt.title("Feature Importance from Random Forest")
plt.xlabel("Importance")
plt.ylabel("Feature")
plt.tight_layout()
plt.show()


# # trying another classifier 

# In[21]:


from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression

scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

lr = LogisticRegression(max_iter=2000)
lr.fit(X_train_scaled, y_train)


# # cross validation

# In[17]:


from sklearn.model_selection import cross_val_score

scores = cross_val_score(clf, X, y, cv=5)
print("Random Forest Cross-Validation Accuracy Scores:", scores)
print("Mean Accuracy:", scores.mean())


# # ann

# In[18]:


import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from tensorflow.keras.utils import to_categorical

le = LabelEncoder()
y_encoded = le.fit_transform(y)  
y_categorical = to_categorical(y_encoded)  

X_scaled = scaler.fit_transform(X)  

X_train, X_test, y_train, y_test = train_test_split(X_scaled, y_categorical, test_size=0.2, random_state=42)

model = Sequential()
model.add(Dense(64, activation='relu', input_shape=(X_train.shape[1],)))
model.add(Dense(32, activation='relu'))
model.add(Dense(y_categorical.shape[1], activation='softmax'))  

model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
model.fit(X_train, y_train, epochs=20, batch_size=32, validation_split=0.2)


# In[22]:


from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

y_pred_prob = model.predict(X_test)
y_pred_ann = (y_pred_prob > 0.5).astype(int)

y_pred_ann = y_pred_ann.ravel()
y_test = y_test.ravel()

print("ANN Evaluation:")
print("Accuracy:", accuracy_score(y_test, y_pred_ann))
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred_ann))
print("Classification Report:\n", classification_report(y_test, y_pred_ann))



# In[ ]:




