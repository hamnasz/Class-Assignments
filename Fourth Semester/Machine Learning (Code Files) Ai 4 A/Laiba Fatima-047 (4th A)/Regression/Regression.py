# %% [markdown]
# # LAB PROJECT 1( REGRESSION )

# %% [markdown]
# ## 📘 Introduction
# 
# This lab project focuses on solving a **regression problem** using Python and machine learning libraries. The notebook walks through the process of loading data, preprocessing it, and applying regression algorithms to predict outcomes.
# 
# **Objectives:**
# - Load and explore real-world data  
# - Apply data preprocessing (handling missing values, feature scaling)  
# - Train and evaluate regression models (e.g., Linear Regression, Decision Trees)  
# - Visualize results and performance metrics  
# 
# This notebook serves as a practical guide to supervised learning and regression analysis in machine learning.
# 

# %%
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.preprocessing import MinMaxScaler, StandardScaler

# %%
df=pd.read_csv("D:/laptop_data_cleaned.csv")

# %% [markdown]
# **1. Check & Handle Missing Values**

# %%
df.isnull().sum()

# %% [markdown]
# There are no missing values in this dataset

# %% [markdown]
# **2. Normalization (Min-Max Scaling)**

# %%
minmax_scaler = MinMaxScaler()
df_norm = df.copy()
df_norm[['Weight', 'Price', 'Ppi']] = minmax_scaler.fit_transform(df[['Weight', 'Price', 'Ppi']])

# %% [markdown]
# **3. Standardization (Z-score Scaling)**

# %%
std_scaler = StandardScaler()
df_std = df.copy()
df_std[['Weight', 'Price', 'Ppi']] = std_scaler.fit_transform(df[['Weight', 'Price', 'Ppi']])

# %% [markdown]
# **4. Data Visualization**

# %%
plt.figure(figsize=(12, 6))
sns.histplot(df['Price'], kde=True)
plt.title("Price Distribution")
plt.show()

# %%
plt.figure(figsize=(12, 6))
sns.boxplot(data=df[['Price', 'Ram', 'Weight']])
plt.title("Boxplots for Price, Ram, and Weight")
plt.show()

# %%
plt.figure(figsize=(12, 6))
sns.heatmap(df.corr(numeric_only=True), annot=True, cmap='coolwarm')
plt.title("Correlation Heatmap")
plt.show()

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
# # Preprocessing - Correlation, Outlier Detection, Feature Engineering, Data Splitting

# %%
from sklearn.model_selection import train_test_split

# %% [markdown]
# **1. Correlation**

# %%
correlation = df.corr(numeric_only=True)
print("Correlation matrix:\n", correlation)

# %% [markdown]
# **2. Outlier Detection (using IQR method on 'Price')**

# %%
Q1 = df['Price'].quantile(0.25)
Q3 = df['Price'].quantile(0.75)
IQR = Q3 - Q1
outliers = df[(df['Price'] < (Q1 - 1.5 * IQR)) | (df['Price'] > (Q3 + 1.5 * IQR))]
print(f"Number of outliers in 'Price': {len(outliers)}")

# %% [markdown]
# **3. Feature Engineering: Total Storage**

# %%
df['Total_Storage'] = df['HDD'] + df['SSD']

# %% [markdown]
# **4. Encoding Categorical Features**

# %%
df_encoded = pd.get_dummies(df, columns=['Company', 'TypeName', 'Cpu_brand', 'Gpu_brand', 'Os'], drop_first=True)

# %% [markdown]
# **5. Splitting data**

# %%
X = df_encoded.drop(['Price'], axis=1)
y = df_encoded['Price']
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
# #  Linear & Multiple Linear Regression

# %%
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

# %%
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split


# %% [markdown]
# **Linear Regression using 'Ram' only**

# %%
lr_simple = LinearRegression()
lr_simple.fit(X_train[['Ram']], y_train)
y_pred_simple = lr_simple.predict(X_test[['Ram']])
print("Simple Linear Regression R2 Score:", r2_score(y_test, y_pred_simple))

# %% [markdown]
# **Prepare a simplified version for visual linear regression (using 'Ram' for simple regression)**

# %%
X_simple = df[['Ram']]
y = df['Price']
X_train_simple, X_test_simple, y_train_simple, y_test_simple = train_test_split(X_simple, y, test_size=0.2, random_state=42)

# %% [markdown]
# **Fit simple linear regression**

# %%
lr_simple = LinearRegression()
lr_simple.fit(X_train_simple, y_train_simple)
y_pred_simple = lr_simple.predict(X_test_simple)

# %%
plt.figure(figsize=(10, 6))
sns.scatterplot(x=X_test_simple['Ram'], y=y_test_simple, label="Actual", color='blue')
sns.lineplot(x=X_test_simple['Ram'], y=y_pred_simple, label="Predicted", color='red')
plt.title("Simple Linear Regression: RAM vs Price")
plt.xlabel("RAM")
plt.ylabel("Price")
plt.legend()
plt.show()

# %% [markdown]
# ***visualization of the Simple Linear Regression model using RAM vs Price:
# Blue Dots: Actual laptop prices from the test set.
# Red Line: Predicted prices from the model.***

# %% [markdown]
# **Multiple Linear Regression using all features**

# %%
lr_multi = LinearRegression()
lr_multi.fit(X_train, y_train)
y_pred_multi = lr_multi.predict(X_test)
print("Multiple Linear Regression R2 Score:", r2_score(y_test, y_pred_multi))

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
# # Logistic Regression (binary classification on TouchScreen), Evaluation

# %%
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report, confusion_matrix

# %% [markdown]
# **Target: TouchScreen (binary)**

# %%
X_bin = df_encoded.drop(['TouchScreen'], axis=1)
y_bin = df_encoded['TouchScreen']

# %%
X_train_bin, X_test_bin, y_train_bin, y_test_bin = train_test_split(X_bin, y_bin, test_size=0.2, random_state=42)

# %% [markdown]
# **Logistic Regression**

# %%
logreg = LogisticRegression(max_iter=5000)
logreg.fit(X_train_bin, y_train_bin)
y_pred_bin = logreg.predict(X_test_bin)

# %%
print("Classification Report:\n", classification_report(y_test_bin, y_pred_bin))
print("Confusion Matrix:\n", confusion_matrix(y_test_bin, y_pred_bin))

# %% [markdown]
# **Model Evaluation Metrics for regression model**

# %%
print("MAE:", mean_absolute_error(y_test, y_pred_multi))
print("MSE:", mean_squared_error(y_test, y_pred_multi))
print("R² Score:", r2_score(y_test, y_pred_multi))

# %%



