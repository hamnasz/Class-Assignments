![Traffic Accident Analysis](traffic.jpg)


# Traffic Accident Analysis

## Project Overview
This project analyzes a dataset on traffic accidents and evaluates different machine learning models to classify accident types. The dataset undergoes exploratory data analysis (EDA), preprocessing, and training using various classification models. The goal is to determine which model performs best in predicting accident types based on available features.

## Dataset Details
The dataset `traffic_accidents.csv` contains information on traffic accidents, including categorical and numerical features. The `crash_type` column serves as the target variable. 

### Data Preprocessing
- Categorical columns are encoded using `LabelEncoder`.
- The `crash_date` column is dropped as it is not required for model training.
- The dataset is split into training (80%) and testing (20%) sets.

## Machine Learning Models Used
The following models were trained and evaluated:
1. **Random Forest Classifier**
2. **Logistic Regression**
3. **Decision Tree Classifier**
4. **K-Nearest Neighbors (KNN)**

## Model Performance
| Model                 | Accuracy |
|----------------------|----------|
| Random Forest       | 83.66%   |
| Logistic Regression | 83.16%   |
| Decision Tree       | 79.23%   |
| KNN                 | 74.52%   |

Random Forest achieved the highest accuracy among all models.

## Results and Insights
- **Random Forest** performed the best due to its ability to handle both categorical and numerical features while reducing overfitting.
- **Logistic Regression** performed slightly worse but is still a strong baseline model.
- **Decision Tree** had lower accuracy, likely due to overfitting on training data.
- **KNN** had the lowest accuracy as it is sensitive to feature scaling and data distribution.

## How to Run the Code
1. Clone this repository:
   ```sh
   git clone https://github.com/arpanpramanik2003/traffic-accident-analysis.git
   ```
2. Navigate to the project folder:
   ```sh
   cd traffic-accident-analysis
   ```
3. Install required dependencies:
   ```sh
   pip install -r requirements.txt
   ```

## Future Improvements
- Adding more advanced models such as **Gradient Boosting** and **Neural Networks**.
- Feature engineering to enhance model performance.
- Hyperparameter tuning for better optimization.
- Deployment using **Flask** or **Streamlit** for interactive visualization.

## Author
**Arpan Pramanik**

For any queries, feel free to connect with me on GitHub!
