#!/usr/bin/env python
# coding: utf-8

# # Core Libraries
# # Pandas utilities
# # Scikit-learn: Preprocessing, Models, Evaluation
# # Joblib for saving and loading models
# # Streamlit for web app interface

# In[2]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from pandas.plotting import scatter_matrix
from sklearn.impute import SimpleImputer
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split, StratifiedShuffleSplit, cross_val_score
from sklearn.pipeline import Pipeline
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_squared_error
import joblib
from joblib import dump, load
import streamlit as st


# In[3]:


housing = pd.read_csv("data.csv")


# In[4]:


housing.head() 


# In[5]:


housing.info() 


# In[6]:


housing['CHAS'].value_counts() 


# In[7]:


housing.describe() 


# In[8]:


housing = pd.read_csv("data.csv")
get_ipython().run_line_magic('matplotlib', 'inline')
housing.hist(bins=50, figsize=(20, 15))
plt.show()


# In[9]:


def split_train_test(data, test_ratio):
    np.random.seed(42)
    shuffled = np.random.permutation(len(data))
    test_set_size = int(len(data) * test_ratio)
    test_indices = shuffled[:test_set_size]
    train_indices = shuffled[test_set_size:]
    return data.iloc[train_indices], data.iloc[test_indices]


# In[10]:


train_set, test_set = split_train_test(housing, 0.2)  


# In[11]:


print(f"Rows in train set: {len(train_set)}\nRows in test set: {len(test_set)}\n")


# In[12]:


train_set, test_set  = train_test_split(housing, test_size=0.2, random_state=42)
print(f"Rows in train set: {len(train_set)}\nRows in test set: {len(test_set)}\n")


# In[13]:


split = StratifiedShuffleSplit(n_splits=1, test_size=0.2, random_state=42)
for train_index, test_index in split.split(housing, housing['CHAS']):
    strat_train_set = housing.loc[train_index]
    strat_test_set = housing.loc[test_index]


# In[14]:


strat_test_set['CHAS'].value_counts()


# In[15]:


strat_train_set['CHAS'].value_counts()


# In[16]:


95/7


# In[17]:


376/28


# In[18]:


housing = strat_train_set.copy()


# ## Correlation

# In[20]:


corr_matrix = housing.corr()
corr_matrix['MEDV'].sort_values(ascending=False)


# In[21]:


attributes = ["MEDV", "RM", "ZN", "LSTAT"]
scatter_matrix(housing[attributes], figsize = (12,8))


# In[22]:


housing.plot(kind="scatter", x="RM", y="MEDV", alpha=0.8)


# ## Attribute Combinations

# In[24]:


housing["TAXRM"] = housing['TAX']/housing['RM']


# In[25]:


housing


# In[26]:


housing.head()


# In[27]:


corr_matrix = housing.corr()
corr_matrix['MEDV'].sort_values(ascending=False)


# In[28]:


housing.plot(kind="scatter", x="TAXRM", y="MEDV", alpha=0.8)


# In[29]:


housing = strat_train_set.drop("MEDV", axis=1)
housing_labels = strat_train_set["MEDV"].copy()


# ## If missing Attributes

# # To take care of missing attributes, you have three options:
# #     1. Get rid of the missing data points
# #     2. Get rid of the whole attribute
# #     3. Set the value to some value(0, mean or median)

# In[32]:


a = housing.dropna(subset=["RM"]) 
a.shape


# In[33]:


housing.drop("RM", axis=1).shape


# In[34]:


median = housing["RM"].median() 


# In[35]:


housing["RM"].fillna(median) 


# In[36]:


housing.shape


# In[37]:


housing.describe() 


# In[38]:


imputer = SimpleImputer(strategy="median")
imputer.fit(housing)


# In[39]:


imputer.statistics_


# In[40]:


X = imputer.transform(housing)
housing_tr = pd.DataFrame(X, columns=housing.columns) 
housing_tr.describe()


# ## SK LEARN FUNCTIONS

# """Primarily, three types of objects
# 1. Estimators - It estimates some parameter based on a dataset. Eg. imputer. It has a fit method and transform method. Fit method - Fits the dataset and calculates internal parameters
# 
# 2. Transformers - transform method takes input and returns output based on the learnings from fit(). It also has a convenience function called fit_transform() which fits and then transforms.
# 
# 3. Predictors - LinearRegression model is an example of predictor. fit() and predict() are two common functions. It also gives score() function which will evaluate the predict"""ions.

# ## Features Scaling 

# """Primarily, two types of feature scaling methods:
# 1. Min-max scaling (Normalization)
#     (value - min)/(max - min)
#     Sklearn provides a class called MinMaxScaler for this
#     
# 2. Standardization
#     (value - mean)/std
#     Sklearn provides a class called StandardScaler for this"""
# 

