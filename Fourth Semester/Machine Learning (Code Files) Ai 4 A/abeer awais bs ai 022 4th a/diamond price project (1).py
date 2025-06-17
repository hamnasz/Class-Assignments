#!/usr/bin/env python
# coding: utf-8

# # Import Libraries and Load Dataset

# In[4]:


import pandas as pd
import numpy as np
import plotly.express as px
import plotly.graph_objects as go

data = pd.read_csv("C:/Users/ADMIN/Downloads/diamonds.csv")
print(data.head())


# # View Last Few Rows

# In[5]:


data.tail()


# # Check Dataset Dimensions

# In[6]:


data.shape


# # View a Random Sample

# In[7]:


data.sample


# # Dataset Info Summary

# In[8]:


data.info()


# # Descriptive Statistics

# In[9]:


data.describe()


# # Check for Missing Values

# In[10]:


data.isnull().sum()


# # Remove Unnecessary Index Column

# In[11]:


if "Unnamed: 0" in data.columns:
    data = data.drop("Unnamed: 0", axis=1)


# # Clear Output in Jupyter Notebook

# In[12]:


from IPython.display import display, clear_output
clear_output(wait=True)


# # Create a New Feature – size

# In[13]:


data["size"] = data["x"] * data["y"] * data["z"]
print(data)


# # Scatter Plot – Diamond Size vs Price

# In[14]:


figure = px.scatter(data_frame = data, x="size",
                    y="price", size="size", 
                    color= "cut", trendline="ols")
figure.show()


# # Box Plot – Price Distribution by Cut and Color

# In[15]:


fig = px.box(data, x="cut", 
             y="price", 
             color="color")
fig.show()


# # Box Plot – Price Distribution by Cut and Clarity

# In[16]:


fig = px.box(data, 
             x="cut", 
             y="price", 
             color="clarity")
fig.show()


# # Encode cut Feature Numerically

# In[17]:


data["cut"] = data["cut"].map({"Ideal": 1, 
                               "Premium": 2, 
                               "Good": 3,
                               "Very Good": 4,
                               "Fair": 5})


# # Sorted Correlation with Price

# In[18]:


correlation = data.corr(numeric_only=True)
print(correlation["price"].sort_values(ascending=False))


# # Splitting data

# In[19]:


from sklearn.model_selection import train_test_split
x = np.array(data[["carat", "cut", "size"]])
y = np.array(data[["price"]])

xtrain, xtest, ytrain, ytest = train_test_split(x, y, 
                                                test_size=0.10, 
                                                random_state=42)


# # Train Random Forest Model

# In[20]:


from sklearn.ensemble import RandomForestRegressor
model = RandomForestRegressor()
model.fit(xtrain, ytrain)


# # Diamond Price Prediction Input

# In[21]:


print("Diamond Price Prediction")
a = float(input("Carat Size: "))
b = int(input("Cut Type (Ideal: 1, Premium: 2, Good: 3, Very Good: 4, Fair: 5): "))
c = float(input("Size: "))
features = np.array([[a, b, c]])
print("Predicted Diamond's Price = ", model.predict(features))


# # ann and confusion matrix

# In[3]:


import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import confusion_matrix, classification_report
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense


df = pd.read_csv("C:/Users/ideal/Downloads/Salary_dataset.csv")


df = df.drop(columns=["Unnamed: 0"])

threshold = df['Salary'].median()
df['SalaryClass'] = (df['Salary'] > threshold).astype(int)


X = df[['YearsExperience']].values
y = df['SalaryClass'].values


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)


model = Sequential()
model.add(Dense(10, activation='relu', input_dim=1))
model.add(Dense(8, activation='relu'))
model.add(Dense(1, activation='sigmoid'))


model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])


model.fit(X_train_scaled, y_train, epochs=100, verbose=0)


y_pred_prob = model.predict(X_test_scaled)
y_pred = (y_pred_prob > 0.5).astype(int)


conf_matrix = confusion_matrix(y_test, y_pred)
report = classification_report(y_test, y_pred)

print("Confusion Matrix:\n", conf_matrix)
print("\nClassification Report:\n", report)


# # confusion martix

# In[4]:


from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
import matplotlib.pyplot as plt


y_pred_prob = model.predict(X_test_scaled)
y_pred = (y_pred_prob > 0.5).astype(int)


conf_matrix = confusion_matrix(y_test, y_pred)

disp = ConfusionMatrixDisplay(confusion_matrix=conf_matrix, display_labels=["Low Salary", "High Salary"])
disp.plot(cmap=plt.cm.Blues)
plt.title("Confusion Matrix")
plt.show()


# In[ ]:




