#!/usr/bin/env python
# coding: utf-8

# # Importing libraries

# In[3]:


import numpy as np 
import pandas as pd 
import os
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split, cross_validate
from sklearn.metrics import classification_report, roc_auc_score
from sklearn.metrics import confusion_matrix, f1_score, precision_score, recall_score


# # Reading csv

# In[5]:


data = pd.read_csv('salary.csv')



# # Initial PreProcessing

# In[7]:


data.head()


# In[9]:


y = data["class"]
X = data[["alpha","delta","u","g","r","i","z"]]
y.shape, X.shape


# In[122]:


data.dtypes


# In[123]:


for column in data.columns:
    print(column, len(data[data[column].isna()]))



# In[124]:


data = data.drop(
    columns=["obj_ID", "run_ID", "rerun_ID",
             "field_ID", "spec_obj_ID", "fiber_ID",
             "plate", "MJD", "cam_col"])


# In[125]:


plt.figure(figsize=(20, 12))
for index, column in enumerate(data.columns):
    plt.subplot(3,3,index+1)
    if column != "class":
        sns.boxplot(data, y=column)
    else:
        sns.countplot(data, x=column)
plt.tight_layout()
plt.show()


# In[126]:


#Filter data using Inter quantile range
def iqr(data, column): #Inter quantile range
    q3 = data[column].quantile(0.75) #3er cuartil
    q1 = data[column].quantile(0.25) #1er cuartil
    superior_limit = q3 + 1.5*(q3 - q1)
    inferior_limit = q1 - 1.5*(q3 - q1)
    return data[(data[column] < superior_limit) & (data[column] > inferior_limit)] #Selects data


# In[127]:


for col in data.columns: 
    if col != "class":
        data = iqr(data, col) 
data


# In[128]:


plt.figure(figsize=(20, 12))
for index, column in enumerate(data.columns):
    plt.subplot(3,3,index+1)
    if column != "class":
        sns.boxplot(data, y=column)
    else:
        sns.countplot(data, x=column)
plt.tight_layout()
plt.show()


# In[129]:


for column in data.columns:
    if column != "class":
        sns.boxplot(data, y=column, x="class")
        plt.show()


# In[130]:


data.columns


# In[131]:


X = data.drop(columns=["alpha", "delta", "class"])
y = data["class"]


# In[132]:


sns.heatmap(X.corr(), annot=True)


# In[133]:


from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler


# In[134]:


X_train, X_test, y_train, y_test = train_test_split(X, y)
X_train.shape, X_test.shape, y_train.shape, y_test.shape


# In[135]:


ss = StandardScaler()
X_train = ss.fit_transform(X_train)
X_test = ss.transform(X_test)


# In[136]:


pca = PCA()
pca.fit(X_train)
pca.explained_variance_ratio_


# In[137]:


exp_variance = pd.DataFrame(pca.explained_variance_ratio_) #Gets explained variance
exp_variance["component"] = exp_variance.index + 1 #Assign a PC number
exp_variance = exp_variance.rename(columns={0: "explained_variance"}) #Rename 0 column to explained_variance
sns.barplot(exp_variance, x="component", y = "explained_variance", color="skyblue") #Plot explained variance
plt.xticks([]) #Drops xticks
plt.show() #Display


# In[138]:


exp_variance["explained_variance_cumulate"] = exp_variance["explained_variance"].cumsum() #Cummulative sum
sns.lineplot(exp_variance, x = "component", y="explained_variance_cumulate") #Plots
plt.axhline(0.95)  #Plots line at 95% of variance
plt.show() #Display


# In[139]:


pca = PCA(4)
X_train_trans = pca.fit_transform(X_train)
X_test_trans = pca.transform(X_test)


# In[140]:


X_train


# In[141]:


sns.scatterplot(pd.DataFrame(X_train_trans, index=y_train.index).sample(10000), x=0, y=1, hue=y_train , alpha=0.4, s = 5)


# In[142]:


from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import balanced_accuracy_score


# In[143]:


lr = LogisticRegression(class_weight="balanced", max_iter=1000)
cv_score = cross_validate(lr, X_train, y_train, scoring="roc_auc_ovr")["test_score"]
lr.fit(X_train, y_train)
y_pred = lr.predict(X_test)
y_prob = lr.predict_proba(X_test)
cv_score.mean(), cv_score.std(), roc_auc_score(y_test, y_prob, multi_class="ovr")


# In[144]:


lr = LogisticRegression(class_weight="balanced")
cv_score = cross_validate(lr, X_train_trans, y_train, scoring="roc_auc_ovr")["test_score"]
lr.fit(X_train_trans, y_train)
y_pred = lr.predict(X_test_trans)
y_prob = lr.predict_proba(X_test_trans)
print(classification_report(y_test, y_pred))


# In[145]:


y_pred = lr.predict(X_test_trans)
cm = pd.DataFrame(confusion_matrix(y_test, y_pred), columns=lr.classes_, index=lr.classes_)
sns.heatmap(cm, annot=True, fmt=".0f")
plt.xlabel("Real")
plt.ylabel("Predicted")
plt.show()


# In[146]:


from sklearn.metrics import roc_curve
fpr, tpr, threshold = roc_curve(y_test == "GALAXY", y_prob[:,0])
plt.plot(fpr, tpr, label="GALAXY")

fpr, tpr, threshold = roc_curve(y_test == "QSO", y_prob[:,1])
plt.plot(fpr, tpr, label="QSO")

fpr, tpr, threshold = roc_curve(y_test == "STAR", y_prob[:,2])
plt.plot(fpr, tpr, label="STAR")
plt.legend()
plt.show()


# In[147]:


coefs = pd.DataFrame(lr.coef_)
coefs


# In[148]:


coefs = coefs.T.rename(columns={0: "Galaxy", 1: "Star", 2: "QSR"}).reset_index()
coefs


# In[149]:


melted = coefs.melt(id_vars="index")
melted


# In[150]:


sns.barplot(melted, y="value",x="index", hue="variable")


# In[151]:


sub_data = pd.DataFrame(X_test_trans)
sub_data["y_pred"] = y_pred
sub_data["y_true"] = y_test.reset_index(drop=True)
sub_data


# In[152]:


sns.scatterplot(sub_data, x=0, y=1, hue="y_pred", alpha=0.3, s=5)


# In[153]:


sns.scatterplot(sub_data, x=0, y=1, hue="y_true", alpha=0.3, s=5)


# In[154]:


sns.pairplot(sub_data[[0,1,2,"y_pred"]], hue="y_pred", plot_kws={"alpha":0.5, "s": 5, "hue_order": ["QSO", "GALAXY", "STAR"]})


# In[155]:


sns.pairplot(sub_data[[0,1,2,"y_true"]], hue="y_true", plot_kws={"alpha":0.5, "s": 5, "hue_order": ["QSO", "GALAXY", "STAR"]})


# In[156]:


print(data.columns.tolist())


# In[157]:


# Load data
df = pd.read_csv('salary.csv')
df.columns = df.columns.str.strip()

# Encode target
class_encoder = LabelEncoder()
df['class'] = class_encoder.fit_transform(df['class'])

# Features and target
X = df[['u', 'g', 'r', 'i', 'z', 'redshift']]
y = df['class']

# Scale
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)



# In[158]:


# Define a new, unseen data sample
custom_input = pd.DataFrame([{
    'u': 18.5,
    'g': 17.8,
    'r': 17.2,
    'i': 16.9,
    'z': 16.7,
    'redshift': 0.01
}])

# Preprocess
custom_input_scaled = scaler.transform(custom_input)

# Predict
prediction = model.predict(custom_input_scaled)
predicted_class = class_encoder.inverse_transform(prediction)[0]

print("Predicted Class:", predicted_class)


# In[ ]:




