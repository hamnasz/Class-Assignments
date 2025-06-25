#!/usr/bin/env python
# coding: utf-8

# # PROJECT 
# 
# ## The goal is to predict the price of a laptop based on its specifications such as RAM, screen size, weight, storage type, and other hardware features. This problem can be approached using regression techniques to model the relationship between laptop features and their market price

# In[400]:


import numpy as np 
import pandas as pd
import re
import matplotlib.pyplot as plt 
import seaborn as sns

from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.metrics import mean_absolute_error, mean_squared_error
from sklearn.decomposition import PCA

from category_encoders import TargetEncoder
from imblearn.over_sampling import SMOTE
from imblearn.under_sampling import RandomUnderSampler
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import MinMaxScaler


# # READING DATA

# In[402]:


data = pd.read_csv('laptop.csv')

data.head()


# # INITIAL PRE_PROCESSING

# In[404]:


data.head(2)


# In[405]:


data.head(30)


# In[406]:


data.tail()


# In[407]:


data.shape


# In[408]:


data.tail(20)


# In[409]:


data.sample()


# In[410]:


data.sample(30)


# In[411]:


data.info()


# In[412]:


data.describe()


# In[413]:


data.isnull().sum()


# # HANDLING MISSING VALUES

# In[415]:


numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])

numeric_cols.fillna(numeric_cols.mean(), inplace=True)  


data = pd.concat([numeric_cols, non_numeric_cols], axis=1)

missing_values = data.isnull().sum()
print(missing_values)


# In[416]:


numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])

numeric_cols.fillna(numeric_cols.mean(), inplace=True)   # Numerical features

for col in non_numeric_cols.columns:
    non_numeric_cols[col].fillna(non_numeric_cols[col].mode()[0], inplace=True)  # Categorical features

data = pd.concat([numeric_cols, non_numeric_cols], axis=1)

missing_values = data.isnull().sum()
print(missing_values)


# # DELETING MISSING VALUES ROW

# In[418]:


data.dropna(inplace=True)

missing_values = data.isnull().sum()
print(missing_values)


# In[419]:


data.shape


# In[420]:


data.describe()


# In[421]:


data.drop_duplicates(inplace=True)
data.shape


# In[422]:


0.25-1.5* 0.5 + 1.0 + 2.0


# In[423]:


0.75 + 1.5 * 0.5 + 1.0


# # OUTLIER REMOVAL

# In[425]:


numeric_cols = data.select_dtypes(include=[np.number])

Q1 = numeric_cols.quantile(0.25)
Q3 = numeric_cols.quantile(0.75)
IQR = Q3 - Q1


data_cleaned = data[~((numeric_cols < (Q1 - 1.5 * IQR)) | (numeric_cols > (Q3 + 1.5 * IQR))).any(axis=1)]

plt.figure(figsize=(20, 6))
plt.subplot(1, 2, 1)
numeric_cols.boxplot()
plt.title("Before Outlier Removal")



plt.tight_layout()
plt.show()


# In[426]:


plt.figure(figsize=(20, 6))

plt.subplot(1, 2, 2)
data_cleaned.select_dtypes(include=[np.number]).boxplot()
plt.title("After Outlier Removal")

plt.tight_layout()
plt.show()


# In[427]:


data_cleaned.shape


# In[428]:


data_cleaned.head()


# # NORMALIZATION AND STANDARIZATION

# In[430]:


numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])

scaler = MinMaxScaler()
scaled_numeric_data = scaler.fit_transform(numeric_cols)
scaled_numeric_df = pd.DataFrame(scaled_numeric_data, columns=numeric_cols.columns)
scaled_data = pd.concat([scaled_numeric_df, non_numeric_cols.reset_index(drop=True)], axis=1)

print(scaled_data.shape)
print()
print('*' * 60)
scaled_data.head()


# # STANDARIZATION

# In[432]:


numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])

scaler = StandardScaler()
scaled_numeric_data = scaler.fit_transform(numeric_cols)

scaled_numeric_df = pd.DataFrame(scaled_numeric_data, columns=numeric_cols.columns)

scaled_data = pd.concat([scaled_numeric_df, non_numeric_cols.reset_index(drop=True)], axis=1)

