import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from imblearn.over_sampling import SMOTE
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score

banknote_data = pd.read_csv('/content/drive/MyDrive/Project/data_banknote_authentication.csv')
banknote_data.columns = ['variance', 'asymmetry', 'kurtosis', 'entropy', 'authentication']

banknote_data.head()
banknote_data.tail()
banknote_data.shape
banknote_data.info()
banknote_data.describe()
banknote_data.columns

banknote_data.isnull().sum()
banknote_data.drop_duplicates(inplace=True)
banknote_data.shape

numerical_cols = ['variance', 'asymmetry', 'kurtosis', 'entropy']

Q1 = banknote_data[numerical_cols].quantile(0.25)
Q3 = banknote_data[numerical_cols].quantile(0.75)
IQR = Q3 - Q1
outlier_removed_data = banknote_data[~((banknote_data[numerical_cols] < (Q1 - 1.5 * IQR)) | (banknote_data[numerical_cols] > (Q3 + 1.5 * IQR))).any(axis=1)]
outlier_removed_data.shape

X = outlier_removed_data.drop('authentication', axis=1)
Y = outlier_removed_data['authentication']
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)
feature_names = X.columns
X_scaled = pd.DataFrame(X_scaled, columns=feature_names, index=X.index)
X_scaled.head()

plt.figure(figsize=(8, 6))
sns.histplot(Y, bins=30, kde=True)
plt.title('Target Variable Distribution After Outlier Removal')
plt.xlabel('Conterfeit')

smote = SMOTE(random_state=42)
X_resampled, Y_resampled = smote.fit_resample(X_scaled, Y)
data_resampled = pd.concat([pd.DataFrame(X_resampled, columns=X.columns), pd.DataFrame(Y_resampled, columns=['authentication'])], axis=1)
data_resampled.head()

X = data_resampled.drop("authentication", axis=1)
Y = data_resampled['authentication']

plt.figure(figsize=(8, 6))
sns.histplot(Y, bins=30, kde=True)
plt.title('Target Variable Distribution After Outlier Removal')
plt.xlabel('Conterfeit')

X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size = 0.1, stratify=Y, random_state=42)
print(X.shape, X_train.shape, X_test.shape)

model = RandomForestClassifier(random_state=42)
model.fit(X_train, Y_train)
Y_pred = model.predict(X_test)

print("Accuracy:", accuracy_score(Y_test, Y_pred))
print("Classification Report:\n", classification_report(Y_test, Y_pred))
print("Confusion Matrix:\n", confusion_matrix(Y_test, Y_pred))
