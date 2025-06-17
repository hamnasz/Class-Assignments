# %% [markdown]
# # Mobile Phone Price Range Classification
# 
# This notebook implements a classification model to predict mobile phone price ranges (budget, mid-range, flagship) based on various features. We'll go through the following steps:
# 
# 1. Data Loading and Initial Exploration
# 2. Data Preprocessing and Cleaning
# 3. Exploratory Data Analysis (EDA)
# 4. Feature Engineering
# 5. Model Training and Evaluation
# 6. Results Visualization

# %%
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
from sklearn.ensemble import RandomForestClassifier

# %%
df = pd.read_csv('data.csv')

print("Dataset Shape:", df.shape)
print("\nDataset Info:")
df.info()

print("\nFirst few rows of the dataset:")
df.head()

# %% [markdown]
# ## Data Quality Check
# Let's check for missing values and basic statistics of our features.

# %%
print("Missing values in the dataset:")
print(df.isnull().sum())

print("\nBasic statistics of numerical features:")
print(df.describe())

# %% [markdown]
# ## Exploratory Data Analysis (EDA)
# 
# Let's analyze the distribution and relationships of key features that might influence the phone's price range. We'll look at:
# 1. Distribution of important numerical features
# 2. Relationship between features
# 3. Feature correlations with price range

# %%
plt.figure(figsize=(15, 10))
plt.suptitle('Distribution of Key Features', fontsize=16)

features_to_plot = ['battery_power', 'clock_speed', 'ram', 'int_memory']
for idx, feature in enumerate(features_to_plot, 1):
    plt.subplot(2, 2, idx)
    sns.histplot(data=df, x=feature, hue='price_range', multiple="stack", bins=30)
    plt.title(f'{feature.replace("_", " ").title()} Distribution by Price Range')
    plt.xlabel(feature.replace("_", " ").title())
    
plt.tight_layout()
plt.show()

plt.figure(figsize=(15, 10))
plt.suptitle('Box Plots of Key Features by Price Range', fontsize=16)

for idx, feature in enumerate(features_to_plot, 1):
    plt.subplot(2, 2, idx)
    sns.boxplot(data=df, x='price_range', y=feature)
    plt.title(f'{feature.replace("_", " ").title()} vs Price Range')
    plt.xlabel('Price Range')
    
plt.tight_layout()
plt.show()

# %% [markdown]
# ## Price Range Distribution Analysis
# 
# Let's analyze the distribution of mobile phones across different price categories:
# - **Price Range 0**: Budget Phones
# - **Price Range 1**: Mid-Range Phones
# - **Price Range 2**: High-End Phones
# - **Price Range 3**: Flagship Phones
# 
# This will help us understand the balance of our dataset across different price segments.

# %%
plt.figure(figsize=(10, 6))
sns.countplot(data=df, x='price_range')
plt.title('Distribution of Mobile Phone Price Ranges')
plt.xlabel('Price Range (0: Budget, 1: Mid-range, 2: High-end, 3: Flagship)')
plt.ylabel('Count')
plt.show()

print("\nPrice Range Distribution:")
print(df['price_range'].value_counts(normalize=True).mul(100).round(2))

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))

sns.countplot(data=df, x='price_range', ax=ax1)
ax1.set_title('Distribution of Mobile Phone Price Ranges')
ax1.set_xlabel('Price Range Categories')
ax1.set_ylabel('Number of Phones')

for i in ax1.containers:
    ax1.bar_label(i, label_type='edge')

ax1.set_xticklabels(['Budget', 'Mid-Range', 'High-End', 'Flagship'])

value_counts = df['price_range'].value_counts()
total = len(df)
percentages = (value_counts / total * 100).round(2)

ax2.pie(value_counts, labels=[f'Budget ({percentages[0]}%)',
                             f'Mid-Range ({percentages[1]}%)',
                             f'High-End ({percentages[2]}%)',
                             f'Flagship ({percentages[3]}%)'],
        autopct='%1.1f%%',
        colors=sns.color_palette('husl', 4),
        explode=[0.05, 0.05, 0.05, 0.05])
ax2.set_title('Percentage Distribution of Price Ranges')

plt.tight_layout()
plt.show()

print("\nDetailed Price Range Distribution:")
print("\nCount of phones in each category:")
print(df['price_range'].value_counts().to_frame('Count').join(
    df['price_range'].value_counts(normalize=True).mul(100).round(2).to_frame('Percentage (%)')
).sort_index().rename(index={0: 'Budget', 1: 'Mid-Range', 2: 'High-End', 3: 'Flagship'}))

# %%
price_distribution = df['price_range'].value_counts().sort_index()
price_percentages = (price_distribution / len(df) * 100).round(2)

summary_df = pd.DataFrame({
    'Count': price_distribution,
    'Percentage (%)': price_percentages
})
summary_df.index = ['Budget (0)', 'Mid-Range (1)', 'High-End (2)', 'Flagship (3)']

print("Detailed Mobile Phone Distribution by Price Range:")
print("\nTotal number of phones:", len(df))
print("\nDistribution:")
print(summary_df)

is_equal = np.allclose(price_percentages, 25.0)
print(f"\nIs the distribution exactly equal (25% each)? {is_equal}")

std_dev = price_percentages.std()
print(f"Standard deviation of percentages: {std_dev:.2f}%")

# %% [markdown]
# ## Feature Correlation Analysis
# Let's examine the correlation between different features and the price range.

# %% [markdown]
# ### Feature Relationships Analysis
# Let's examine the relationships between different features using scatter plots and pair plots. This will help us understand how features interact with each other and influence the price range.

# %%
key_features = ['battery_power', 'ram', 'px_height', 'price_range']
plt.figure(figsize=(12, 8))
sns.pairplot(df[key_features], hue='price_range', diag_kind='hist')
plt.suptitle('Pair Plot of Key Features', y=1.02)
plt.show()

plt.figure(figsize=(18, 12))
sns.heatmap(df.corr(), annot=True, cmap='coolwarm', center=0)
plt.title('Correlation Heatmap of Features')
plt.tight_layout()
plt.show()

# %%
correlations = df.corr()['price_range'].sort_values(ascending=False)

plt.figure(figsize=(12, 6))
sns.barplot(x=correlations.index, y=correlations.values)
plt.xticks(rotation=45, ha='right')
plt.title('Feature Correlation with Price Range')
plt.tight_layout()
plt.show()

print("\nTop 5 most correlated features with price range:")
print(correlations.head())

# %% [markdown]
# ## Feature Engineering
# Let's create some meaningful features and prepare our data for modeling.

# %%
df['screen_area'] = df['sc_w'] * df['sc_h']
df['total_pixels'] = df['px_width'] * df['px_height']
df['pixel_density'] = df['total_pixels'] / df['screen_area']
df['has_connectivity'] = (df['wifi'] | df['three_g'] | df['four_g']).astype(int)

print("Dataset with engineered features:")
df[['screen_area', 'total_pixels', 'pixel_density', 'has_connectivity']].head()

# %%
plt.figure(figsize=(15, 10))
plt.suptitle('Distribution of Engineered Features by Price Range', fontsize=16)

engineered_features = ['screen_area', 'total_pixels', 'pixel_density', 'has_connectivity']
for idx, feature in enumerate(engineered_features, 1):
    plt.subplot(2, 2, idx)
    if feature == 'has_connectivity':
        sns.countplot(data=df, x=feature, hue='price_range')
        plt.title('Connectivity vs Price Range')
    else:
        sns.boxplot(data=df, x='price_range', y=feature)
        plt.title(f'{feature.replace("_", " ").title()} vs Price Range')
    
plt.tight_layout()
plt.show()

# %% [markdown]
# ## Data Preprocessing
# Let's prepare our data for modeling by scaling the features and splitting the dataset.

# %%
features = ['battery_power', 'clock_speed', 'int_memory', 'm_dep', 'mobile_wt', 
           'n_cores', 'pc', 'ram', 'screen_area', 'total_pixels', 'pixel_density',
           'has_connectivity', 'talk_time']

X = df[features]
y = df['price_range']

X.isnull().sum()

# %%
X = X.replace([np.inf, -np.inf], np.nan)
X = X.fillna(X.median())
X.head()

# %%
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# %%
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

print("Training set shape:", X_train_scaled.shape)
print("Testing set shape:", X_test_scaled.shape)

# %% [markdown]
# ## Model Training and Evaluation
# Let's train a Random Forest Classifier and evaluate its performance.
# 
# ## Feature Engineering
# 
# To improve our model's performance, we'll create new meaningful features:
# 
# 1. **Screen Area**: Calculate the total screen area using width and height
# 2. **Total Pixels**: Compute the total number of pixels in the display
# 3. **Pixel Density**: Calculate pixels per unit area (screen quality indicator)
# 4. **Connectivity Score**: Create a binary indicator for device connectivity
# 
# These engineered features will help capture more complex relationships in the data.
# 
# ### Model Training and Evaluation
# 
# We'll use a Random Forest Classifier for our prediction task because:
# 1. It handles non-linear relationships well
# 2. Provides feature importance rankings
# 3. Less prone to overfitting
# 4. Works well with both numerical and categorical features
# 
# We'll evaluate the model using:
# 1. Overall accuracy
# 2. Per-class precision, recall, and F1-score
# 3. Confusion matrix for detailed error analysis
# 4. Feature importance for insights into decision-making

# %%
rf_model = RandomForestClassifier(n_estimators=100, random_state=42)
rf_model.fit(X_train_scaled, y_train)

y_pred = rf_model.predict(X_test_scaled)

print("Model Accuracy: {:.2f}%".format(accuracy_score(y_test, y_pred) * 100))
print("\nClassification Report:")
print(classification_report(y_test, y_pred))

plt.figure(figsize=(10, 8))
sns.heatmap(confusion_matrix(y_test, y_pred), annot=True, fmt='d', cmap='Blues')
plt.title('Confusion Matrix')
plt.xlabel('Predicted')
plt.ylabel('Actual')
plt.show()

feature_importance = pd.DataFrame({
    'feature': features,
    'importance': rf_model.feature_importances_
})
feature_importance = feature_importance.sort_values('importance', ascending=False)

plt.figure(figsize=(12, 6))
sns.barplot(x='importance', y='feature', data=feature_importance)
plt.title('Feature Importance')
plt.xlabel('Importance')
plt.tight_layout()
plt.show()


