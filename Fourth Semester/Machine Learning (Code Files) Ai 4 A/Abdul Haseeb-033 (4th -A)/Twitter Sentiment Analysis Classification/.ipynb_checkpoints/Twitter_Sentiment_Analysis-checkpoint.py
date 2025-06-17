#!/usr/bin/env python
# coding: utf-8

# ## Importing Necessary Libraries

# In[61]:


import pandas as pd
import numpy as np
import string
import re
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score


# ## Loading the data

# In[32]:


data =pd.read_csv("Twitter.csv")


# ### Data Preview 

# In[62]:


data


# In[33]:


data.head()


# In[34]:


data.tail()


# In[35]:


data.shape


# In[36]:


data.info()


# In[37]:


data.columns


# In[38]:


data.describe()


# # Noramalization

# In[39]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler

data = pd.read_csv("Twitter.csv")

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


# ## Data Preprocessing

# ### Assigning Column Names

# In[40]:


data.columns = ["id", "information", "sentiment", "text"]


# In[41]:


data.columns


# ### Create a new Column("Label")
# #### (Negative = -1,  Nuetral = 0,  Positive = 1)

# In[42]:


def label(sentiment):
    if sentiment == "Negative":
        return -1
    elif sentiment == "Neutral":
        return 0
    elif sentiment == "Positive":
        return 1


# In[43]:


data['label'] = data['sentiment'].apply(label)


# In[44]:


data.head()


# ### 'id', 'information' and 'sentiment' columns are not required for analysis, So drop these Columns.

# In[45]:


data = data.drop(['id', 'information', 'sentiment'], axis = 1)


# ### Shuffling the Data Randomly

# In[46]:


data = data.sample(frac=1)
data.reset_index(inplace=True)
data.drop(["index"], axis=1, inplace=True)


# In[47]:


data.head()


# ### Checking Null values and Dropping the Row with Null Value.

# In[48]:


data.isnull().sum()


# In[49]:


data = data.dropna(axis=0, how="any", subset=None, inplace=False)


# In[50]:


data.isnull().sum()


# ## Visualizing Data

# ### Distibution of Labels
# #### Negative = -1, Neutral = 0, Positive = 1

# In[51]:


fig = plt.figure(figsize=(5,5))
sns.countplot(x='label', data = data)
plt.xticks([0, 1, 2], ['Negative', 'Neutral', 'Positive'])
plt.show()


# ## Text Preprocessing

# In[52]:


def preprocessing(text):
    text = text.lower()
    text = re.sub(r'\[.*?\]','',text)  # Using raw string here
    text = re.sub(r"\W", " ", text)   # Using raw string here
    text = re.sub(r'https?://\S+|www\.\S+', '', text)  # Using raw string here
    text = re.sub(r'<.*?>+', '', text)  # Using raw string here
    text = re.sub(r'[%s]' % re.escape(string.punctuation), '', text)  # Using raw string here
    text = re.sub(r'\w*\d\w*', '', text)  # Using raw string here
    return text


# In[53]:


data['text'] = data['text'].apply(preprocessing)


# In[54]:


print(data["text"].iloc[0], "\n")
print(data["text"].iloc[15], "\n")
print(data["text"].iloc[49], "\n")
print(data["text"].iloc[2000], "\n")
print(data["text"].iloc[56000], "\n")


# ### Defining dependent and independent variable as x and y.

# In[55]:


x = data['text'].values
y = data['label'].values


# ### Convert text to vectors.

# In[56]:


vectorizer = CountVectorizer()
vectorizer.fit(x)

x = vectorizer.transform(x)


# ## Training the model

# ### Splitting the dataset into training set and testing set. 

# In[57]:


x_train, x_test, y_train, y_test = train_test_split( x, y, test_size=0.2)


# ## Logistic Regression

# In[58]:


model = LogisticRegression()
model.fit(x_train, y_train)


# In[34]:


x_train_prediction = model.predict(x_train)
training_data_accuracy = accuracy_score(x_train_prediction, y_train)


# ## Accuracy Score

# In[35]:


print('Accuracy score of the training data : ', training_data_accuracy)


# ## Evaluation

# In[36]:


def predict_sentiment(text):
    cleaned_text = preprocessing(text)
    text_vec = vectorizer.transform([cleaned_text])
    sentiment = model.predict(text_vec)[0]

    if(sentiment == -1):
        return 'Negative'
    elif(sentiment == 0):
        return 'Neutral'
    elif(sentiment == 1):
        return 'Positive'


# ## Input

# In[37]:


new_texts = [
    "welcome to free the jungle",
    "I really enjoyed this!", 
    "Not worth the money.", 
    "Exceptional quality!"
]


# ## Output

# In[38]:


for text in new_texts:
    print(f"Text: {text} | Sentiment: {predict_sentiment(text)}")

