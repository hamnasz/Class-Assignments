#1: Loading Libraries
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix


#2: Reading and Exploring Data
data = pd.read_csv('/content/drive/MyDrive/Project/My Classification/weather_classification_data.csv')
data.head()
data.info()
data.describe()
data.shape
data.columns
data.nunique()

#3: Data Cleaning
##Checking Null Values
data.isnull().sum()

##Checking Duplicates
data.duplicated().sum()


#4: Outlier Detection and Removal
numerical_cols = ['Temperature', 'Humidity', 'Wind Speed', 'Precipitation (%)', 'Atmospheric Pressure', 'UV Index', 'Visibility (km)']

Q1 = data[numerical_cols].quantile(0.25)
Q3 = data[numerical_cols].quantile(0.75)
IQR = Q3 - Q1
outlier_removed_data = data[~((data[numerical_cols] < (Q1 - 1.5 * IQR)) | (data[numerical_cols] > (Q3 + 1.5 * IQR))).any(axis=1)]
outlier_removed_data.shape

## Box plot before removing outliers
plt.figure(figsize=(20, 5))
plt.subplot(1, 2, 1)
data.boxplot()
plt.title("Before Outlier Removal")
plt.tight_layout()
plt.show()

## Box plot after removing outliers
plt.figure(figsize=(20, 5))
plt.subplot(1, 2, 2)
outlier_removed_data.boxplot()
plt.title("After Outlier Removal")
plt.tight_layout()
plt.show()


##5: One Hot Encoding
categorical_cols = ['Cloud Cover', 'Season', 'Location']

encoded_data = pd.get_dummies(outlier_removed_data, columns=categorical_cols)

encoded_data.head()


#6: Data Transformation
##Standardization
x = encoded_data.drop('Weather Type', axis=1)
y = encoded_data['Weather Type']
scaler = StandardScaler()
x_scaled = scaler.fit_transform(x)
feature_names = x.columns
x_scaled = pd.DataFrame(x_scaled, columns=feature_names, index=x.index)
x_scaled.head()

## Plot the Standardized data
plt.figure(figsize=(20, 5))
sns.boxplot(data=x_scaled)
plt.title('Scaled Numerical Features')

##Plot the Target Value Distribution
plt.figure(figsize=(6, 3))
sns.histplot(y, bins=30, kde=True)
plt.title('Target Variable Distribution After Outlier Removal')
plt.xlabel('Conterfeit')


#7: Splitting Data
x_train, x_test, y_train, y_test = train_test_split(x_scaled, y, test_size=0.2, random_state=42)


#8: Classification
model = RandomForestClassifier()
model.fit(x_train, y_train)

#9: Evaluation Metrics
y_pred = model.predict(x_test)

print("\nClassification Report:\n")
print(classification_report(y_test, y_pred))

conf_matrix = confusion_matrix(y_test, y_pred)
plt.figure(figsize=(8, 6))
sns.heatmap(conf_matrix, annot=True, fmt='d', cmap='Blues')
plt.title("Confusion Matrix")
plt.xlabel("Predicted")
plt.ylabel("Actual")
plt.tight_layout()
plt.show()


#10: Predicting on Unseen Data
new_data = pd.DataFrame([{
    "Temperature": 28.5,
    "Humidity": 65,
    "Wind Speed": 14,
    "Precipitation (%)": 10,
    "Atmospheric Pressure": 1012,
    "UV Index": 5,
    "Visibility (km)": 8,
    "Cloud Cover": "Partly Cloudy",
    "Season": "Summer",
    "Location": "Lahore"
}])

new_data_encoded = pd.get_dummies(new_data)

for col in feature_names:
    if col not in new_data_encoded.columns:
        new_data_encoded[col] = 0

new_data_encoded = new_data_encoded[feature_names]

new_data_scaled = scaler.transform(new_data_encoded)

predicted_weather = model.predict(new_data_scaled)

print("\nPredicted Weather Type:", predicted_weather[0])