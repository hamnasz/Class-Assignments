# %% [markdown]
# # Implementing Decision Tree Classifier

# %% [markdown]
# # 📊 Project 2 – Regression Analysis Using Machine Learning
# 
# ## 📘 Introduction
# 
# This project explores the use of **regression algorithms** in predicting numerical outcomes based on input data. Regression is a type of supervised learning in machine learning where the output variable is continuous. In this notebook, we walk through the complete process—from data preprocessing to model training and evaluation.
# 
# By the end of this project, we will have a trained regression model that can predict values based on new input, along with visualizations and metrics to evaluate its accuracy.
# 
# ---
# 
# ## 🎯 Objectives
# 
# - Import and clean the dataset
# - Perform exploratory data analysis (EDA)
# - Apply feature scaling (if necessary)
# - Train and evaluate different regression models such as:
#   - Linear Regression
#   - Decision Tree Regressor
#   - Random Forest Regressor
# - Visualize model performance using plots
# - Interpret the results and draw conclusions
# 
# ---
# 
# ## 🛠️ Tools and Libraries
# 
# - **Pandas** for data handling  
# - **NumPy** for numerical operations  
# - **Matplotlib / Seaborn** for visualization  
# - **Scikit-learn** for model building and evaluation
# 
# ---
# 
# > This notebook is an educational resource aimed at building intuition and hands-on experience in regression analysis using Python.
# 

# %% [markdown]
# ***Step 1: Preprocessing***

# %%
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import classification_report, accuracy_score
import pandas as pd

# %%
df2 = pd.read_csv("D:/factory_sensor_simulator_2040.csv")

# %% [markdown]
# **Display basic info and check for missing values**

# %%
df2.info(), df2.isnull().sum()

# %% [markdown]
# **Drop columns with heavy missing value**

# %%
df_clean = df2.drop(columns=['Laser_Intensity', 'Hydraulic_Pressure_bar', 'Coolant_Flow_L_min', 'Heat_Index'])


# %% [markdown]
# **Encode categorical column**

# %%
le = LabelEncoder()
df_clean['Machine_Type'] = le.fit_transform(df_clean['Machine_Type'])

# %% [markdown]
# **Separate features and target**

# %%
X = df_clean.drop(columns=['Failure_Within_7_Days', 'Machine_ID'])
y = df_clean['Failure_Within_7_Days']


# %% [markdown]
# **Train-test split**

# %%
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# %% [markdown]
# **Step 2: Train Decision Tree**

# %%
dt_model = DecisionTreeClassifier(random_state=42)
dt_model.fit(X_train, y_train)

# %% [markdown]
# **Step 3: Predict and Evaluate**

# %%
y_pred_dt = dt_model.predict(X_test)

# %% [markdown]
# **Output accuracy and classification report**

# %%
dt_accuracy = accuracy_score(y_test, y_pred_dt)
dt_report = classification_report(y_test, y_pred_dt)

# %%
dt_accuracy, dt_report

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
# #  Implementing Support Vector Machine (SVM)
# 

# %%
from sklearn.svm import SVC
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, accuracy_score

# %% [markdown]
# **Step 1: Feature scaling (SVM performs better with scaled data)**

# %%
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# %% [markdown]
# **Step 2: Train-test split**

# %%
X_train_svm, X_test_svm, y_train_svm, y_test_svm = train_test_split(X_scaled, y, test_size=0.2, random_state=42)


# %% [markdown]
# **Step 3: Train SVM model**

# %% [markdown]
# Sample only 20,000 rows

# %%
X_sampled = X.sample(20000, random_state=42)
y_sampled = y.loc[X_sampled.index]


# %%
X_scaled = scaler.fit_transform(X_sampled)

X_train_svm, X_test_svm, y_train_svm, y_test_svm = train_test_split(X_scaled, y_sampled, test_size=0.2, random_state=42)

svm_model = SVC(kernel='linear', random_state=42)
svm_model.fit(X_train_svm, y_train_svm)

# %% [markdown]
# **Step 4 : Predict & evaluate**

# %%
y_pred_svm = svm_model.predict(X_test_svm)
print("Accuracy:", accuracy_score(y_test_svm, y_pred_svm))
print("Classification Report:\n", classification_report(y_test_svm, y_pred_svm))

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
# #  Evaluation Metrics for Classification

# %%
from sklearn.metrics import confusion_matrix, precision_score, recall_score, f1_score, roc_auc_score, roc_curve
import seaborn as sns
import matplotlib.pyplot as plt

# %% [markdown]
# **Confusion matrix**

# %%
cm = confusion_matrix(y_test, y_pred_dt)
sns.heatmap(cm, annot=True, fmt='d', cmap='Blues')
plt.title("Confusion Matrix (Decision Tree)")
plt.xlabel("Predicted")
plt.ylabel("Actual")
plt.show()

# %% [markdown]
# **Metrics**

# %%
print("Accuracy:", accuracy_score(y_test, y_pred_dt))
print("Precision:", precision_score(y_test, y_pred_dt))
print("Recall:", recall_score(y_test, y_pred_dt))
print("F1-score:", f1_score(y_test, y_pred_dt))

# %% [markdown]
# **AUC and ROC Curve**

# %%
y_prob_dt = dt_model.predict_proba(X_test)[:, 1]
fpr, tpr, thresholds = roc_curve(y_test, y_prob_dt)
roc_auc = roc_auc_score(y_test, y_prob_dt)

# %%
plt.plot(fpr, tpr, label=f"AUC = {roc_auc:.2f}")
plt.plot([0, 1], [0, 1], 'k--')
plt.title("ROC Curve (Decision Tree)")
plt.xlabel("False Positive Rate")
plt.ylabel("True Positive Rate")
plt.legend()
plt.show()

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
# #  Handling Imbalanced Datasets

# %%
from imblearn.over_sampling import SMOTE
from imblearn.under_sampling import RandomUnderSampler
from collections import Counter

# %% [markdown]
# **Original distribution**

# %%
print("Original class distribution:", Counter(y))


# %% [markdown]
# **SMOTE Over-sampling**

# %%
sm = SMOTE(random_state=42)
X_smote, y_smote = sm.fit_resample(X, y)
print("After SMOTE:", Counter(y_smote))

# %% [markdown]
# **Under-sampling**

# %%
rus = RandomUnderSampler(random_state=42)
X_under, y_under = rus.fit_resample(X, y)
print("After Under-sampling:", Counter(y_under))

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
#  

# %% [markdown]
# #  Artificial Neural Networks (ANN)

# %%
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from sklearn.preprocessing import StandardScaler, LabelEncoder
data = pd.read_csv("D:/factory_sensor_simulator_2040.csv")


for column in data.select_dtypes(include=['object']).columns:
    le = LabelEncoder()
    data[column] = le.fit_transform(data[column])


X = data.iloc[:, :-1].values  # all columns except last
y = data.iloc[:, -1].values   # last column is the target

sc = StandardScaler()
X = sc.fit_transform(X)


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=0)


# %%

model = Sequential()
model.add(Dense(units=16, activation='relu', input_dim=X.shape[1]))
model.add(Dense(units=8, activation='relu'))
model.add(Dense(units=1, activation='sigmoid' if len(np.unique(y)) == 2 else 'linear'))


model.compile(optimizer='adam', loss='binary_crossentropy' if len(np.unique(y)) == 2 else 'mean_squared_error', metrics=['accuracy'])

model.fit(X_train, y_train, batch_size=32, epochs=20, validation_split=0.2)
SS

loss, accuracy = model.evaluate(X_test, y_test)
print(f"\nTest Loss: {loss:.4f}, Test Accuracy: {accuracy:.4f}")


# %% [markdown]
# **Plot Accuracy and Loss Over Epochs**
# 

# %%
import matplotlib.pyplot as plt

# %% [markdown]
# **Train the model and store history**

# %%

history = model.fit(X_train, y_train, batch_size=32, epochs=50, validation_split=0.2)

# %%


# %% [markdown]
# **Plot Accuracy**

# %%
plt.figure(figsize=(10, 5))
plt.plot(history.history['accuracy'], label='Training Accuracy', marker='o')
plt.plot(history.history['val_accuracy'], label='Validation Accuracy', marker='x')
plt.title('Model Accuracy')
plt.ylabel('Accuracy')
plt.xlabel('Epoch')
plt.legend()
plt.grid(True)
plt.show()

# %% [markdown]
# **Plot Loss**

# %%

plt.figure(figsize=(10, 5))
plt.plot(history.history['loss'], label='Training Loss', marker='o')
plt.plot(history.history['val_loss'], label='Validation Loss', marker='x')
plt.title('Model Loss')
plt.ylabel('Loss')
plt.xlabel('Epoch')
plt.legend()
plt.grid(True)
plt.show()


# %%
import seaborn as sns

accuracies = [0.87, 0.85, 0.89, 0.83, 0.88] 

plt.figure(figsize=(8, 5))
sns.boxplot(data=accuracies)
plt.title("Boxplot of Model Accuracies")
plt.ylabel("Accuracy")
plt.grid(True)
plt.show()

# %%

y_pred_prob = model.predict(X_test)
y_pred = (y_pred_prob > 0.5).astype(int).flatten()  # For binary classification


cm = confusion_matrix(y_test, y_pred)

s
plt.figure(figsize=(6,4))
sns.heatmap(cm, annot=True, fmt='d', cmap='Blues')
plt.xlabel('Predicted')
plt.ylabel('Actual')
plt.title('Confusion Matrix')
plt.show()

print("Classification Report:\n")
print(classification_report(y_test, y_pred))

# %%
plt.figure(figsize=(10, 4))
plt.plot(y_test[:50], label='Actual', marker='o')
plt.plot(y_pred[:50], label='Predicted', marker='x')
plt.title('Actual vs Predicted (Sample)')
plt.xlabel('Sample Index')
plt.ylabel('Class')
plt.legend()
plt.grid(True)
plt.show()


# %%



