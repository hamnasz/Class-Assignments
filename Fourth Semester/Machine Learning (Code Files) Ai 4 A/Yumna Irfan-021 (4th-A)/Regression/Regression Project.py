## Regression Project
Description: The dataset is of insurance in which charges is dependent and others are independent variables.Insurance dataset contains information about individuals such as age, sex, BMI, number of children, smoking status, region, and insurance charges.
# DATA PREPROCESSING
# 1. Import necessary libraries
import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler, MinMaxScaler, LabelEncoder, OneHotEncoder
from sklearn.impute import SimpleImputer
import matplotlib.pyplot as plt  
# 2. Load dataset and Showing Dataset Dimesnsion
df = pd.read_csv('insurance.csv')  
df.shape
# 3. Explore the data
df.sample()
df.head()
df.tail()
# Checking Information and Datatypes
df.info()
df.dtypes
df.describe()
# Checking Null Values
df.isnull().sum()
# 4. Identifying Numerical and Categorical Columns
## Checking Outliers
num_cols = df.select_dtypes(include=['int64', 'float64']).columns  
mask = pd.Series(True, index=df.index)  

for col in num_cols: 
    Q1 = df[col].quantile(0.25)  
    Q3 = df[col].quantile(0.75)  
    IQR = Q3 - Q1  
    lower_bound = Q1 - 1.5 * IQR  
    upper_bound = Q3 + 1.5 * IQR  
    mask = mask & df[col].between(lower_bound, upper_bound)  

data_cleaned = df[mask]  
plt.figure(figsize=(25,6))
plt.subplot(1,2,1)
df.boxplot()
plt.title("Before Removing Outliers")
plt.tight_layout()
plt.show()
plt.figure(figsize=(30,6))
plt.subplot(1,2,1)
data_cleaned.boxplot()
plt.title("After Removing Outliers")
plt.tight_layout()
plt.show()
cat_cols = df.select_dtypes(include=['object']).columns
## Impute numerical columns with mean
num_imputer = SimpleImputer(strategy='mean')
df[num_cols] = num_imputer.fit_transform(df[num_cols])
## Impute categorical columns with most frequent
cat_imputer = SimpleImputer(strategy='most_frequent')
df[cat_cols] = cat_imputer.fit_transform(df[cat_cols])
# 5. Encode categorical variables
df = pd.get_dummies(df, columns=cat_cols, drop_first=True)
# 6. Feature Scaling
scaler = StandardScaler()
df[num_cols] = scaler.fit_transform(df[num_cols])
# 7. Split dataset into features (X) and target (y)
X = df.drop('charges', axis=1)  
y = df['charges']
# 8. Train-test split
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)
# 9. Final check
print("Training data shape:", X_train.shape)
print("Testing data shape:", X_test.shape)
# Building Linear Regression Model
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score
# Initialize model and Training model
model = LinearRegression()
model.fit(X_train, y_train)
# Model Prediction
y_pred = model.predict(X_test)
# Model Evaluation Metrics
print("Mean Squared Error:", mean_squared_error(y_test, y_pred))
print("R² Score:", r2_score(y_test, y_pred))
# Data Visualization Setup
import matplotlib.pyplot as plt
# Actual vs Predicted Plot
plt.scatter(y_test, y_pred, color='blue', alpha=0.5)
plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], 'r--', lw=2)
plt.ylabel('Predicted charges')
plt.xlabel('Actual charges')
plt.title('Actual vs Predicted charges')
plt.grid(True)
plt.show()