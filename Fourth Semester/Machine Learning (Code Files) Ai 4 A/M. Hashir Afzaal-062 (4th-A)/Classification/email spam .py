#!/usr/bin/env python
# coding: utf-8

# # Libraries 

# In[4]:


import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score
import pickle
from sklearn.svm import SVC
from keras.models import Sequential
from keras.layers import Dense
from keras.utils import to_categorical
from keras import Input
from keras.models import load_model


# # read data set 

# In[6]:


raw_mail_data = pd.read_csv('mail_data.csv')


# In[7]:


raw_mail_data


# # replace the null values with a null string

# # Pre-Processing

# In[10]:


mail_data = raw_mail_data.where((pd.notnull(raw_mail_data)),'')


# In[11]:


mail_data.head()


# In[12]:


mail_data.shape


# # Label Encoding

# # label spam mail as 0;  ham mail as 1;

# In[15]:


mail_data.loc[mail_data['Category'] == 'spam', 'Category',] = 0
mail_data.loc[mail_data['Category'] == 'ham', 'Category',] = 1


# # separating the data as texts and label

# In[17]:


X = mail_data['Message']

Y = mail_data['Category']


# In[18]:


X


# In[19]:


Y


# # Splitting the data into training data & test data

# In[21]:


X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2, random_state=3)


# In[22]:


print(X.shape)
print(X_train.shape)
print(X_test.shape)


# # Feature Extraction 

# # transform the text data to feature vectors that can be used as input to the Logistic regression

# In[25]:


feature_extraction = TfidfVectorizer(min_df = 1, stop_words='english', lowercase=True)
X_train_features = feature_extraction.fit_transform(X_train)
X_test_features = feature_extraction.transform(X_test)


# convert Y_train and Y_test values as integers

# In[27]:


Y_train = Y_train.astype('int')
Y_test = Y_test.astype('int')


# In[28]:


X_train


# In[29]:


X_train_features


# # Training the Model

# # Logistic Regression

# In[32]:


model = LogisticRegression()


# # training the Logistic Regression model with the training data

# In[34]:


model.fit(X_train_features, Y_train)


# # Evaluating the trained model

# # prediction on training data

# In[37]:


prediction_on_training_data = model.predict(X_train_features)
accuracy_on_training_data = accuracy_score(Y_train, prediction_on_training_data)


# In[38]:


print('Accuracy on training data : ', accuracy_on_training_data)


# # prediction on test data

# In[40]:


prediction_on_test_data = model.predict(X_test_features)
accuracy_on_test_data = accuracy_score(Y_test, prediction_on_test_data)


# In[41]:


print('Accuracy on test data : ', accuracy_on_test_data)


# # Save model

# # Save vectorizer

# In[44]:


with open("model_lr.pkl", "wb") as f:
    pickle.dump(model, f)
with open("vectorizer.pkl", "wb") as f:
    pickle.dump(feature_extraction, f)


# # Train ANN Model
# 

# In[46]:


X_train_ann = X_train_features.toarray()
X_test_ann = X_test_features.toarray()


# In[47]:


ann_model = Sequential()
ann_model.add(Input(shape=(X_train_ann.shape[1],)))  
ann_model.add(Dense(64, activation='relu'))
ann_model.add(Dense(32, activation='relu'))
ann_model.add(Dense(1, activation='sigmoid'))


# In[48]:


ann_model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
ann_model.fit(X_train_ann, Y_train, epochs=5, batch_size=32, verbose=1)


# In[49]:


loss, accuracy = ann_model.evaluate(X_test_ann, Y_test, verbose=0)
print("ANN Accuracy on test data:", accuracy)


# # Save ANN model

# In[51]:


ann_model.save("model_ann.keras")  


# # Predict 

# In[ ]:


def check_with_lr(email):
    model = pickle.load(open("model_lr.pkl", "rb"))
    vectorizer = pickle.load(open("vectorizer.pkl", "rb"))
    features = vectorizer.transform([email])
    prediction = model.predict(features)[0]
    return "Not Spam ✅" if prediction == 1 else "Spam ❌"

def check_with_ann(email):
    model = load_model("model_ann.keras")
    vectorizer = pickle.load(open("vectorizer.pkl", "rb"))
    features = vectorizer.transform([email]).toarray()
    prediction = model.predict(features)[0][0]
    return "Not Spam ✅" if prediction > 0.5 else "Spam ❌"

# Get user input
if __name__ == "__main__":
    print("=== Email Spam Classifier ===")

    user_input_1 = input("\nEnter email text to check with Logistic Regression:\n> ")
    print("Logistic Regression Prediction:", check_with_lr(user_input_1))

    user_input_2 = input("\nEnter email text to check with ANN:\n> ")
    print("ANN Prediction:", check_with_ann(user_input_2))


# In[ ]:




