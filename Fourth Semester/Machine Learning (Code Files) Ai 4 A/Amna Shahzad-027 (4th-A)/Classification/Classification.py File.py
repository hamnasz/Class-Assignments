# %% [markdown]
# # EXTROVERT VS INTROVERT BEHAVIOUR CLASSIFICATION DATASET

# %% [markdown]
# # DESCRIPTION
# Overview
# 
# Dive into the Extrovert vs. Introvert Personality Traits Dataset, a rich collection of behavioral and social data designed to explore the spectrum of human personality. This dataset captures key indicators of extroversion and introversion, making it a valuable resource for psychologists, data scientists, and researchers studying social behavior, personality prediction, or data preprocessing techniques.
# 
# Context
# 
# Personality traits like extroversion and introversion shape how individuals interact with their social environments. This dataset provides insights into behaviors such as time spent alone, social event attendance, and social media engagement, enabling applications in psychology, sociology, marketing, and machine learning. Whether you're predicting personality types or analyzing social patterns, this dataset is your gateway to uncovering fascinating insights.
# 
# Dataset Details
# 
# Size: The dataset contains 2,900 rows and 8 columns.
# 
# Features:
# 
#     - Time_spent_Alone: Hours spent alone daily (0–11).
#     - Stage_fear: Presence of stage fright (Yes/No).
#     - Social_event_attendance: Frequency of social events (0–10).
#     - Going_outside: Frequency of going outside (0–7).
#     - Drained_after_socializing: Feeling drained after socializing (Yes/No).
#     - Friends_circle_size: Number of close friends (0–15).
#     - Post_frequency: Social media post frequency (0–10).
#     - Personality: Target variable (Extrovert/Introvert).*
# Data Quality: Includes some missing values, ideal for practicing imputation and preprocessing.
# Format: Single CSV file, compatible with Python, R, and other tools.*
# 
# Data Quality Notes
# 
# Contains missing values in columns like Time_spent_Alone and Going_outside, offering opportunities for data cleaning practice.
# Balanced classes ensure robust model training.
# Binary categorical variables simplify encoding tasks.
# Potential Use Cases
# 
# Build machine learning models to predict personality types.
# Analyze correlations between social behaviors and personality traits.
# Explore social media engagement patterns.
# Practice data preprocessing techniques like imputation and encoding.
# Create visualizations to uncover behavioral trends.

# %% [markdown]
# # 1. Importing Libraries

# %%
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.impute import SimpleImputer
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC
from sklearn.metrics import classification_report, confusion_matrix
from imblearn.over_sampling import SMOTE
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

# %% [markdown]
# # 2. Reading Data

# %%
df = pd.read_csv('Downloads/Introvert Vs Extrovert/personality_dataset.csv')

# %% [markdown]
# # 3. Exploring Data

# %%
df.info()

# %%
df.describe()

# %%
df.head()

# %%
df.tail()

# %%
type(df)

# %%
df.sample(3)

# %%
df.dtypes

# %%
df.shape

# %%
df.ndim

# %% [markdown]
# # 4. Feature Names

# %%
df.columns

# %%
df["Personality"].value_counts()

# %%
df.isnull()

# %%
df.isnull().any()

# %%
print('Missing data sum :')
df.isnull().sum()

# %%
print('\nMissing data percentage (%):')
print(df.isnull().sum()/df.count()*100)

# %% [markdown]
# # 5. SEPARATE CATEGORICAL AND NUMERICAL FEATURES

# %%
cat_features = [feature for feature in df.columns if df[feature].dtypes == 'O']
print('Number of categorical variables: ', len(cat_features))
print('*'*80)
print('Categorical variables column name:',cat_features)

# %%
cd = pd.DataFrame(cat_features)
cd.head()

# %%
df.info()

# %%
numerical_features = [feature for feature in df.columns if df[feature].dtypes != 'O']
print('Number of numerical variables: ', len(numerical_features))
print('*'*80)
print('Numerical Variables Column: ',numerical_features)

# %%
print('*'*10)

# %%
numerical_features

# %% [markdown]
# # 6. CHECK DUPLICATE VALUES

# %%
df.duplicated()

# %%
df.duplicated().sum()

# %% [markdown]
# # 7. Correlation matrix

# %%
plt.figure(figsize=(8, 6))
sns.heatmap(df.corr(numeric_only=True), annot=True, cmap="coolwarm")
plt.title("Correlation Matrix")
plt.show()

# %% [markdown]
# # 8. Plot Heatmap

# %%
numeric_df = df.select_dtypes(include=['number'])
corr = numeric_df.corr()
fig = plt.figure(figsize=(8, 6))
sns.heatmap(corr, linewidths=.5, cmap="RdBu", annot=True, fmt="g")
plt.show()

# %%
df_corr = df.copy()
from sklearn.preprocessing import LabelEncoder
import seaborn as sns
import matplotlib.pyplot as plt

for col in df_corr.select_dtypes(include=['object']).columns:
    le = LabelEncoder()
    df_corr[col] = le.fit_transform(df_corr[col])

corr_matrix = df_corr.corr().round(2)
sns.heatmap(corr_matrix, annot=True, cmap="coolwarm", linewidths=0.5)

# %%
mask = np.triu(np.ones_like(corr_matrix, dtype=bool))

plt.figure(figsize=(10,10))
sns.heatmap(corr_matrix, center=0, vmin=-1, vmax=1, mask=mask, annot=True, cmap='BrBG')
plt.show()

# %%
cat_features = [feature for feature in df.columns if df[feature].dtypes == 'O']
print('Number of categorical variables: ', len(cat_features))
print('*'*80)
print('Categorical variables column name:',cat_features)

# %%
numerical_features = [feature for feature in df.columns if df[feature].dtypes != 'O']
print('Number of numerical variables: ', len(numerical_features))
print('*'*80)
print('Numerical Variables Column: ',numerical_features)

# %% [markdown]
# # 9. Visualizing Categorical Features

# %%
for col in df.columns:
    sns.countplot(x=col, data=df)
    plt.title(f"Distribution of {col}")
    plt.xticks(rotation=45)
    plt.show()

# %% [markdown]
# # 10. Barplot of Numerical Features

# %%
for col in numerical_features:
    plt.figure(figsize=(6,3), dpi=100)
    sns.barplot(data=df,x='Going_outside',y=col,palette='gist_rainbow_r')

# %% [markdown]
# # 11. Handling Missing Values

# %%
df.head()

# %%
df.isnull().sum()

# %%
df["Going_outside"]=df["Going_outside"].fillna(df["Going_outside"].mean())

# %%
df["Post_frequency"]=df["Post_frequency"].fillna(df["Post_frequency"].mean())

# %%
df["Friends_circle_size"]=df["Friends_circle_size"].fillna(df["Friends_circle_size"].mean())

# %%
df["Time_spent_Alone"]=df["Time_spent_Alone"].fillna(df["Time_spent_Alone"].mean())

# %%
df["Social_event_attendance"]=df["Social_event_attendance"].fillna(df["Social_event_attendance"].mean())

# %%
df.isnull().sum()

# %%
df.head()

# %% [markdown]
# # 12. Dropping Irrelevent Columns

# %%
train  = df.drop(['Personality'],axis=1)
train

# %%
train.columns

# %%
train.shape

# %%
train.info()

# %%
train_data_cat = train.select_dtypes("object")
train_data_num = train.select_dtypes("number")

# %%
train_data_cat.head(3)

# %%
train_data_num.head(3)

# %% [markdown]
# # 13. Converting categorical features into numerical

# %%
train_data_cata_encoded=pd.get_dummies(train_data_cat, columns=train_data_cat.columns.to_list())
train_data_cata_encoded.head()

# %%
data=pd.concat([train_data_cata_encoded,train_data_num],axis=1,join="outer")
data.head()

# %%
categorical_cols = X.select_dtypes(include='object').columns
print("Categorical columns:", categorical_cols.tolist())

# %%
from sklearn.preprocessing import LabelEncoder

le = LabelEncoder()
for col in categorical_cols:
    X[col] = le.fit_transform(X[col])

# %%
from sklearn.model_selection import train_test_split

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)


# %% [markdown]
# # 14. Separate Independent and Dependent

# %%
X = df.drop("Personality", axis=1)
y = df["Personality"]

# %%
print(X.shape)
print(y.shape)

# %% [markdown]
# # 15. Scaling Data

# %%
from sklearn.preprocessing import StandardScaler

x_numeric = X.select_dtypes(include=['number'])
sc = StandardScaler()
x_scaled = sc.fit_transform(x_numeric)

# %% [markdown]
# X

# %% [markdown]
# # 16. Splitting data into Training and Testing

# %%
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.pipeline import Pipeline
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, confusion_matrix,classification_report
from sklearn.svm import SVC
import pickle

from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import AdaBoostClassifier
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.model_selection import GridSearchCV, cross_val_score, StratifiedKFold, learning_curve

# %% [markdown]
# # 17. Splitting the dataset

# %% [markdown]
# - training data 70%
# - testing data 30%

# %%
X_train, X_test, y_train, y_test = train_test_split(x_scaled, y, test_size=0.2, random_state=42)

# %%
X_train.shape, X_test.shape

# %%
# Building Classifiers

# %%
accuracy = {}

# %% [markdown]
# # 18. Logistic Regression

# %%
logreg = LogisticRegression()

# %%
logreg.fit(X_train, y_train)

# %%
y_pred_log = logreg.predict(X_test)

# %% [markdown]
# # 19. Confusion Matrix

# %%
from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred_log)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")

# %% [markdown]
# # 20. Classification Report

# %%
print(classification_report(y_test,y_pred_log))

# %% [markdown]
# # 21. Predicting

# %%
y_pred_test = logreg.predict(X_test)

test = pd.DataFrame({
    'Actual':y_test,
    'Y test predicted':y_pred_test
})

# %%
test.sample(10)

# %% [markdown]
# # 22. DecisionTreeClassifier

# %%
dtc = DecisionTreeCla.ssifier(max_depth=3)
dtc.fit(X_train, y_train)
y_pred2 = dtc.predict(X_test)
print(accuracy_score(y_test, y_pred2))
accuracy[str(dtc)] = accuracy_score(y_test, y_pred2)*100

# %%
from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred2)
conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")

# %%
print(classification_report(y_test,y_pred2))

# %%
y_pred_test = dtc.predict(X_test)

test = pd.DataFrame({
    'Actual':y_test,
    'Y test predicted':y_pred_test
})

# %%
test.head(5)

# %%
rfc = RandomForestClassifier(max_depth=5)
rfc.fit(X_train, y_train)
y_pred3 = rfc.predict(X_test)
print(accuracy_score(y_test, y_pred3))
accuracy[str(rfc)] = accuracy_score(y_test, y_pred3)*100

# %%
from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred3)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")

# %%
gbc = GradientBoostingClassifier(n_estimators=100, learning_rate=0.1)
gbc.fit(X_train, y_train)
y_pred4 = gbc.predict(X_test)
print(accuracy_score(y_test, y_pred4))
accuracy[str(gbc)] = accuracy_score(y_test, y_pred4)*100

# %%
from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred4)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")

# %% [markdown]
# # 23. SVM 

# %%
svc = SVC()
svc.fit(X_train, y_train)
y_pred5 = svc.predict(X_test)
print(accuracy_score(y_test, y_pred5))
accuracy[str(svc)] = accuracy_score(y_test, y_pred5)*100

# %%
from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred5)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")

# %%
accuracy

# %% [markdown]
# # 24. Handling this data using SMOTE

# %%
from imblearn.over_sampling import SMOTE

# %%
sm = SMOTE(random_state=42)
X_res, y_res = sm.fit_resample(x_scaled, y)

# %% [markdown]
# # 25. Split the oversampling data

# %%
X_train_res, X_test_res, y_train_res, y_test_res = train_test_split(X_res, y_res, test_size=0.2, random_state=42)

# %%
print(X_train.shape)
print(X_test.shape)
print(y_train.shape)
print(y_test.shape)

# %%
lr = LogisticRegression(max_iter=200)
lr.fit(X_train, y_train)
y_pred1 = lr.predict(X_test)
print(accuracy_score(y_test, y_pred1))
accuracy[str(lr)] = accuracy_score(y_test, y_pred1)*100

# %%
from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred1)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")

# %%
print(classification_report(y_test,y_pred1))

# %%
y_pred_test = lr.predict(X_test)

test = pd.DataFrame({
    'Actual':y_test,
    'Y test predicted':y_pred_test
})

# %%
test.head()

# %%
from sklearn.preprocessing import LabelEncoder

le = LabelEncoder()
y = le.fit_transform(df['Going_outside']) 

# %%
from sklearn.model_selection import train_test_split

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

# %% [markdown]
# # 26. Deep Learning 

# %%
import tensorflow as tf
from tensorflow import keras

# %% [markdown]
# # 27. Create Neural Network

# %% [markdown]
# - Creating sequnetial ANN Network
# - Creating 5 layers Network
# - Activation is "Relu", "Sigmoid"
# - Last layer is output layer
# - Problem is binary classification thats way output node is 1 and activation is "sigmoid"

# %%
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

# %% [markdown]
# # 28. model architecture

# %%
model = Sequential()
model.add(Dense(64, activation='relu', input_dim=7))  
model.add(Dense(64, activation='relu'))
model.add(Dense(32, activation='relu'))
model.add(Dense(16, activation='relu'))
model.add(Dense(8, activation='relu'))
model.add(Dense(1, activation='sigmoid')) 

# %% [markdown]
# # 29. Compile the model

# %%
model.compile(
    loss='binary_crossentropy',
    optimizer='adam',
    metrics=['accuracy']
)

# %% [markdown]
# # 30. Fit the model on training data

# %%
model.fit(
    X_train,
    y_train,
    epochs=100,
    batch_size=100,
    validation_split=0.2,
    verbose=1
)

# %% [markdown]
# # 31. Evaluate The Model

# %%
model.evaluate(X_test, y_test)

# %%
y_pred=model.predict(X_test).flatten()
y_pred=np.round(y_pred)

y_pred[:11]
y_test[:11]

from sklearn.metrics import classification_report

print(classification_report(y_test, y_pred))

# %% [markdown]
# # 32. CONFUSION MATRIX

# %%
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.metrics import confusion_matrix

cm = confusion_matrix(y_test, y_pred)

labels = sorted(list(set(y_test)))

conf_matrix = pd.DataFrame(data=cm,
                           columns=[f'Predicted:{l}' for l in labels],
                           index=[f'Actual:{l}' for l in labels])

plt.figure(figsize=(10, 8))
sns.heatmap(conf_matrix, annot=True, fmt='d', cmap="YlGnBu")
plt.title("Confusion Matrix")
plt.ylabel("Actual Label")
plt.xlabel("Predicted Label")
plt.show()


# %% [markdown]
# # CONCLUSION

# %% [markdown]
# - Data Preprocessing:
# Cleaned the dataset and handled categorical variables.
# Ensured features were converted to numerical types for model compatibility.
# 
# - Model Building:
# Created a Neural Network using Keras Sequential API.
# Architecture included input, hidden, and output layers with activation functions (relu, sigmoid).
# 
# - Model Training:
# Trained the model with X_train and y_train using 100 epochs and batch size of 100.
# Used validation_split=0.2 to monitor validation performance.
# 
# - Predictions & Evaluation:
# Made predictions on X_test.
# Evaluated performance using a confusion matrix and classification metrics.
# 
# - Results:
# Model successfully learned the patterns in data.
# Confusion matrix shows reasonable accuracy with room for improvement in certain misclassified cases.

# %% [markdown]
# # THE END


