import streamlit as st
import pandas as pd
import numpy as np
import joblib
import matplotlib.pyplot as plt

from tensorflow.keras.models import load_model

# =====================================
# PAGE SETTINGS
# =====================================

st.set_page_config(
    page_title="Weather Forecasting",
    layout="wide"
)

st.title(
    "Weather Forecasting Using Data Mining and Predictive Analytics Models"
)

st.write(
    "Deep Learning Based Weather Prediction System"
)

# =====================================
# LOAD DATASET
# =====================================

df = pd.read_csv(
    "seattle-weather.csv"
)

# =====================================
# LOAD MODELS
# =====================================

classifier = load_model(
    "models/weather_classifier.keras",
    compile=False
)

forecast_model = load_model(
    "models/temperature_forecaster.keras",
    compile=False
)

scaler = joblib.load(
    "models/scaler.pkl"
)

temp_scaler = joblib.load(
    "models/temp_scaler.pkl"
)

encoder = joblib.load(
    "models/label_encoder.pkl"
)

# =====================================
# SIDEBAR
# =====================================

menu = st.sidebar.selectbox(
    "Navigation",
    [
        "Home",
        "Weather Prediction",
        "Temperature Forecasting"
    ]
)

# =====================================
# HOME PAGE
# =====================================

if menu == "Home":

    st.header("Dataset Overview")

    st.dataframe(df.head())

    st.subheader("Statistical Summary")

    st.write(df.describe())

    # Weather Distribution
    st.subheader(
        "Weather Type Distribution"
    )

    weather_count = (
        df["weather"]
        .value_counts()
    )

    fig, ax = plt.subplots()

    ax.bar(
        weather_count.index,
        weather_count.values
    )

    ax.set_xlabel(
        "Weather Type"
    )

    ax.set_ylabel(
        "Count"
    )

    st.pyplot(fig)

    # Temperature Trend
    st.subheader(
        "Temperature Trends"
    )

    fig2, ax2 = plt.subplots()

    ax2.plot(
        df["temp_max"],
        label="Maximum Temp"
    )

    ax2.plot(
        df["temp_min"],
        label="Minimum Temp"
    )

    ax2.legend()

    st.pyplot(fig2)

# =====================================
# WEATHER PREDICTION
# =====================================

elif menu == "Weather Prediction":

    st.header(
        "Predict Weather"
    )

    precipitation = st.number_input(
        "Precipitation",
        min_value=0.0
    )

    temp_max = st.number_input(
        "Maximum Temperature"
    )

    temp_min = st.number_input(
        "Minimum Temperature"
    )

    wind = st.number_input(
        "Wind Speed",
        min_value=0.0
    )

    if st.button(
        "Predict Weather"
    ):

        user_data = np.array([
            [
                precipitation,
                temp_max,
                temp_min,
                wind
            ]
        ])

        scaled_input = scaler.transform(
            user_data
        )

        prediction = classifier.predict(
            scaled_input
        )

        class_index = np.argmax(
            prediction
        )

        predicted_weather = (
            encoder.inverse_transform(
                [class_index]
            )[0]
        )

        confidence = (
            np.max(prediction)
            * 100
        )

        st.success(
            f"Predicted Weather: {predicted_weather}"
        )

        st.info(
            f"Confidence: {confidence:.2f}%"
        )

# =====================================
# TEMPERATURE FORECAST
# =====================================

elif menu == "Temperature Forecasting":

    st.header(
        "Next Day Temperature Forecast"
    )

    st.write(
        "Enter temperatures for the previous 7 days"
    )

    max_temps = []
    min_temps = []

    for i in range(7):

        col1, col2 = st.columns(2)

        with col1:
            max_temp = st.number_input(
                f"Day {i+1} Max Temp",
                key=f"max{i}"
            )

        with col2:
            min_temp = st.number_input(
                f"Day {i+1} Min Temp",
                key=f"min{i}"
            )

        max_temps.append(
            max_temp
        )

        min_temps.append(
            min_temp
        )

    if st.button(
        "Forecast Temperature"
    ):

        sequence = np.array(
            list(
                zip(
                    max_temps,
                    min_temps
                )
            )
        )

        scaled_sequence = (
            temp_scaler.transform(
                sequence
            )
        )

        scaled_sequence = np.expand_dims(
            scaled_sequence,
            axis=0
        )

        prediction = (
            forecast_model.predict(
                scaled_sequence
            )
        )

        prediction = (
            temp_scaler
            .inverse_transform(
                prediction
            )
        )

        max_prediction = (
            prediction[0][0]
        )

        min_prediction = (
            prediction[0][1]
        )

        st.success(
            f"Predicted Maximum Temperature: {max_prediction:.2f}°C"
        )

        st.success(
            f"Predicted Minimum Temperature: {min_prediction:.2f}°C"
        )