# ## Now pipeline

# In[46]:


my_pipeline = Pipeline([
    ('imputer', SimpleImputer(strategy="median")),

    ('std_scaler', StandardScaler()),
])
housing_num_tr = my_pipeline.fit_transform(housing)
housing_num_tr.shape


# ## Models Selection

# In[48]:


rf_model = RandomForestRegressor(n_estimators=100, random_state=42)
rf_model.fit(housing_num_tr, housing_labels)


# In[49]:


model = RandomForestRegressor()
model.fit(housing_num_tr, housing_labels)


# In[50]:


model = LinearRegression()
model.fit(housing_num_tr, housing_labels)


# In[51]:


some_data = housing.iloc[:5]


# In[52]:


some_labels = housing_labels.iloc[:5]


# In[53]:


prepared_data = my_pipeline.transform(some_data)


# In[54]:


model.predict(prepared_data)


# In[55]:


some_labels


# In[56]:


list(some_labels)


# ## Evaluating Model

# In[58]:


housing_predictions = model.predict(housing_num_tr)
mse = mean_squared_error(housing_labels, housing_predictions)
rmse = np.sqrt(mse)
rmse


# ## Cross Validation (needs utility)

# In[60]:


scores = cross_val_score(model, housing_num_tr, housing_labels, scoring="neg_mean_squared_error", cv=10)
rmse_scores = np.sqrt(-scores)
rmse_scores


# In[61]:


def print_scores(scores):
    print("Scores:", scores)
    print("Mean: ", scores.mean())
    print("Standard deviation: ", scores.std())


# In[62]:


print_scores(rmse_scores)


# ## Testing 

# In[64]:


X_test = strat_test_set.drop("MEDV", axis=1)
Y_test = strat_test_set["MEDV"].copy()
X_test_prepared = my_pipeline.transform(X_test)
final_predictions = model.predict(X_test_prepared)
final_mse = mean_squared_error(Y_test, final_predictions)
final_rmse = np.sqrt(final_mse)


# In[65]:


final_rmse


# In[66]:


prepared_data[0]


# ## Saving Model 

# In[68]:


dump(model, 'Dragon.joblib')
model = load('Dragon.joblib') 
features = np.array([[-5.43942006, 4.12628155, -1.6165014, -0.67288841, -1.42262747,
       -11.44443979304, -49.31238772,  7.61111401, -26.0016879 , -0.5778192 ,
       -0.97491834,  0.41164221, -66.86091034]])
model.predict(features)
dump(rf_model, 'Dragon_RF.joblib')


# # Load the saved model and pipeline
# # Feature names based on the dataset used
# # Process user input and predict house price
# # Preprocess the input using the pipeline
# 

# In[70]:


linear_model = load('Dragon.joblib')          
rf_model = load('Dragon_RF.joblib')           

# Load pipeline
my_pipeline = load('preprocessing_pipeline.pkl')    

feature_names = [
    "CRIM", "ZN", "INDUS", "CHAS", "NOX", "RM", "AGE", "DIS", 
    "RAD", "TAX", "PTRATIO", "B", "LSTAT"
]

def get_user_input():
    """Get user input through Streamlit."""
    user_input = []
    st.write("### 🔢 Enter the following feature values:")
    for feature in feature_names:
        value = st.number_input(f"{feature}:", value=0.0, step=0.01)
        user_input.append(value)    
    return np.array(user_input).reshape(1, -1)

def predict_house_price():
    user_input = get_user_input()
    input_df = pd.DataFrame(user_input, columns=feature_names)
    prepared_input = my_pipeline.transform(input_df)

    # Make predictions with both models
    prediction_lr = linear_model.predict(prepared_input)
    prediction_rf = rf_model.predict(prepared_input)

    # Show results
    st.markdown("## 🏡 Predicted Median House Values")
    col1, col2 = st.columns(2)
    with col1:
        st.write("### Linear Regression")
        st.success(f"${prediction_lr[0] * 1000:.2f}")
    with col2:
        st.write("### Random Forest Regression")
        st.info(f"${prediction_rf[0] * 1000:.2f}")

if __name__ == "__main__":
    st.title("🏠 House Price Prediction App")
    st.write("This app predicts house prices using two models: *Linear Regression* and *Random Forest*.")
    predict_house_price()


# In[71]:


joblib.dump(model, "house_price_model.pkl")


# In[72]:


joblib.dump(my_pipeline, "preprocessing_pipeline.pkl")


# In[ ]:


get_ipython().system('streamlit run app.py')


# In[ ]:




