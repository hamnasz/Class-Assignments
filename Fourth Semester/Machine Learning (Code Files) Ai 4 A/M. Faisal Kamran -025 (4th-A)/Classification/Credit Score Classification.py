#!/usr/bin/env python
# coding: utf-8

# # Credit Score Classification Project
# ## Muhammad Faisal Kamran 2023-BS-AI-025

# ## About Dataset
# The dataset contains 100,000 records of customer financial behavior with 28 features, including income, debt, credit history, and payment patterns.
# Key features include
# - Annual_Income and Monthly_Inhand_Salary
# - Num_Bank_Accounts, Num_Credit_Card
# - Interest_Rate
# - Num_of_Loan and Delay_from_due_date
# - Num_of_Delayed_Payment
# - Credit_Mix
# - Outstanding_Debt
# - Credit_Utilization_Ratio and Credit_History_Age
# - Total_EMI_per_month
# - Monthly_Balance
# 

# ## Introduction to Python and Libraries for Machine Learning, Environmental Setup

# ### Importing Libraries

# In[1]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.impute import SimpleImputer
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import LinearSVC
from sklearn.metrics import classification_report, confusion_matrix
import warnings
warnings.filterwarnings("ignore")


# ### Reading Dataset

# In[2]:


df = pd.read_csv('train.csv')


# ## Exploring Dataset

# In[3]:


df.head()


# In[4]:


df.tail()


# In[5]:


df.sample()


# In[6]:


df.describe()


# ## Handling missing values, data normalization, standardization, Data visualization

# ### Handling missing values

# In[7]:


df.isnull().sum()


# In[8]:


for col in df.columns:
    if df[col].dtype == 'object':
        df[col] = df[col].replace(['', 'NA', 'NaN'], np.nan)
        df[col].fillna(df[col].mode()[0], inplace=True)
    else:
        df[col].replace(['', 'NA', 'NaN'], np.nan, inplace=True)
        df[col] = pd.to_numeric(df[col], errors='coerce')
        df[col].fillna(df[col].mean(), inplace=True)


# ### Encode categorical columns

# In[9]:


categorical_cols = df.select_dtypes(include='object').columns
le = LabelEncoder()
for col in categorical_cols:
    df[col] = le.fit_transform(df[col])


# ### Visualizations

# In[10]:


plt.figure(figsize=(8, 5))
sns.countplot(x='Credit_Score', data=df)
plt.title('Distribution of Credit Scores')
plt.show()


# In[11]:


plt.figure(figsize=(12, 6))
sns.heatmap(df.corr(), annot=False, cmap='coolwarm')
plt.title('Correlation Matrix')
plt.show()


# ### Select only 12 relevant features for training and prediction

# In[12]:


selected_features = [
    'Annual_Income',
    'Monthly_Inhand_Salary',
    'Num_Bank_Accounts',
    'Num_Credit_Card',
    'Interest_Rate',
    'Num_of_Loan',
    'Delay_from_due_date',
    'Num_of_Delayed_Payment',
    'Credit_Mix',
    'Outstanding_Debt',
    'Credit_History_Age',
    'Monthly_Balance'
]

X = df[selected_features]
y = df['Credit_Score']


# ### Normalize/standardize features

# In[13]:


scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)


# ## Data Preprocessing

# ### Correlation Analysis

# In[14]:


plt.figure(figsize=(12, 6))
sns.heatmap(df.corr(), annot=False, cmap='coolwarm')
plt.title('Correlation Matrix')
plt.show()


# ### Outlier Detection

# In[15]:


plt.figure(figsize=(15, 10))
for i, feature in enumerate(['Annual_Income', 'Monthly_Inhand_Salary', 'Outstanding_Debt', 'Monthly_Balance']):
    plt.subplot(2, 2, i+1)
    sns.boxplot(data=df, x=feature)
    plt.title(f'Boxplot of {feature}')
plt.tight_layout()
plt.show()


# ### Train-Test Split

# In[16]:


X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)


# ## Logistic Regression

# In[17]:


log_reg = LogisticRegression(max_iter=1000)
log_reg.fit(X_train, y_train)
y_pred_log = log_reg.predict(X_test)
print("\nLogistic Regression Report:\n", classification_report(y_test, y_pred_log))


# ## Decision Tree

# In[18]:


dt = DecisionTreeClassifier(random_state=42)
dt.fit(X_train, y_train)
y_pred_dt = dt.predict(X_test)
print("\nDecision Tree Report:\n", classification_report(y_test, y_pred_dt))


# ## Linear Support Vector Machine

# In[19]:


svm = LinearSVC(max_iter=10000)
svm.fit(X_train, y_train)
y_pred_svm = svm.predict(X_test)
print("\nLinear SVM Report:\n", classification_report(y_test, y_pred_svm))


# ## Evaluation Metrics

# In[22]:


from sklearn.metrics import accuracy_score, confusion_matrix, ConfusionMatrixDisplay, roc_auc_score, roc_curve, auc

def evaluate_and_plot(model, X_test, y_test, model_name, is_binary=False):
    y_pred = model.predict(X_test)
    acc = accuracy_score(y_test, y_pred)
    cm = confusion_matrix(y_test, y_pred)

    print(f"\n{model_name} Accuracy: {acc:.4f}")
    print(f"{model_name} Confusion Matrix:\n{cm}")

    disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=np.unique(y_test))
    disp.plot(cmap='Blues')
    plt.title(f'{model_name} - Confusion Matrix')
    plt.show()

    if is_binary and hasattr(model, "predict_proba"):
        y_prob = model.predict_proba(X_test)[:, 1]
        fpr, tpr, _ = roc_curve(y_test, y_prob)
        roc_auc = auc(fpr, tpr)
        print(f"{model_name} AUC Score: {roc_auc:.4f}")

        plt.figure()
        plt.plot(fpr, tpr, label=f'AUC = {roc_auc:.2f}')
        plt.plot([0, 1], [0, 1], 'k--')
        plt.xlabel('False Positive Rate')
        plt.ylabel('True Positive Rate')
        plt.title(f'{model_name} - ROC Curve')
        plt.legend(loc='lower right')
        plt.show()

is_binary = len(np.unique(y_test)) == 2

evaluate_and_plot(log_reg, X_test, y_test, "Logistic Regression", is_binary=is_binary)
evaluate_and_plot(dt, X_test, y_test, "Decision Tree", is_binary=is_binary)
evaluate_and_plot(svm, X_test, y_test, "Linear SVM", is_binary=False)  


# ## Training, Evaluating Model and Output of the Model

# In[24]:


print("\nCredit Score Prediction : ")
a = float(input("Annual Income: "))
b = float(input("Monthly Inhand Salary: "))
c = float(input("Number of Bank Accounts: "))
d = float(input("Number of Credit cards: "))
e = float(input("Interest rate: "))
f = float(input("Number of Loans: "))
g = float(input("Average number of days delayed by the person: "))
h = float(input("Number of delayed payments: "))
i = int(input("Credit Mix (Bad: 0, Standard: 1, Good: 2): "))
j = float(input("Outstanding Debt: "))
k = float(input("Credit History Age: "))
l = float(input("Monthly Balance: "))

user_features = np.array([[a, b, c, d, e, f, g, h, i, j, k, l]])
user_features_scaled = scaler.transform(user_features)

print("Predicted Credit Score =", dt.predict(user_features_scaled)[0])


# In[ ]:




