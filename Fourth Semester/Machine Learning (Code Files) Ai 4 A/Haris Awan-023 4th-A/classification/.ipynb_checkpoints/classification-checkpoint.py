#!/usr/bin/env python
# coding: utf-8

# # 1. Introduction to Python and Libraries for Machine Learning

# In[2]:


import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC
from sklearn.metrics import classification_report, confusion_matrix, roc_auc_score, roc_curve, accuracy_score


# ### Data Loading

# In[4]:


df = pd.read_csv("drug200.csv")


# ### Environmental Setup

# In[6]:


df.head()


# In[7]:


df.describe()


# In[8]:


df.info()


# In[9]:


df.tail()


# ### Handling missing values, data normalization, standardization

# In[21]:


df.isnull().sum()
le = LabelEncoder()
df['Sex'] = le.fit_transform(df['Sex'])
df['BP'] = le.fit_transform(df['BP'])
df['Cholesterol'] = le.fit_transform(df['Cholesterol'])
X = df.drop('Drug', axis=1)
y = df['Drug']
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)


# ### Data visualization using Matplotlib and Seaborn

# In[24]:


sns.countplot(x='Drug', data=df)
plt.title("Drug Distribution")
plt.show()
sns.heatmap(df.drop('Drug', axis=1).corr(), annot=True, cmap='coolwarm')
plt.title("Feature Correlation")
plt.show()


# ### Data preprocessing 

# In[27]:


X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)


# ### Logistic Regression for binary classification, Model evaluation using metrics (R², MAE, MSE)

# In[30]:


log_reg = LogisticRegression()
log_reg.fit(X_train, y_train)
y_pred_lr = log_reg.predict(X_test)
print(classification_report(y_test, y_pred_lr))


# ### Implementing Decision Tree

# In[33]:


tree = DecisionTreeClassifier()
tree.fit(X_train, y_train)
y_pred_tree = tree.predict(X_test)
print(classification_report(y_test, y_pred_tree))


# ### Implementing Support Vector Machine

# In[36]:


svm_model = SVC(probability=True)
svm_model.fit(X_train, y_train)
y_pred_svm = svm_model.predict(X_test)
print(classification_report(y_test, y_pred_svm))


# ### Evaluation Matrices for classification 

# In[39]:


print(confusion_matrix(y_test, y_pred_svm))
print(accuracy_score(y_test, y_pred_svm))
y_proba_lr = log_reg.predict_proba(X_test)
fpr, tpr, _ = roc_curve(y_test, y_proba_lr[:, 1], pos_label='DrugY')
plt.plot(fpr, tpr, label="Logistic Regression")
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('ROC Curve')
plt.legend()
plt.show()


# ### User Input and Output

# In[42]:


def get_user_input():
    age = int(input("Age: "))
    sex = input("Sex (M/F): ")
    bp = input("BP (LOW/NORMAL/HIGH): ")
    chol = input("Cholesterol (NORMAL/HIGH): ")
    na_to_k = float(input("Na_to_K: "))
    sex = 1 if sex.upper() == 'M' else 0
    bp = {'LOW': 0, 'NORMAL': 1, 'HIGH': 2}.get(bp.upper(), 1)
    chol = {'NORMAL': 0, 'HIGH': 1}.get(chol.upper(), 1)
    user_data = pd.DataFrame([[age, sex, bp, chol, na_to_k]],
                             columns=['Age', 'Sex', 'BP', 'Cholesterol', 'Na_to_K'])
    user_data_scaled = scaler.transform(user_data)
    return user_data_scaled

user_input_scaled = get_user_input()
prediction = svm_model.predict(user_input_scaled)
print("\n Predicted Drug Recommendation:", prediction[0])


# In[ ]:




