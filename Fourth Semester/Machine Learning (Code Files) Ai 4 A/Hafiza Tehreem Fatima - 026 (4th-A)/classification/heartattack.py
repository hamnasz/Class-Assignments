#!/usr/bin/env python
# coding: utf-8

# # Description
# A heart attack dataset with 1319 samples and 9 fields: 8 input features (age, gender, heart rate, systolic BP, diastolic BP, blood sugar, CK-MB, Troponin) and 1 output label (heart attack class: positive or negative). The dataset aims to identify key factors contributing to heart attacks.

# In[1]:


get_ipython().system('jupyter nbconvert --to script heart attack (classification).ipynb')


# # Import libraries

# In[1334]:


import pandas as pd 
import numpy as np 
import os 

import matplotlib.pyplot as plt 
import seaborn as sns

from sklearn.preprocessing import FunctionTransformer  
from sklearn.preprocessing import OneHotEncoder 
from sklearn.preprocessing import StandardScaler 
from imblearn.over_sampling import RandomOverSampler 
from sklearn.decomposition import PCA 

from sklearn.neighbors import KNeighborsClassifier 
from sklearn.linear_model import LogisticRegression
from sklearn.naive_bayes import GaussianNB
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier

import tensorflow
from tensorflow import keras
from tensorflow.keras import Sequential
from tensorflow.keras.layers import Dense

from sklearn.metrics import accuracy_score


# # Reading data

# In[1337]:


import pandas as pd
import numpy as np
data = pd.read_csv("Heart Attack.csv")


# In[1339]:


data.head()


# In[1341]:


data.tail()


# In[1343]:


type(data)


# # Exploring data

# In[1346]:


data.sample(3)


# In[1348]:


data.dtypes


# In[1350]:


data.info()


# In[1352]:


data.describe()


# In[1354]:


data.shape


# In[1356]:


data.ndim


# In[1358]:


data.columns


# In[1360]:


data["age"].nunique()


# In[1362]:


data.age.nunique()


# In[1364]:


data.age.unique()


# In[1366]:


data["age"].unique()


# In[1368]:


data["gender"].unique()


# In[1370]:


data.head(3)


# In[1372]:


data.age.value_counts(True)


# In[1374]:


data.age.value_counts().rename('count'),

data.age.value_counts(True).rename('%').mul(100)


# In[1376]:


data["age"].value_counts()


# In[1378]:


data["age"].sample(20)


# In[1380]:


data.age.value_counts()


# In[1382]:


import matplotlib.pyplot as plt
import seaborn as sns

sns.countplot(data=data , x='age')
plt.title('Number of Patient')


# In[1383]:


data.info()


# In[1384]:


data.sample(20)


# In[1385]:


data.columns


# In[1390]:


data["age"].value_counts()


# # Missing values

# In[1393]:


data.isnull()


# In[1395]:


data.isnull().any()


# In[1397]:


data.isnull().sum()


# In[1399]:


print('Missing data sum :')
print(data.isnull().sum())

print('\nMissing data percentage (%):')
print(data.isnull().sum()/data.count()*100)


# # Seperate Categorical and Numerical Features

# In[1402]:


cat_features = [feature for feature in data.columns if data[feature].dtypes == 'O']
print('Number of categorical variables: ', len(cat_features))
print('*'*80)
print('Categorical variables column name:',cat_features)


# In[1404]:


cd = pd.DataFrame(cat_features)
cd.head()


# In[1406]:


data.info()


# In[1408]:


numerical_features = [feature for feature in data.columns if data[feature].dtypes != 'O']
print('Number of numerical variables: ', len(numerical_features))
print('*'*80)
print('Numerical Variables Column: ',numerical_features)


# In[1410]:


print('*'*10)


# In[1412]:


numerical_features


# In[1414]:


cat_features


# # Checking Duplicating Values

# In[1417]:


data.gender.duplicated()


# In[1419]:


data.duplicated().sum()


# In[1421]:


data['gender'].unique()


# In[1423]:


data['age'].sample(10)


# In[1425]:


data['age'].unique()


# In[1427]:


data['impluse'].unique()


# In[1429]:


data['glucose'].unique()


# In[1431]:


data['kcm'].unique()


# In[1433]:


data['class'].nunique()


# In[1435]:


data['class'].unique()


# In[1437]:


data.columns


# In[1439]:


data['troponin'].unique()


# In[1441]:


data['age'].nunique()


# In[1443]:


data['age'].unique()


# In[1445]:


corr = data.drop(columns=['class']).corr()

plt.figure(figsize=(8, 8))
sns.heatmap(data=corr, annot=True, cmap='Spectral')
plt.title("Correlation Matrix")
plt.show()


# In[1446]:


fig = plt.figure(figsize=(12, 8))
corr = data.drop(columns=['class']).corr()
sns.heatmap(corr, linewidths=0.5, cmap="RdBu", annot=True, fmt="g")
plt.title("Correlation Matrix of Heart Attack Dataset")
plt.show()


# In[1448]:


corr_matrix = data.drop(columns=['class']).corr().round(2)
corr_matrix


# In[1449]:


mask = np.triu(np.ones_like(corr_matrix, dtype=bool))

plt.figure(figsize=(10,10))
sns.heatmap(corr_matrix, center=0, vmin=-1, vmax=1, mask=mask, annot=True, cmap='BrBG')
plt.show()


# In[1451]:


cat_features = [feature for feature in data.columns if data[feature].dtypes == 'O']
print('Number of categorical variables: ', len(cat_features))
print('*'*80)
print('Categorical variables column name:',cat_features)


# In[1453]:


numerical_features = [feature for feature in data.columns if data[feature].dtypes != 'O']
print('Number of numerical variables: ', len(numerical_features))
print('*'*80)
print('Numerical Variables Column: ',numerical_features)


# # Visualizing Categorical Features

# In[1458]:


for col in cat_features[:]:
    plt.figure(figsize=(6,3), dpi=100)
    sns.countplot(data=data,x=col,hue ='age',palette='gist_rainbow_r')
    plt.legend(loc=(1.05,0.5))


# In[1459]:


numerical_features = ['age', 'impluse', 'pressurehight', 'pressurelow', 'glucose', 'kcm', 'troponin']

for col in numerical_features:
    plt.figure(figsize=(6, 3), dpi=100)
    sns.barplot(data=data, x='gender', y=col, hue='gender', palette='gist_rainbow_r', legend=False)
    plt.title(f'{col} vs Gender')
    plt.show()


# # Handling Missing Values

# In[1462]:


data.head()


# In[1464]:


data.isnull().sum()


# In[1467]:


data["glucose"] = data["glucose"].fillna(data["glucose"].mean())


# In[1469]:


data.isnull().sum()


# # dropping irrelevant feature

# In[1472]:


train  = data.drop(['class'],axis=1)
train


# In[1474]:


train.columns


# In[1476]:


train.shape


# In[1478]:


train.info()


# In[1480]:


train_data_cat = train.select_dtypes("object")
train_data_num = train.select_dtypes("number")


# In[1482]:


train_data_cat.head(3)


# In[1484]:


train_data_num.head(3)


# # Converting categorical features into numerical

# In[1487]:


data_encoded = pd.get_dummies(data, columns=['gender'])
data_encoded.head()


# In[1489]:


data = pd.concat([data_encoded, train_data_num], axis=1, join="outer")
data.head()


# # seperate dependant and independant feature

# In[1492]:


y = data['age']
x = data.drop('age', axis = 1)


# In[1494]:


print(x.shape)
print(y.shape)


# # scailing the data

# In[1497]:


x = data.drop(columns=['class'])

sc = StandardScaler()
x = sc.fit_transform(x)


# In[1499]:


x


# # Splitting data into Training and Testing

# In[1502]:


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


# # Splitting the dataset
# training data 70%
# 
# testing data 30%

# In[1505]:


X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.3, random_state=7)
X_train.shape, X_test.shape


# # Building Classifiers

# In[1508]:


accuracy = {}


# # Confusion Matrix

# In[1511]:


import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import confusion_matrix, accuracy_score




# 
# # Step 1: Encode 'class' as 0 (negative) and 1 (positive)

# In[1514]:


data['class'] = data['class'].map({'negative': 0, 'positive': 1})


# 
# # Step 2: Separate features (X) and target (y)

# In[1517]:


X = data.drop(columns=['class'])
y = data['class']


# 
# # Step 3: Scale the numeric features (StandardScaler)

# In[1520]:


sc = StandardScaler()
X_scaled = sc.fit_transform(X)


# 
# 
# # Step 4: Split the data into training and testing sets (70% training, 30% testing)

# In[1523]:


X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.3, random_state=42)


# 
# # Step 5: Initialize and train the Logistic Regression model

# In[1526]:


lr = LogisticRegression(max_iter=200)
lr.fit(X_train, y_train)


# 
# 
# # Step 6: Make predictions on the test data

# In[1529]:


y_pred = lr.predict(X_test)


# 
# 
# 
# # Step 7: Calculate accuracy

# In[1532]:


accuracy = accuracy_score(y_test, y_pred)
print(f'Accuracy: {accuracy * 100:.2f}%')


# 
# # Step 8: Generate confusion matrix

# In[1535]:


cm = confusion_matrix(y_test, y_pred)


# 
# # Step 9: Create a DataFrame for confusion matrix visualization

# In[1538]:


conf_matrix = pd.DataFrame(data=cm, columns=['Predicted: 0', 'Predicted: 1'],
                           index=['Actual: 0', 'Actual: 1'])


# 
# # Step 10: Plot confusion matrix with heatmap

# In[1553]:


plt.figure(figsize=(8, 5))
sns.heatmap(conf_matrix, annot=True, fmt='d', cmap="YlGnBu", cbar=False)
plt.title("Confusion Matrix")
plt.show()


# # Classification report

# In[1560]:


from sklearn.preprocessing import LabelEncoder

le = LabelEncoder()
data['class'] = le.fit_transform(data['class']) 


# # Predicting

# In[1563]:


y_pred_test = lr.predict(X_test)

test = pd.DataFrame({
    'Actual':y_test,
    'Y test predicted':y_pred_test
})


# In[1565]:


test.sample(10)


# # DecisionTreeClassifier

# In[1568]:


from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score



# # Initialize the DecisionTreeClassifier with max_depth=3

# In[1571]:


dtc = DecisionTreeClassifier(max_depth=3)


# 
# # Fit the model on the training data

# In[1574]:


dtc.fit(X_train, y_train)


# 
# 
# 
# # Predict on the test set

# In[1577]:


y_pred2 = dtc.predict(X_test)


# 
# # Calculate and print the accuracy score

# In[1580]:


accuracy_dtc = accuracy_score(y_test, y_pred2)
print(f"Decision Tree Accuracy: {accuracy_dtc * 100:.2f}%")


# 
# 
# 
# # Store the accuracy in the accuracy dictionary

# In[1583]:


accuracy = {}
accuracy[str(dtc)] = accuracy_dtc * 100


# 
# # Optionally, print the accuracy dictionary

# In[1586]:


print("Accuracy dictionary:", accuracy)


# In[1588]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred2)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# In[1590]:


print(classification_report(y_test,y_pred2))


# In[1592]:


y_pred_test = dtc.predict(X_test)

test = pd.DataFrame({
    'Actual':y_test,
    'Y test predicted':y_pred_test
})


# In[1594]:


test.head(5)


# In[1596]:


rfc = RandomForestClassifier(max_depth=5)
rfc.fit(X_train, y_train)
y_pred3 = rfc.predict(X_test)
print(accuracy_score(y_test, y_pred3))
accuracy[str(rfc)] = accuracy_score(y_test, y_pred3)*100


# In[1598]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred3)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# In[1600]:


gbc = GradientBoostingClassifier(n_estimators=100, learning_rate=0.1)
gbc.fit(X_train, y_train)
y_pred4 = gbc.predict(X_test)
print(accuracy_score(y_test, y_pred4))
accuracy[str(gbc)] = accuracy_score(y_test, y_pred4)*100


# In[1601]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred4)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# # SVM

# In[1605]:


svc = SVC()
svc.fit(X_train, y_train)
y_pred5 = svc.predict(X_test)
print(accuracy_score(y_test, y_pred5))
accuracy[str(svc)] = accuracy_score(y_test, y_pred5)*100


# In[1607]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred5)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# In[1608]:


accuracy


# # Handling this data using SMOTE

# In[1612]:


from imblearn.over_sampling import SMOTE


# In[1614]:


from imblearn.over_sampling import SMOTE
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler
import pandas as pd




# 
# # Assuming 'data' is your dataframe and 'class' is the target column

# In[1617]:


X = data.drop('class', axis=1)  
y = data['class'] 


# # Step 1: Split the dataset into training and testing sets (80% train, 20% test)

# In[1620]:


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


# # Step 2: Apply SMOTE to the training set to balance the classes

# In[1623]:


smote = SMOTE(random_state=42)
X_train_res, y_train_res = smote.fit_resample(X_train, y_train)


# # Step 3: Standardize the features using StandardScaler (optional but recommended)
# 

# In[1626]:


scaler = StandardScaler()
X_train_res = scaler.fit_transform(X_train_res)
X_test = scaler.transform(X_test)


# # Step 4: Initialize and train the Decision Tree Classifier
# 

# In[1629]:


dtc = DecisionTreeClassifier(max_depth=3)
dtc.fit(X_train_res, y_train_res)


# 
# 
# # Step 5: Make predictions on the test set
# 

# In[1632]:


y_pred2 = dtc.predict(X_test)


# 
# 
# 
# # Step 6: Calculate and print the accuracy score
# 

# In[1635]:


accuracy_dtc = accuracy_score(y_test, y_pred2)
print(f"Decision Tree Accuracy with SMOTE: {accuracy_dtc * 100:.2f}%")


# In[ ]:





# # Splitting the oversampling data

# In[1639]:


print(X_train.shape)
print(X_test.shape)
print(y_train.shape)
print(y_test.shape)


# In[1641]:


lr = LogisticRegression(max_iter=200)
lr.fit(X_train, y_train)
y_pred1 = lr.predict(X_test)
print(accuracy_score(y_test, y_pred1))
accuracy[str(lr)] = accuracy_score(y_test, y_pred1)*100


# In[1643]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,y_pred1)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# In[1645]:


print(classification_report(y_test,y_pred1))


# In[1647]:


y_pred_test = lr.predict(X_test)

test = pd.DataFrame({
    'Actual':y_test,
    'Y test predicted':y_pred_test
})


# In[1649]:


test.head()


# In[1651]:


knn_model = KNeighborsClassifier(n_neighbors=3)
knn_model.fit(X_train,y_train)
knn_predict = knn_model.predict(X_test)
print(accuracy_score(y_test, knn_predict))
accuracy[str(lr)] = accuracy_score(y_test, knn_predict)*100


# In[1653]:


from sklearn.metrics import confusion_matrix

cm=confusion_matrix(y_test,knn_predict)

conf_matrix=pd.DataFrame(data=cm,columns=['Predicted:0','Predicted:1'],index=['Actual:0','Actual:1'])
plt.figure(figsize = (8,5))
sns.heatmap(conf_matrix, annot=True,fmt='d',cmap="YlGnBu")


# In[1655]:


print(classification_report(y_test,knn_predict))


# In[1657]:


y_pred_test = knn_model.predict(X_test)

test = pd.DataFrame({
    'Actual':y_test,
    'Y test predicted':y_pred_test
})


# In[1659]:


test.sample(10)


# # Deep Learning

# In[1662]:


import tensorflow as tf
from tensorflow import keras


# # Create neural network

# In[1665]:


model=keras.Sequential([
    keras.layers.Dense(4800,input_shape=[21], activation='relu'),
    keras.layers.Dense(2000, activation='relu'),
    keras.layers.Dense(1000, activation='relu'),
    keras.layers.Dense(1000, activation='relu'), 
    keras.layers.Dense(1,activation="sigmoid")
])
model.summary()


# In[1667]:


model.compile(loss='binary_crossentropy', optimizer='adam',metrics=['accuracy'])


# In[1669]:


import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.utils import to_categorical
from imblearn.over_sampling import SMOTE


# # Step 1: Encode the target variable if it's categorical
# l

# In[1672]:


e = LabelEncoder()
data['class'] = le.fit_transform(data['class'])  # Converts string labels to 0, 1, ...


# # Step 2: Split data into features and target
# 

# In[1675]:


X = data.drop('class', axis=1)
y = data['class']


# 
# # Step 3: Train-test split
# 

# In[1678]:


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


# 
# 
# 
# # Step 4: Balance the training set using SMOTE
# 

# In[1681]:


sm = SMOTE(random_state=42)
X_train_res, y_train_res = sm.fit_resample(X_train, y_train)


# # Step 5: Scale the features

# In[1686]:


scaler = StandardScaler()
X_train_res = scaler.fit_transform(X_train_res)
X_test = scaler.transform(X_test)


# # Step 6: Convert target to categorical (for binary/multiclass classification)
# 

# In[1689]:


y_train_cat = to_categorical(y_train_res)
y_test_cat = to_categorical(y_test)


# # Step 7: Build the Neural Network model
# 

# In[1694]:


model = Sequential()
model.add(Dense(32, input_dim=X_train_res.shape[1], activation='relu'))
model.add(Dense(16, activation='relu'))
model.add(Dense(y_train_cat.shape[1], activation='softmax'))  # softmax for multi-class


# # Step 8: Compile the model
# 

# In[1697]:


model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])


# # Step 9: Train the model
# 

# In[1700]:


model.fit(X_train_res, y_train_cat, epochs=50, batch_size=16, verbose=1, validation_split=0.2)


# # Step 10: Evaluate the model
# 

# In[1703]:


loss, accuracy = model.evaluate(X_test, y_test_cat, verbose=0)
print(f"\nTest Accuracy: {accuracy*100:.2f}%")


# In[1705]:


corr = data.corr()
plt.figure(figsize=(8,8))
sns.heatmap(data=corr, annot=True, cmap='Spectral').set(title="Correlation Matrix")


# In[ ]:





# In[1708]:


from keras.models import Sequential
from keras.layers import Dense,Dropout
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.losses import BinaryCrossentropy
model = Sequential()
model.add(Dense(512,activation='relu',input_shape=(21,)))
model.add(Dense(512,activation='relu'))
model.add(Dropout(0.5))
model.add(Dense(256,activation='relu'))
model.add(Dense(256,activation='relu'))
model.add(Dropout(0.5))
model.add(Dense(128,activation='relu'))
model.add(Dense(128,activation='relu'))
model.add(Dropout(0.5))
model.add(Dense(1,activation = 'sigmoid'))
model.summary()


# In[1710]:


model.compile(loss='binary_crossentropy', optimizer='adam',metrics=['accuracy'])


# In[1712]:


from keras.callbacks import EarlyStopping
cb = EarlyStopping(
    monitor='accuracy',
    min_delta=0.001,
    patience=100,
    mode='auto')


# # Model 1: Simple Feedforward Neural Network

# In[1715]:


model1 = Sequential([
    Dense(32, input_dim=X_train.shape[1], activation='relu'),
    Dense(16, activation='relu'),
    Dense(y_train_cat.shape[1], activation='softmax')
])

model1.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
model1.fit(X_train, y_train_cat, epochs=50, batch_size=32, validation_split=0.2)


# # Evaluate

# In[1718]:


loss, acc = model1.evaluate(X_test, y_test_cat)
print("Model 1 Test Accuracy:", acc)



# # Confusion matrix

# In[1726]:


from sklearn.metrics import confusion_matrix
import seaborn as sns
import matplotlib.pyplot as plt




# 
# # Step 1: Predict using the model

# In[1729]:


y_pred_prob = model1.predict(X_test)  # Use model2 or model3 if you want
y_pred = np.argmax(y_pred_prob, axis=1)
y_true = np.argmax(y_test_cat, axis=1)


# 
# 
# # Step 2: Create confusion matrix

# In[1732]:


cm = confusion_matrix(y_true, y_pred)


# 
# # Step 3: Convert to DataFrame and plot

# In[1735]:


conf_matrix = pd.DataFrame(data=cm,
                           columns=['Predicted:0', 'Predicted:1'],
                           index=['Actual:0', 'Actual:1'])

plt.figure(figsize=(8, 5))
sns.heatmap(conf_matrix, annot=True, fmt='d', cmap="YlGnBu")
plt.title("Confusion Matrix")
plt.ylabel("Actual Class")
plt.xlabel("Predicted Class")
plt.show()


# In[ ]:




