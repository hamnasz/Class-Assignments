import streamlit as st
import pandas as pd
from joblib import load
import numpy as np # Used for potential numerical operations if needed

# --- Model and Pipeline Loading ---
# Ensure these .joblib and .pkl files are in the same directory as this app.py
# If they are in a different location, provide the full path to the files.

linear_model = None
rf_model = None
my_pipeline = None

# Load the Linear Regression model
try:
    linear_model = load('Dragon.joblib')
    st.success("Linear Regression model loaded successfully from 'Dragon.joblib'!")
except FileNotFoundError:
    st.error("Error: 'Dragon.joblib' (Linear Regression) not found. Please ensure your Linear Regression model is saved with this name and is in the correct directory.")
    st.stop() # Stop the app if a crucial model is missing
except Exception as e:
    st.error(f"Error loading Linear Regression model from 'Dragon.joblib': {e}")
    st.stop()

# Load the Random Forest model
try:
    rf_model = load('Dragon_RF.joblib')
    st.success("Random Forest model loaded successfully from 'Dragon_RF.joblib'!")
except FileNotFoundError:
    st.error("Error: 'Dragon_RF.joblib' (Random Forest) not found. Please ensure your Random Forest model is saved with this name and is in the correct directory.")
    st.stop()
except Exception as e:
    st.error(f"Error loading Random Forest model from 'Dragon_RF.joblib': {e}")
    st.stop()

# Load the preprocessing pipeline
try:
    my_pipeline = load('preprocessing_pipeline.pkl')
    st.success("Preprocessing pipeline loaded successfully from 'preprocessing_pipeline.pkl'!")
except FileNotFoundError:
    st.error("Error: 'preprocessing_pipeline.pkl' not found. Please ensure your preprocessing pipeline is saved and in the correct directory.")
    st.stop()
except Exception as e:
    st.error(f"Error loading preprocessing pipeline: {e}")
    st.stop()

# --- Feature Names ---
# This list defines the order of features expected by your models and pipeline
feature_names = [
    "CRIM", "ZN", "INDUS", "CHAS", "NOX", "RM", "AGE", "DIS",
    "RAD", "TAX", "PTRATIO", "B", "LSTAT"
]

# --- Streamlit UI for User Input ---
def get_user_input():
    st.sidebar.header("Input Features")

    # Sliders and selectbox for user to input feature values
    # The default, min, and max values are examples; adjust them based on your dataset's actual ranges
    CRIM = st.sidebar.slider("CRIM (Per capita crime rate by town)", 0.0, 90.0, 0.05, step=0.01)
    ZN = st.sidebar.slider("ZN (Proportion of residential land zoned for lots over 25,000 sq.ft.)", 0.0, 100.0, 0.0, step=0.1)
    INDUS = st.sidebar.slider("INDUS (Proportion of non-retail business acres per town)", 0.0, 30.0, 2.0, step=0.1)
    CHAS = st.sidebar.selectbox("CHAS (Charles River dummy variable: 1 if tract bounds river; 0 otherwise)", (0, 1), format_func=lambda x: "Yes" if x == 1 else "No")
    NOX = st.sidebar.slider("NOX (Nitric oxides concentration (parts per 10 million))", 0.3, 1.0, 0.5, step=0.001)
    RM = st.sidebar.slider("RM (Average number of rooms per dwelling)", 3.0, 9.0, 6.0, step=0.01)
    AGE = st.sidebar.slider("AGE (Proportion of owner-occupied units built prior to 1940)", 0.0, 100.0, 50.0, step=0.1)
    DIS = st.sidebar.slider("DIS (Weighted distances to five Boston employment centres)", 1.0, 15.0, 4.0, step=0.01)
    RAD = st.sidebar.slider("RAD (Index of accessibility to radial highways)", 1, 24, 3)
    TAX = st.sidebar.slider("TAX (Full-value property-tax rate per $10,000)", 180, 720, 300)
    PTRATIO = st.sidebar.slider("PTRATIO (Pupil-teacher ratio by town)", 10.0, 23.0, 18.0, step=0.1)
    B = st.sidebar.slider("B (1000(Bk - 0.63)^2 where Bk is the proportion of Black residents by town)", 0.0, 400.0, 350.0, step=0.1)
    LSTAT = st.sidebar.slider("LSTAT (% lower status of the population)", 0.0, 35.0, 10.0, step=0.1)

    # Create a dictionary from the input data
    data = {
        "CRIM": CRIM, "ZN": ZN, "INDUS": INDUS, "CHAS": CHAS, "NOX": NOX,
        "RM": RM, "AGE": AGE, "DIS": DIS, "RAD": RAD, "TAX": TAX,
        "PTRATIO": PTRATIO, "B": B, "LSTAT": LSTAT
    }
    # Convert dictionary to a Pandas DataFrame
    return pd.DataFrame([data])

# --- Prediction Logic and Display ---
def predict_house_price():
    user_input_df = get_user_input()

    # Create a button to trigger prediction
    if st.sidebar.button("Predict House Price"):
        st.subheader("User Input Features")
        st.write(user_input_df)

        # Transform the user input using the loaded preprocessing pipeline
        # It's crucial to pass the DataFrame with the correct feature order
        prepared_input = my_pipeline.transform(user_input_df[feature_names])

        st.subheader("🏡 Predicted House Prices")

        # --- Display Linear Regression Prediction ---
        if linear_model: # Check if the model was loaded successfully
            prediction_lr = linear_model.predict(prepared_input)
            st.write("### Linear Regression Model")
            # Assuming predictions are in thousands (as per your notebook's display format)
            st.success(f"Predicted Price: ${prediction_lr[0] * 1000:.2f}")
        else:
            st.warning("Linear Regression model not available for prediction.")

        st.markdown("---") # Add a separator for better visual distinction

        # --- Display Random Forest Prediction ---
        if rf_model: # Check if the model was loaded successfully
            prediction_rf = rf_model.predict(prepared_input)
            st.write("### Random Forest Model")
            # Assuming predictions are in thousands
            st.info(f"Predicted Price: ${prediction_rf[0] * 1000:.2f}")
        else:
            st.warning("Random Forest model not available for prediction.")

# --- Main Application Entry Point ---
if __name__ == "__main__":
    st.title("🏠 House Price Prediction App")
    st.write("This app predicts house prices using two models: *Linear Regression* and *Random Forest*. Adjust the features in the sidebar and click 'Predict House Price'.")
    predict_house_price()
