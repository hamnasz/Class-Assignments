#!/usr/bin/env python
# coding: utf-8

# # Importing libraries

# In[73]:


import numpy as np 
import pandas as pd 
import os
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split, cross_validate
from sklearn.metrics import classification_report, roc_auc_score
from sklearn.metrics import confusion_matrix, f1_score, precision_score, recall_score
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
from sklearn.metrics import roc_curve, auc
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler


# # Reading csv

# In[75]:


data = pd.read_csv('star.csv')



# # Initial PreProcessing

# In[77]:


data.head()


# In[78]:


y = data["class"]
X = data[["alpha","delta","u","g","r","i","z"]]
y.shape, X.shape


# In[79]:


data.dtypes


# In[80]:


for column in data.columns:
    print(column, len(data[data[column].isna()]))
    


# In[81]:


data = data.drop(
    columns=["obj_ID", "run_ID", "rerun_ID",
             "field_ID", "spec_obj_ID", "fiber_ID",
             "plate", "MJD", "cam_col"])


# In[82]:


from sklearn.preprocessing import LabelEncoder
class_encoder = LabelEncoder()
data['class'] = class_encoder.fit_transform(data['class'])


# In[83]:


from sklearn.preprocessing import StandardScaler
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)


# In[84]:


plt.figure(figsize=(20, 12))
for index, column in enumerate(data.columns):
    plt.subplot(3,3,index+1)
    if column != "class":
        sns.boxplot(data, y=column)
    else:
        sns.countplot(data, x=column)
plt.tight_layout()
plt.show()


# In[85]:


def iqr(data, column): 
    q3 = data[column].quantile(0.75) #3er cuartil
    q1 = data[column].quantile(0.25) #1er cuartil
    superior_limit = q3 + 1.5*(q3 - q1)
    inferior_limit = q1 - 1.5*(q3 - q1)
    return data[(data[column] < superior_limit) & (data[column] > inferior_limit)] #Selects data


# In[86]:


for col in data.columns: 
    if col != "class":
        data = iqr(data, col) 
data


# In[87]:


plt.figure(figsize=(20, 12))
for index, column in enumerate(data.columns):
    plt.subplot(3,3,index+1)
    if column != "class":
        sns.boxplot(data, y=column)
    else:
        sns.countplot(data, x=column)
plt.tight_layout()
plt.show()


# In[88]:


for column in data.columns:
    if column != "class":
        sns.boxplot(data, y=column, x="class")
        plt.show()


# In[89]:


data.columns


# In[90]:


X = data.drop(columns=["alpha", "delta", "class"])
y = data["class"]


# In[91]:


sns.heatmap(X.corr(), annot=True)


# In[92]:


X_train, X_test, y_train, y_test = train_test_split(X, y)
X_train.shape, X_test.shape, y_train.shape, y_test.shape


# In[93]:


ss = StandardScaler()
X_train = ss.fit_transform(X_train)
X_test = ss.transform(X_test)


# In[94]:


pca = PCA()
pca.fit(X_train)
pca.explained_variance_ratio_


# In[95]:


exp_variance = pd.DataFrame(pca.explained_variance_ratio_) 
exp_variance["component"] = exp_variance.index + 1 
exp_variance = exp_variance.rename(columns={0: "explained_variance"}) 
sns.barplot(exp_variance, x="component", y = "explained_variance", color="skyblue") 
plt.xticks([]) 
plt.show() 


# In[96]:


exp_variance["explained_variance_cumulate"] = exp_variance["explained_variance"].cumsum() #Cummulative sum
sns.lineplot(exp_variance, x = "component", y="explained_variance_cumulate") #Plots
plt.axhline(0.95)  #Plots line at 95% of variance
plt.show() #Display


# In[97]:


pca = PCA(4)
X_train_trans = pca.fit_transform(X_train)
X_test_trans = pca.transform(X_test)


# In[98]:


X_train


# In[99]:


sns.scatterplot(pd.DataFrame(X_train_trans, index=y_train.index).sample(10000), x=0, y=1, hue=y_train , alpha=0.4, s = 5)


# In[100]:


print(data.columns)


# In[101]:


df = pd.read_csv('star.csv')
df.columns = df.columns.str.strip()

class_encoder = LabelEncoder()
df['class'] = class_encoder.fit_transform(df['class'])

X = df[['u', 'g', 'r', 'i', 'z', 'redshift']]
y = df['class']

scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)
model = RandomForestClassifier(random_state=42)
model.fit(X_train, y_train)


# In[102]:


import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix

y_pred_test = model.predict(X_test)

cm = confusion_matrix(y_test, y_pred_test)

plt.figure(figsize=(8, 6))
sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', xticklabels=model.classes_, yticklabels=model.classes_)
plt.xlabel('Predicted')
plt.ylabel('Actual')
plt.title('Confusion Matrix')
plt.show()


# In[103]:


y_prob = model.predict_proba(X_test)

fpr, tpr, thresholds = roc_curve(y_test, y_prob[:, 1], pos_label=1)  # Use the class 1 probability for ROC

roc_auc = auc(fpr, tpr)

plt.figure(figsize=(8, 6))
plt.plot(fpr, tpr, color='blue', lw=2, label='ROC curve (AUC = %0.2f)' % roc_auc)
plt.plot([0, 1], [0, 1], color='gray', lw=2, linestyle='--')  # Diagonal line representing random guesses
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('ROC Curve')
plt.legend(loc='lower right')
plt.show()


# In[104]:


importances = model.feature_importances_

features = X.columns

feat_importance_df = pd.DataFrame({
    'Feature': features,
    'Importance': importances
})

plt.figure(figsize=(10, 6))
sns.barplot(x='Importance', y='Feature', data=feat_importance_df.sort_values('Importance', ascending=False))
plt.title('Feature Importance Plot')
plt.show()


# In[105]:


y_pred_test = model.predict(X_test)

plt.figure(figsize=(8, 6))
plt.scatter(y_test, y_pred_test, color='blue', alpha=0.5)
plt.plot([min(y_test), max(y_test)], [min(y_test), max(y_test)], color='red', linestyle='--')
plt.xlabel('Actual Values')
plt.ylabel('Predicted Values')
plt.title('Predicted vs Actual Plot')
plt.show()


# In[106]:


accuracy = accuracy_score(y_test, y_pred_test)
print(f'Accuracy: {accuracy * 100:.2f}%')

print('Classification Report:')
print(classification_report(y_test, y_pred_test))


# In[107]:


custom_input = pd.DataFrame([{
    'u': 17.5,
    'g': 17.8,
    'r': 17.2,
    'i': 14.9,
    'z': 16.7,
    'redshift': 0.1
}])

custom_input_scaled = scaler.transform(custom_input)

prediction = model.predict(custom_input_scaled)
predicted_class = class_encoder.inverse_transform(prediction)[0]

print("Predicted Class:", predicted_class)

