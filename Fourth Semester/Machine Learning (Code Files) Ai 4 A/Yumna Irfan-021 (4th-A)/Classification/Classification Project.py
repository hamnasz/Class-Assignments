## CLASSIFICATION PROJECT
 Description: The dataset contains information about student performance, with the goal of predicting whether a student will Pass or Fail. The dependent variable is Pass-Fail rest are independent. The dataset contain 708 rows and 10 columns.
# DATA PREPROCESSING
# 1. Import necessary libraries
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, MinMaxScaler, LabelEncoder, OneHotEncoder
from sklearn.impute import SimpleImputer
# 2. Load dataset
df = pd.read_csv('student_performance_dataset.csv')  
df.shape
# 3. Explore the data
df.head()
df.info()
df.describe()
df.isnull().sum()
df.columns
# 4. Defining the Target Column for Prediction
target_col=df['Pass_Fail']
# Checking Class Distribution in the Target Column
target_col.value_counts()
# Dropping Unnecessary Columns from the DataFrame
df = df.drop(['Student_ID', 'Gender', 'Pass_Fail'], axis=1)
# 5. Identifying Numerical and Categorical Columns in the DataFrame
num_cols = df.select_dtypes(include=['int64', 'float64']).columns
cat_cols = df.select_dtypes(include=['object']).columns
## Impute numerical columns with mean
num_imputer = SimpleImputer(strategy='mean')
df[num_cols] = num_imputer.fit_transform(df[num_cols])
## Impute categorical columns with most frequent
cat_imputer = SimpleImputer(strategy='most_frequent')
df[cat_cols] = cat_imputer.fit_transform(df[cat_cols])
# 6. One-Hot Encoding Categorical Columns and Previewing Transformed Data
df = pd.get_dummies(df, columns=cat_cols, drop_first=True)
df.head(2)
# Displaying Columns In Dataframe
df.columns
# 7. Scaling Numerical Features Using StandardScaler
scaler = StandardScaler()
df[num_cols] = scaler.fit_transform(df[num_cols])
# Defining Features (X) and Target Variable (y)
X = df 
y = target_col
X
y
# 8. Train-test split
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)
## 9. Final check
print("Training data shape:", X_train.shape)
print("Testing data shape:", X_test.shape)
# Importing Libraries for Model Training and Evaluation
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
# Training the Random Forest Classifier Model
model = RandomForestClassifier(random_state=42)
model.fit(X_train, y_train)
# Evaluating Model Performance on Test Data
y_pred = model.predict(X_test)

print("Accuracy:", accuracy_score(y_test, y_pred))
print("Classification Report:\n", classification_report(y_test, y_pred))
# Displaying Model Accuracy 
print(X_train.shape, X_test.shape)
print("Train Accuracy:", model.score(X_train, y_train))
print("Test Accuracy:", model.score(X_test, y_test))
# Importing Libraries for Data Visualization and Model Evaluation
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
# Random Forest: Confusion Matrix
cm = confusion_matrix(y_test, y_pred)

plt.figure(figsize=(6, 4))
sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', xticklabels=['Not Popular', 'Popular'], yticklabels=['Not Popular', 'Popular'])
plt.xlabel('Predicted')
plt.ylabel('Actual')
plt.title('Confusion Matrix - RandomForestClassifier')
plt.show()
# Libraries for Building and Evaluating a Neural Network Model
from sklearn.compose import ColumnTransformer
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report
import matplotlib.pyplot as plt
import seaborn as sns
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Input
# Applying Label Encoding to the Target Variable
le = LabelEncoder()
y = le.fit_transform(y)
# Identifying Categorical Columns in the Feature Set
categorical_cols = X.select_dtypes(include=['object', 'category']).columns.tolist()
# Applying One-Hot Encoding to Categorical Features 
preprocessor = ColumnTransformer(
    transformers=[('cat', OneHotEncoder(drop='first', handle_unknown='ignore'), categorical_cols)],
    remainder='passthrough'
)
# Data Transformation 
X_processed = preprocessor.fit_transform(X)
# Scaling Features Using StandardScaler
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X_processed)
# Train-test split 
X_train, X_test, y_train, y_test = train_test_split(
    X_scaled, y, test_size=0.2, random_state=42
)
# Building ANN
model = Sequential([
    Input(shape=(X_train.shape[1],)),
    Dense(64, activation='relu'),
    Dense(32, activation='relu'),
    Dense(1, activation='sigmoid')
])
# Model Compilation
model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
# Training model
model.fit(X_train, y_train, epochs=20, batch_size=32, verbose=1)
# Predictions and Evaluation
y_pred_prob = model.predict(X_test)
y_pred = (y_pred_prob > 0.5).astype(int).flatten()
# Evaluating Model Performance
print("Accuracy:", accuracy_score(y_test, y_pred))
print("Classification Report:\n", classification_report(y_test, y_pred))
# ANN Confusion Matrix
cm = confusion_matrix(y_test, y_pred)

plt.figure(figsize=(6, 4))
sns.heatmap(cm, annot=True, fmt='d', cmap='Blues')
plt.xlabel('Predicted')
plt.ylabel('Actual')
plt.title('Confusion Matrix')
plt.show()