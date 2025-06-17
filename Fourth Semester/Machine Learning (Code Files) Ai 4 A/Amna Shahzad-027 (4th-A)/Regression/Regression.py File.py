# %% [markdown]
# # CAR PRICE PREDICTION REGRESSION DATASET

# %% [markdown]
# # DESCRIPTION
# The CarPrice_Assignment dataset contains detailed specifications and pricing information for 205 different cars. It is designed to support data analysis and machine learning tasks related to automobile pricing and feature correlations.
# Each row in the dataset represents one car, and there are 26 different attributes (or columns) describing various characteristics of these cars.
# The dataset begins with a unique identifier for each car, followed by a "symboling" rating. This rating is an insurance risk indicator ranging from -2 to +3, where higher values imply greater risk. The CarName column includes both the brand and model of each vehicle.
# Several categorical features describe the type and configuration of the car. For instance, fueltype specifies whether the car uses gasoline or diesel, while aspiration indicates whether the engine is normally aspirated or turbocharged. The number of doors (doornumber), body type (carbody), and drive type (drivewheel) give additional context to the vehicle’s structure and driving mechanism. Engine placement is noted in enginelocation, typically as either front or rear.
# Physical dimensions like wheelbase, length, width, and height are provided in inches, along with the curbweight, which represents the car's weight without passengers or luggage. The dataset also details the engine’s configuration through columns like enginetype, cylindernumber, and enginesize.
# Fuel system type is included under fuelsystem, and mechanical aspects such as bore ratio, stroke, compression ratio, horsepower, and peak RPM offer insight into engine performance. Finally, fuel efficiency is recorded as miles per gallon in both city and highway conditions (citympg and highwaympg), and the last column, price, captures the car’s market price in US dollars.
# This dataset is well-suited for exploring the relationships between car features and their prices, making it valuable for regression modeling, exploratory data analysis, and feature importance studies

# %% [markdown]
# # DATA PREPROCESSING STEPS

# %% [markdown]
# # 1.READING DATA

# %%
import matplotlib.pyplot as plt 
import seaborn as sns 
color = sns.color_palette()
import pandas as pd

data = pd.read_csv("Downloads/Dataset Regression/CarPrice_Assignment.csv")


# %% [markdown]
# # 2.EXPLORING DATA

# %%
data.head(2)

# %%
data.head(30)

# %%
data.tail()

# %%
data.shape

# %%
data.tail(20)

# %%
data.sample

# %%
data.sample(30)

# %%
data.info() 

# %%
data.describe()

# %% [markdown]
# # 3: Data Cleaning

# %% [markdown]
# Handling Missing Values
# -
# - Imputation: Filling missing values with mean.

# %%
import pandas as pd

# %%
data.isnull().sum()

# %%
import pandas as pd
import numpy as np

numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])

numeric_cols.fillna(numeric_cols.mean(), inplace=True)   

data = pd.concat([numeric_cols, non_numeric_cols], axis=1)

missing_values = data.isnull().sum()
print(missing_values)

# %%
data.shape

# %% [markdown]
# # 4. Removal: Deleting rows with missing values.

# %%
data.isnull().sum()

# %%
data.shape

# %%
data.dropna(inplace=True)
missing_values = data.isnull().sum()
print(missing_values)

# %%
data.shape

# %% [markdown]
# # 4: REMOVING DUPLICATES

# %%
data.drop_duplicates(inplace=True)

# %% [markdown]
# # 5: OUTLIER DETECTION AND REMOVAL

# %%
from scipy import stats
num_cols = df.select_dtypes(include=['float64', 'int64']).columns
z_scores = stats.zscore(df[num_cols])
df = df[(abs(z_scores) < 3).all(axis=1)]

# %%
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


# %%
plt.figure(figsize=(20, 6))
plt.subplot(1, 2, 2)
data_cleaned.select_dtypes(include=[np.number]).boxplot()
plt.title("After Outlier Removal")

plt.tight_layout()
plt.show()


# %% [markdown]
# # 6: DATA TRANSFORMATION

# %% [markdown]
# # Key Differences
# - Range of Values:
# 
# Normalization: Values are scaled to a fixed range, typically [0, 1]. Standardization: Values are rescaled to have a mean of 0 and a standard deviation of 1. Effect on Distribution:
# 
# Normalization: Compresses or stretches the data to fit within the specified range, potentially altering the original distribution. Standardization: Preserves the shape of the original distribution but changes the scale. Use Cases:
# 
# Normalization: Suitable for distance-based algorithms, like k-nearest neighbors and neural networks. Standardization: Suitable for algorithms that assume a normal distribution, like linear regression and logistic regression.

# %% [markdown]
# # Normalization
# - Normalization
# Definition:
# Normalization rescales the data to a fixed range, typically [0, 1] or [-1, 1].

# %%
import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler

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

# %% [markdown]
# # Standardization
# -
# Standardization rescales the data so that it has a mean of 0 and a standard deviation of 1.

# %%
import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler

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

# %% [markdown]
# # 7: DIMENTIONALITY REDUCTION (PCA)

# %%
from sklearn.decomposition import PCA

pca = PCA(n_components=0.95)  
pca_features = pca.fit_transform(df.drop("price", axis=1))

# %% [markdown]
# - LINEAR REGRESSION 

# %%
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestRegressor
from sklearn.decomposition import PCA
import numpy as np

# %% [markdown]
# - CLEAN AND PROCESS THE DATA

# %%
df['CarBrand'] = df['CarName'].apply(lambda x: x.split(' ')[0].lower())
df.drop(['car_ID', 'CarName'], axis=1, inplace=True)

df['horsepower'] = pd.to_numeric(df['horsepower'], errors='coerce')
df['peakrpm'] = pd.to_numeric(df['peakrpm'], errors='coerce')
df.fillna(df.median(numeric_only=True), inplace=True)


# %% [markdown]
# - ENCODE CATEGORICAL FEATURES

# %%
df = pd.get_dummies(df, drop_first=True)

# %% [markdown]
# # 9: FEATURE SELECTION USING RANDOM FOREST

# %%
X = df.drop("price", axis=1)
y = df["price"]

model = RandomForestRegressor(random_state=42)
model.fit(X, y)

# %%
importances = pd.Series(model.feature_importances_, index=X.columns)
top_features = importances.nlargest(15).index
X = X[top_features]

# %% [markdown]
# # 10: SPLITTING THE DATA

# %%
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# %% [markdown]
# # 11: APPLY LINEAR REGRESSION

# %%
lr_model = LinearRegression()
lr_model.fit(X_train, y_train)

# %% [markdown]
# # 12: PREDICT AND EVALUATE

# %%
plt.scatter(y_test,y_pred)
plt.plot([y.min(),y.max()], [y.min(), y.max()], 'k--')
plt.xlabel('Actual Prices')
plt.ylabel('Predicted Prices')
plt.title('Actual vs Predicted Prices')
plt.show()

# %%
y_pred = lr_model.predict(X_test)
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

mse, r2


