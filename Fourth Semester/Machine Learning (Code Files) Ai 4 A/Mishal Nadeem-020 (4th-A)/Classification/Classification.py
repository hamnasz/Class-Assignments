#!/usr/bin/env python
# coding: utf-8

# # CLASSIFICATION PROJECT

# ## Dataset: Loan Approval

# ## DATA PREPROCESSING

# ### Importing Libraries

# In[510]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.model_selection import train_test_split, learning_curve
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix, roc_curve, auc
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.feature_selection import SelectKBest, chi2
from imblearn.over_sampling import SMOTE
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.utils import plot_model


# ### Reading Data

# In[513]:


df = pd.read_csv('la.csv')


# ### Exporing Data

# In[516]:


df.head()


# In[517]:


df.tail()


# In[520]:


df.info()


# In[522]:


df.describe()


# ### Cleansing Data

# #### Before Cleansing Data

# In[526]:


df.isnull().sum()


# #### After Cleansing Data

# ##### Handle missing values in numeric columns (fill with median)

# In[529]:


numeric_cols = df.select_dtypes(include=['number']).columns
df[numeric_cols] = df[numeric_cols].fillna(df[numeric_cols].median())


# ##### Handle missing values in categorical columns (fill with mode)

# In[533]:


categorical_cols = df.select_dtypes(include=['object']).columns
for col in categorical_cols:
    df[col] = df[col].fillna(df[col].mode()[0])


# In[535]:


df.isnull().sum()


# ### Outlier Detection and Removal

# In[538]:


df_class_1 = df[df['LoanStatus'] == 1]
df_class_0 = df[df['LoanStatus'] == 0]

def remove_outliers_iqr(df_subset):
    numeric_cols = df_subset.select_dtypes(include=[np.number]).columns
    Q1 = df_subset[numeric_cols].quantile(0.25)
    Q3 = df_subset[numeric_cols].quantile(0.75)
    IQR = Q3 - Q1
    mask = ~((df_subset[numeric_cols] < (Q1 - 1.5 * IQR)) | 
             (df_subset[numeric_cols] > (Q3 + 1.5 * IQR))).any(axis=1)
    return df_subset[mask]

df_class_1_clean = remove_outliers_iqr(df_class_1.drop(columns=['LoanStatus']))
df_class_0_clean = remove_outliers_iqr(df_class_0.drop(columns=['LoanStatus']))

df_class_1_clean['LoanStatus'] = 1
df_class_0_clean['LoanStatus'] = 0

df_cleaned = pd.concat([df_class_1_clean, df_class_0_clean], axis=0).reset_index(drop=True)

print(f"Original class counts:\n{df['LoanStatus'].value_counts()}")
print(f"\nCleaned class counts:\n{df_cleaned['LoanStatus'].value_counts()}")
print(f"\nRows removed: {len(df) - len(df_cleaned)}")
print(f"Final shape of cleaned dataset: {df_cleaned.shape}")

numeric_cols = df.select_dtypes(include=[np.number]).columns

plt.figure(figsize=(15, 6))

plt.subplot(1, 2, 1)
sns.boxplot(data=df[numeric_cols])
plt.title('Before Outlier Removal')
plt.xticks(rotation=90)

plt.subplot(1, 2, 2)
sns.boxplot(data=df_cleaned[numeric_cols])
plt.title('After Outlier Removal')
plt.xticks(rotation=90)

plt.tight_layout()
plt.show()


# ### Separate Target Column

# In[540]:


X = df_cleaned.drop('LoanStatus', axis=1) 
y = df_cleaned['LoanStatus']


# ### Data Transformation (Standardization)

# #### Before Standardization

# In[543]:


X.head()


# #### After Standardization

# In[547]:


numeric_cols = X.select_dtypes(include=np.number).columns

X[numeric_cols] = X[numeric_cols].astype(float)

scaler = StandardScaler()
X.loc[:, numeric_cols] = scaler.fit_transform(X[numeric_cols])

X.head()


# ### Categorical into Numerical (One-Hot Encoding)

# #### Before One-Hot Encoding

# In[552]:


X.shape


# In[554]:


X.info()


# #### After One-Hot Encoding

# In[557]:


X = pd.get_dummies(X, drop_first=False)


# In[559]:


X.shape


# In[561]:


X.info()


# ### Handle Imbalanced Data

# #### Before Handling Imbalanced Data

# In[565]:


y.value_counts()


# #### After Handling Imbalanced Data

# In[568]:


smote = SMOTE(random_state=42)
X, y = smote.fit_resample(X, y)


# In[570]:


print(X.shape)
print(y.shape)
y.value_counts()


# ### Feature Selection

# In[573]:


from sklearn.feature_selection import SelectKBest, f_classif

selector = SelectKBest(score_func=f_classif, k=6)
X_selected = selector.fit_transform(X, y)
selected_features = X.columns[selector.get_support()]
print("Selected features:", selected_features)


# ### Data Splitting

# In[576]:


X_train, X_test, y_train, y_test = train_test_split(X[selected_features], y, test_size=0.2, random_state=42)
X_train.shape, X_test.shape, y_train.shape, y_test.shape


# ## CLASSIFICATION

# ### a. Random Forest

# #### Train the model

# In[581]:


rf = RandomForestClassifier()
rf.fit(X_train, y_train)


# #### Classification Report

# In[583]:


y_pred_rf = rf.predict(X_test)
print("\nRandom Forest")
print("Accuracy:", accuracy_score(y_test, y_pred_rf))
print("Classification Report:\n", classification_report(y_test, y_pred_rf))
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred_rf))


# #### Confusion Matrix

# In[587]:


cm_rf = confusion_matrix(y_test, y_pred_rf)
plt.figure(figsize=(6,4))
sns.heatmap(cm_rf, annot=True, fmt='d', cmap='Blues')
plt.title('Random Forest Confusion Matrix')
plt.xlabel('Predicted')
plt.ylabel('Actual')
plt.show()


# ### b. SVM

# #### Train the model

# In[590]:


svm = SVC(probability=True)
svm.fit(X_train, y_train)


# #### Classification Report

# In[593]:


y_pred_svm = svm.predict(X_test)
print("\nSVM")
print("Accuracy:", accuracy_score(y_test, y_pred_svm))
print("Classification Report:\n", classification_report(y_test, y_pred_svm))
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred_svm))


# #### Confusion Matrix

# In[597]:


cm_svm = confusion_matrix(y_test, y_pred_svm)
plt.figure(figsize=(6,4))
sns.heatmap(cm_svm, annot=True, fmt='d', cmap='Greens')
plt.title('SVM Confusion Matrix')
plt.xlabel('Predicted')
plt.ylabel('Actual')
plt.show()


# ### c. ANN

# #### Train the model

# In[601]:


ann = Sequential()
ann.add(Dense(32, input_dim=X_train.shape[1], activation='relu'))
ann.add(Dense(16, activation='relu'))
ann.add(Dense(1, activation='sigmoid'))
ann.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
ann.fit(X_train, y_train, epochs=50, batch_size=32, verbose=1)
ann_preds = (ann.predict(X_test) > 0.5).astype(int)


# #### Classification Report

# In[603]:


print("\nANN")
print("Accuracy:", accuracy_score(y_test, ann_preds))
print("Classification Report:\n", classification_report(y_test, ann_preds))
print("Confusion Matrix:\n", confusion_matrix(y_test, ann_preds))


# #### Confusion Matrix

# In[605]:


cm_ann = confusion_matrix(y_test, ann_preds)
plt.figure(figsize=(6,4))
sns.heatmap(cm_ann, annot=True, fmt='d', cmap='Oranges')
plt.title('ANN Confusion Matrix')
plt.xlabel('Predicted')
plt.ylabel('Actual')
plt.show()


# ### Performance Analysis and Model Insights (Random Forest)

# #### ROC Curve

# In[608]:


y_prob_rf = rf.predict_proba(X_test)[:, 1]
fpr, tpr, thresholds = roc_curve(y_test, y_prob_rf)
roc_auc = auc(fpr, tpr)

plt.figure(figsize=(7,4))
plt.plot(fpr, tpr, label=f'Random Forest (AUC = {roc_auc:.2f})')
plt.plot([0,1], [0,1], 'k--')
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('ROC Curve')
plt.legend()
plt.grid()
plt.show()


# In[609]:


from sklearn.model_selection import StratifiedKFold, cross_val_score
from sklearn.ensemble import RandomForestClassifier

skf = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)
model = RandomForestClassifier()

scores = cross_val_score(model, X, y, cv=skf, scoring='roc_auc')
print("AUC scores from cross-validation:", scores)
print("Mean AUC:", scores.mean())


# #### Learning Curve

# In[611]:


train_sizes, train_scores, test_scores = learning_curve(
    rf, X[selected_features], y, cv=5, scoring='accuracy', train_sizes=np.linspace(0.1, 1.0, 10))

train_mean = np.mean(train_scores, axis=1)
test_mean = np.mean(test_scores, axis=1)

plt.figure(figsize=(7,4))
plt.plot(train_sizes, train_mean, label='Training Accuracy')
plt.plot(train_sizes, test_mean, label='Validation Accuracy')
plt.xlabel('Training Size')
plt.ylabel('Accuracy')
plt.title('Learning Curve - Random Forest')
plt.legend()
plt.grid()
plt.show()


# #### Feature Importance

# In[613]:


importances = rf.feature_importances_
indices = np.argsort(importances)[::-1]
features_sorted = [selected_features[i] for i in indices]
importances_sorted = importances[indices]

plt.figure(figsize=(7, 4))
sns.barplot(x=features_sorted, y=importances_sorted,  color='pink')
plt.title('Feature Importance - Random Forest')
plt.xlabel('Feature')
plt.ylabel('Importance')
plt.xticks(rotation=45, ha='right')
plt.grid()
plt.tight_layout()
plt.show()