print(scaled_data.shape)
print()
print('*' * 60)
scaled_data.head()


# In[433]:


data.head(2)


# In[434]:


data["Cpu"].unique()


# In[435]:


data.Inches.unique()


# In[436]:


data.Ram.unique()


# In[437]:


cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']

data1 = pd.get_dummies(cat_features)
data1


# In[438]:


cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']

data1 = pd.get_dummies(data, columns=cat_features)

scaled_data = pd.concat([data, data1], axis=1)

print(scaled_data.shape)
print()
print('*' * 70)

scaled_data.head()


# In[439]:


data.columns


# In[440]:


scaled_data.columns


# # DATA REDUCTION & PCA

# In[442]:


data.fillna(data.mean(numeric_only=True), inplace=True)

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']
numeric_features = [feature for feature in data.columns if data[feature].dtype != 'O']

data = pd.get_dummies(data, columns=cat_features)

scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features].values)

pca = PCA(n_components=15)
data_pca = pca.fit_transform(data)

print(data_pca.shape)
print(data_pca[:5]) 


plt.figure(figsize=(14, 6))

plt.subplot(1, 2, 1)
plt.scatter(data[numeric_features[0]], data[numeric_features[1]], alpha=0.5)
plt.title('Original Data')
plt.xlabel(numeric_features[0])
plt.ylabel(numeric_features[1])

pca = PCA(n_components=15)  
data_pca = pca.fit_transform(data)

plt.subplot(1, 2, 2)
plt.scatter(data_pca[:, 0], data_pca[:, 1], alpha=0.5)
plt.title('PCA Transformed Data')
plt.xlabel('Principal Component 1')
plt.ylabel('Principal Component 2')

plt.tight_layout()
plt.show()


# In[443]:


type(data_pca)


# In[444]:


data_pca.ndim


# # HANDLING IMBALANCED DATA

# In[446]:


data.Price.value_counts(True)


# In[447]:


data.fillna(data.mean(numeric_only=True), inplace=True)

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']
numeric_features = [feature for feature in data.columns if data[feature].dtype != 'O']

data = pd.get_dummies(data, columns=cat_features)

scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features].values)

X = data.drop(columns=['Price'])
y = data['Price']

if y.dtype == 'O':
    le = LabelEncoder()
    y = le.fit_transform(y)

print(f"Shape of X: {X.shape}, Shape of y: {y.shape}")

if len(np.unique(y)) < 20:  
    smote = SMOTE(random_state=42)
    X_resampled, y_resampled = smote.fit_resample(X, y)
    print("Applied SMOTE.")
else:
    X_resampled, y_resampled = X, y
    print("Skipped SMOTE (target seems continuous).")

data_resampled = pd.concat([pd.DataFrame(X_resampled, columns=X.columns), pd.DataFrame(y_resampled, columns=['Price'])], axis=1)

print(data_resampled.head())


# In[448]:


data_resampled.Price.value_counts(True)


# In[449]:


data_resampled.shape


# In[450]:


data.fillna(data.mean(numeric_only=True), inplace=True)

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']
numeric_features = [feature for feature in data.columns if data[feature].dtype != 'O']

data = pd.get_dummies(data, columns=cat_features)

scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features].values)

X = data.drop(columns=['Price'])
y = data['Price']

if y.dtype == 'O':
    le = LabelEncoder()
    y = le.fit_transform(y)

print(f"Shape of X: {X.shape}, Shape of y: {y.shape}")

if len(np.unique(y)) < 20:  
    rus = RandomUnderSampler()
    X_resampled, y_resampled = rus.fit_resample(X, y)
    print("Applied Random Undersampling.")
else:
    X_resampled, y_resampled = X, y
    print("Skipped Undersampling (Price seems continuous).")

data_resampled = pd.concat([pd.DataFrame(X_resampled, columns=X.columns), pd.DataFrame(y_resampled, columns=['Price'])], axis=1)

print(data_resampled.head())


# In[451]:


data_resampled.Price.value_counts()


# In[452]:


data.fillna(data.mean(numeric_only=True), inplace=True)

cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']
numeric_features = [feature for feature in data.columns if data[feature].dtype != 'O']

target_encoder = TargetEncoder(cols=cat_features)
data[cat_features] = target_encoder.fit_transform(data[cat_features], data['Price'])

scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features])

X = data.drop(columns=['Price'])
y = data['Price']

print(X.head())
print(y.head())


# # TRAINING 

# In[454]:


df = pd.read_csv('laptop.csv')
df = df.drop(columns=['Unnamed: 0'])

df['Ram'] = df['Ram'].str.replace('GB', '').astype(int)
df['Weight'] = df['Weight'].str.replace('kg', '').astype(float)

def parse_memory(mem_str):
    mem_str = mem_str.replace('Flash Storage', 'SSD').replace('HDD', '').replace('SSD', '')
    mem_str = mem_str.replace(' ', '').replace('GB', '').replace('TB', '000')
    parts = re.split(r'\+|/', mem_str)
    total = 0
    for part in parts:
        try:
            total += int(part)
        except ValueError:
            continue
    return total

df['Memory'] = df['Memory'].apply(parse_memory)

# Features and Target
X = df[['Company', 'TypeName', 'Inches', 'Cpu', 'Ram', 'Memory', 'Gpu', 'OpSys', 'Weight']]
y = df['Price']

# Categorical Columns
categorical_cols = ['Company', 'TypeName', 'Cpu', 'Gpu', 'OpSys']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

pipeline = Pipeline(steps=[
    ('preprocessor', ColumnTransformer(transformers=[
        ('cat', TargetEncoder(), categorical_cols),  # Apply TargetEncoder to categorical features
        ('num', StandardScaler(), ['Ram', 'Memory', 'Weight', 'Inches'])  # Scale numerical features
    ], remainder='passthrough')),
    ('model', LinearRegression())  
])

pipeline.fit(X_train, y_train)

y_pred = pipeline.predict(X_test)

mae = mean_absolute_error(y_test, y_pred)
rmse = np.sqrt(mean_squared_error(y_test, y_pred))
print(f"Model Performance: MAE = {mae:.2f}, RMSE = {rmse:.2f}")


# ## PLOTTING GRAPHS

# In[456]:


plt.figure(figsize=(8, 6))
sns.scatterplot(x=y_test, y=y_pred)
plt.title('Actual vs Predicted Prices')
plt.xlabel('Actual Prices')
plt.ylabel('Predicted Prices')
plt.plot([min(y_test), max(y_test)], [min(y_test), max(y_test)], color='red', linestyle='--')  # Add a line for perfect predictions
plt.show()


# In[457]:


residuals = y_test - y_pred

plt.figure(figsize=(8, 6))
sns.residplot(x=y_pred, y=residuals, lowess=True, color='green', line_kws={'color': 'red', 'lw': 1})
plt.title('Residual Plot: Actual vs Predicted Prices')
plt.xlabel('Predicted Prices')
plt.ylabel('Residuals (Errors)')
plt.axhline(y=0, color='black', linestyle='--') 
plt.show()


# In[458]:


plt.figure(figsize=(8, 6))
sns.histplot(residuals, kde=True, color='blue')
plt.title('Distribution of Residuals (Errors)')
plt.xlabel('Residuals (Errors)')
plt.ylabel('Frequency')
plt.show()


# In[459]:


metrics = {
    'Mean Absolute Error (MAE)': [mae],
    'Root Mean Squared Error (RMSE)': [rmse],
    'R-squared (R2)': [pipeline.score(X_test, y_test)]
}

metrics_df = pd.DataFrame(metrics)
print(metrics_df)


# In[460]:


new_data = pd.DataFrame([{
    'Company': 'HP',
    'TypeName': 'Notebook',
    'Inches': 15.6,
    'Cpu': 'Intel Core i5 7200U 2.5GHz',
    'Ram': 12,
    'Memory': 512,
    'Gpu': 'Intel HD Graphics 620',
    'OpSys': 'Windows 10',
    'Weight': 1.9
}])

predicted_price = pipeline.predict(new_data)
print(f"💰 Predicted Price: ₹{predicted_price[0]:,.2f}")


# In[ ]:




