#!/usr/bin/env python
# coding: utf-8

# # Movie Revenue Prediction Project
# ### 1. Import Libraries
# #### In this cell, we import all the necessary libraries.
# #### These libraries help us with data processing, visualization, and building the machine learning model.
# 

# In[2]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_absolute_error, r2_score


# ### 2. Load and Preprocess the Dataset
# #### Here we load the already preprocessed dataset.
# #### The dataset should contain important movie features and the target revenue.
# 

# In[4]:


df = pd.read_csv('tmdb_5000_movies.csv')
df.head()


# In[5]:


df.info()


# In[6]:


print("\n Missing Values in Each Column:")
print(df.isnull().sum())


# In[7]:


print("\n Statistical Summary:")
print(df.describe())


# ### 3. Data Preprocessing Summary
# #### Loaded the TMDB 5000 Movies dataset.
# #### Removed irrelevant or textual columns (e.g., homepage, overview, title).
# #### Dropped rows with missing values.
# #### Extracted release_year from release_date and dropped the original column.
# #### Counted the number of genres per movie and stored in num_genres.
# #### Dropped the original genres column.
# #### Reset the index and displayed the cleaned dataset shape and preview.

# In[9]:


df = pd.read_csv('tmdb_5000_movies.csv')
columns_to_drop = ['homepage', 'id', 'keywords', 'overview', 'production_companies', 
                   'production_countries', 'spoken_languages', 'status', 'tagline', 'title']
df = df.drop(columns=columns_to_drop)
df = df.dropna()
df['release_date'] = pd.to_datetime(df['release_date'])
df['release_year'] = df['release_date'].dt.year
df = df.drop('release_date', axis=1)
import ast
def count_genres(x):
    try:
        genres = ast.literal_eval(x)
        return len(genres)
    except:
        return 0

df['num_genres'] = df['genres'].apply(count_genres)
df = df.drop('genres', axis=1)
df = df.reset_index(drop=True)
print("\n Data after preprocessing:")
print(df.head())
print("\n Dataset Shape:", df.shape)


# ### 4. Split Features and Target
# #### We separate the input features (X) and target variable (y).
# #### Then we split the data into training and testing sets.
# 

# In[11]:


X = df[['budget', 'popularity', 'runtime', 'vote_average', 'vote_count', 'release_year', 'num_genres']]
y = df['revenue']


# ### 5. Train the Model
# #### We train a Random Forest Regressor model on the training data.

# In[13]:


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
model = RandomForestRegressor(n_estimators=100, random_state=42)
model.fit(X_train, y_train)
y_pred = model.predict(X_test)


# ### 6. Model Evaluation
# #### We evaluate the trained model using Mean Absolute Error (MAE) and R-squared score (R2).
# 

# In[15]:


mae = mean_absolute_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

print("\n📊 Model Evaluation:")
print(f"Mean Absolute Error (MAE): {mae:.2f}")
print(f"R² Score: {r2:.2f}")


# ### 7. Feature Importance Visualization
# #### We visualize the importance of each feature using a bar chart.
# 

# In[17]:


import matplotlib.pyplot as plt
import seaborn as sns
feature_importances = model.feature_importances_
feat_importances = pd.DataFrame({
    'Feature': X.columns,
    'Importance': feature_importances
}).sort_values(by='Importance', ascending=False)
plt.figure(figsize=(10,6))
sns.barplot(x='Importance', y='Feature', data=feat_importances)
plt.title('Feature Importance for Movie Revenue Prediction', fontsize=16) 
plt.xlabel('Importance')
plt.ylabel('Feature')
plt.show()


# In[18]:


from sklearn.ensemble import RandomForestRegressor
model = RandomForestRegressor(n_estimators=100, random_state=42)
model.fit(X_train, y_train)


# ### 8. Take User Input & Predict Revenue
# #### In this cell, we take user inputs for all the movie features
# #### Then we use the trained model to predict the revenue based on those inputs.
# 

# In[22]:


budget = int(input("Enter the budget of the movie (in dollars): "))
popularity = float(input("Enter the popularity score: "))
runtime = float(input("Enter the runtime of the movie (in minutes): "))
vote_average = float(input("Enter the average vote (rating out of 10): "))
vote_count = int(input("Enter the total number of votes: "))
release_year = int(input("Enter the release year: "))
num_genres = int(input("Enter the number of genres: "))
input_features = pd.DataFrame([{
    'budget': budget,
    'popularity': popularity,
    'runtime': runtime,
    'vote_average': vote_average,
    'vote_count': vote_count,
    'release_year': release_year,
    'num_genres': num_genres
}])
predicted_revenue = model.predict(input_features)
print(f"\n Predicted Movie Revenue: ${predicted_revenue[0]:,.2f}")


# In[ ]:





# In[ ]:




