#!/usr/bin/env python
# coding: utf-8

# In[10]:


import pandas as pd


# In[12]:


data = pd.read_csv('C:/Users/HP/Downloads/archive (2)/Cellphone.csv')


# In[14]:


data


# In[19]:


import numpy as np


# In[21]:


import matplotlib.pyplot as plt


# In[22]:


import seaborn as sns


# In[ ]:


1: Reading Data


# In[28]:


data = pd.read_csv(r'C:/Users/HP/Downloads/archive (2)/Cellphone.csv')

data.head()


# In[30]:


data.head(2)


# In[32]:


data.head(30)


# In[34]:


data.tail()


# In[36]:


data.shape


# In[38]:


data.tail(20)


# In[40]:


data.sample()


# In[42]:


data.sample(30)


# In[16]:


data.describe()


# 2: Data Cleaning
# -
# 

# In[21]:


data.isnull().sum()


# In[50]:


import pandas as pd
import numpy as np


numeric_cols = data.select_dtypes(include=[np.number])
non_numeric_cols = data.select_dtypes(exclude=[np.number])


numeric_cols = numeric_cols.fillna(numeric_cols.mean())


for col in non_numeric_cols.columns:
    if non_numeric_cols[col].isnull().any():
        non_numeric_cols[col] = non_numeric_cols[col].fillna(non_numeric_cols[col].mode()[0])


data = pd.concat([numeric_cols, non_numeric_cols], axis=1)


missing_values = data.isnull().sum()
print(missing_values)


# In[52]:


data.shape


# In[ ]:


Removal: Deleting rows with missing values.


# In[56]:


data.shape


# In[58]:


data.dropna(inplace=True)


missing_values = data.isnull().sum()
print(missing_values)


# In[60]:


data.shape


# In[ ]:


Removing Duplicates


# In[62]:


data = pd.read_csv(r'C:/Users/HP/Downloads/archive (2)/Cellphone.csv')
data.shape


# In[64]:


data.drop_duplicates(inplace=True)
data.shape


# In[ ]:


3: Outlier Detection and Removal


# In[66]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv(r'C:/Users/HP/Downloads/archive (2)/Cellphone.csv')



data.describe()


# In[68]:


0.25-1.5*0.5


# In[70]:


0.75 + 1.5 * 0.5


# In[72]:


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


# In[76]:


plt.figure(figsize=(20, 6))


plt.subplot(1, 2, 2)
data_cleaned.select_dtypes(include=[np.number]).boxplot()
plt.title("After Outlier Removal")

plt.tight_layout()
plt.show()


# In[74]:


data_cleaned.shape


# In[76]:


data_cleaned.head()


# In[ ]:


4. Data Transformation


# In[78]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler


data = pd.read_csv(r'C:/Users/HP/Downloads/archive (2)/Cellphone.csv')


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


# In[ ]:


Standardization


# In[80]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler


data = pd.read_csv(r'C:/Users/HP/Downloads/archive (2)/Cellphone.csv')


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


# In[ ]:


5: One-Hot Encoding


# In[82]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler


data = pd.read_csv(r'C:/Users/HP/Downloads/archive (2)/Cellphone.csv')
data.head(2)


# In[88]:


import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler


data = pd.read_csv(r'C:/Users/HP/Downloads/archive (2)/Cellphone.csv')


cat_features = [feature for feature in data.columns if data[feature].dtype == 'O']


data1 = pd.get_dummies(data, columns=cat_features)


scaled_data = pd.concat([data, data1], axis=1)


print(scaled_data.shape)
print()
print('*' * 70)

scaled_data.head()


# In[90]:


data.columns


# In[92]:


scaled_data.columns


# In[94]:


data1.head()


# In[ ]:


6: Data Reduction¶


# In[96]:


scaled_data.shape


# In[ ]:


7: Handling Imbalanced Data
Resampling Techniques
Oversampling


# In[100]:


data.shape


# In[114]:


from sklearn.preprocessing import StandardScaler
import pandas as pd


numeric_features = data.select_dtypes(include=[np.number]).columns


scaler = StandardScaler()
data[numeric_features] = scaler.fit_transform(data[numeric_features])


if 'price' in data.columns:
    if data['price'].dtype != 'int64' and data['price'].dtype != 'bool':
        data['price'] = (data['price'] > 0.5).astype(int)

   
if 'price' in data.columns:
    X = data.drop(columns=['price'])
else:
    print("'price' column does not exist. Cannot drop it.")
    X = data.copy() 


# In[120]:


import pandas as pd
from sklearn.utils import resample


data = pd.read_csv(r'C:/Users/HP/Downloads/archive (2)/Cellphone.csv')


print("Columns before resampling:", data.columns)


data_resampled = resample(data, replace=True, n_samples=len(data), random_state=42)


print("Columns after resampling:", data_resampled.columns)


if 'price' in data_resampled.columns:
    print(data_resampled['price'].value_counts(normalize=True))
else:
    print("'price' column not found in data_resampled.")



# In[122]:


data_resampled.shape


# In[ ]:


8: Splitting Data


# In[3]:


import pandas as pd
from sklearn.model_selection import train_test_split


data = pd.read_csv(r'C:/Users/HP/Downloads/archive (2)/Cellphone.csv')


if 'price' in data.columns:
  
    X = data.drop('price', axis=1)
    y = data['price']

    
    X = pd.get_dummies(X, drop_first=True)

    
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.3, random_state=42
    )

    print("Data split successful!")
    print("X_train shape:", X_train.shape)
    print("X_test shape:", X_test.shape)
else:
    print("Column 'price' not found in the dataset.")


# In[ ]:


Regression


# In[6]:


import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error


np.random.seed(42)
X = 2 * np.random.rand(100, 1)
y = 4 + 3 * X + np.random.randn(100, 1)


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


model = LinearRegression()
model.fit(X_train, y_train)


y_pred = model.predict(X_test)


mse = mean_squared_error(y_test, y_pred)
print(f'Mean Squared Error: {mse}')


plt.scatter(X_test, y_test, color='blue', label='Actual data')
plt.plot(X_test, y_pred, color='red', linewidth=2, label='Regression line')
plt.xlabel('X')
plt.ylabel('y')
plt.legend()
plt.title('Linear Regression Model')
plt.show()


# In[ ]:


Evaluation


# In[8]:


import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score

np.random.seed(42)
X = 2 * np.random.rand(100, 1)
y = 4 + 3 * X + np.random.randn(100, 1)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)

y_pred = model.predict(X_test)

mse = mean_squared_error(y_test, y_pred)
mae = mean_absolute_error(y_test, y_pred)
rmse = np.sqrt(mse)
r2 = r2_score(y_test, y_pred)

print(f'Mean Squared Error (MSE): {mse}')
print(f'Mean Absolute Error (MAE): {mae}')
print(f'Root Mean Squared Error (RMSE): {rmse}')
print(f'R² Score: {r2}')


# In[ ]:




