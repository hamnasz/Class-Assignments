#1: Loading Libraries
import pandas as pd
import numpy as np
import sklearn
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, mean_squared_error


#2: Reading and Exploring Data
data = pd.read_csv('/content/drive/MyDrive/Project/My Regression/Achilles_Data-Gold.csv')
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
features = ["close", "open", "high", "low", "ema"]
Q1 = data[features].quantile(0.25)
Q3 = data[features].quantile(0.75)
IQR = Q3 - Q1
outlier_removed_data = data[~((data[features] < (Q1 - 1.5 * IQR)) | (data[features] > (Q3 + 1.5 * IQR))).any(axis=1)]
outlier_removed_data.shape

## Box plot before removing outliers
plt.figure(figsize=(12, 3))
plt.subplot(1, 2, 1)
data.boxplot()
plt.title("Before Outlier Removal")
plt.tight_layout()
plt.show()

## Box plot after removing outliers
plt.figure(figsize=(12, 3))
plt.subplot(1, 2, 2)
outlier_removed_data.boxplot()
plt.title("After Outlier Removal")
plt.tight_layout()
plt.show()


#5: Data Transformation
## Standardization
features_to_scale = ["open", "high", "low", "tick_volume", "ema", "obv"]
x = outlier_removed_data[features_to_scale]
y = outlier_removed_data['close']
scaler = StandardScaler()
x_scaled = scaler.fit_transform(x)

## Plot the Standardized data
plt.figure(figsize=(10, 5))
sns.boxplot(data=x_scaled)
plt.title('Scaled Numerical Features')

##Plot the Target Value Distribution
plt.figure(figsize=(6, 3))
sns.histplot(y, bins=30, kde=True)
plt.title('Target Variable Distribution After Outlier Removal')
plt.xlabel('Conterfeit')


#6: Principal Component Analysis
pca = PCA(n_components=6)
x_pca = pca.fit_transform(x_scaled)

## Plot the PCA transformed data
plt.subplot(1, 2, 2)
plt.scatter(x_pca[:, 0], x_pca[:, 1], alpha=0.5)
plt.title('PCA Transformed Data')
plt.xlabel('Principal Component 1')
plt.ylabel('Principal Component 2')
plt.tight_layout()
plt.show()


#7: Splitting Data
x_train, x_test, y_train, y_test = train_test_split(x_pca, y, test_size=0.2, random_state=42)


#8: Linear Regression
model = LinearRegression()
model.fit(x_train, y_train)


#9: Evaluation Metrics
y_pred = model.predict(x_test)
mae = mean_absolute_error(y_test, y_pred)
mse = mean_squared_error(y_test, y_pred)
rmse = np.sqrt(mse)

print("\nEvaluation Metrics:")
print(f"MAE:  {mae:.2f}")
print(f"MSE:  {mse:.2f}")
print(f"RMSE: {rmse:.2f}")


#10: Sample Prediction
results = pd.DataFrame({"Actual": y_test.values, "Predicted": y_pred})
print("\nSample Predictions:\n", results.head())


#11: Predicting on Unseen Data
new_data = pd.DataFrame({
    "open": [1900.5],
    "high": [1920.7],
    "low": [1885.3],
    "tick_volume": [123456],
    "ema": [1902.6],
    "obv": [4567890]
})

new_data_scaled = scaler.transform(new_data)

new_data_pca = pca.transform(new_data_scaled)

predicted_price = model.predict(new_data_pca)

print("\nPredicted Gold Price:", predicted_price[0])
