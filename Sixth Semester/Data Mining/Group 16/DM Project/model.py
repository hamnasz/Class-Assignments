import os
import joblib
import numpy as np
import pandas as pd

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler, LabelEncoder
from sklearn.metrics import accuracy_score, mean_absolute_error

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout, LSTM
from tensorflow.keras.utils import to_categorical

# ==========================================
# CREATE MODELS FOLDER
# ==========================================

os.makedirs("models", exist_ok=True)

# ==========================================
# LOAD DATASET
# ==========================================

df = pd.read_csv("seattle-weather.csv")

# Convert date column
df["date"] = pd.to_datetime(df["date"])

print("Dataset Loaded Successfully")
print(df.head())

# ==========================================
# WEATHER CLASSIFICATION MODEL
# ==========================================

print("\nTraining Weather Classification Model...")

features = [
    "precipitation",
    "temp_max",
    "temp_min",
    "wind"
]

X = df[features]
y = df["weather"]

# Encode labels
label_encoder = LabelEncoder()
y_encoded = label_encoder.fit_transform(y)

# Save encoder
joblib.dump(
    label_encoder,
    "models/label_encoder.pkl"
)

# Feature scaling
scaler = MinMaxScaler()

X_scaled = scaler.fit_transform(X)

# Save scaler
joblib.dump(
    scaler,
    "models/scaler.pkl"
)

# Train/Test Split
X_train, X_test, y_train, y_test = train_test_split(
    X_scaled,
    y_encoded,
    test_size=0.2,
    random_state=42
)

# Convert to categorical
y_train_cat = to_categorical(y_train)
y_test_cat = to_categorical(y_test)

# Build ANN model
classifier = Sequential()

classifier.add(
    Dense(
        64,
        activation="relu",
        input_shape=(X_train.shape[1],)
    )
)

classifier.add(Dropout(0.3))

classifier.add(
    Dense(
        32,
        activation="relu"
    )
)

classifier.add(Dropout(0.2))

classifier.add(
    Dense(
        len(label_encoder.classes_),
        activation="softmax"
    )
)

# Compile
classifier.compile(
    optimizer="adam",
    loss="categorical_crossentropy",
    metrics=["accuracy"]
)

# Train
classifier.fit(
    X_train,
    y_train_cat,
    epochs=30,
    batch_size=16,
    validation_split=0.2,
    verbose=1
)

# Save model
classifier.save(
    "models/weather_classifier.keras"
)

# Evaluate
predictions = classifier.predict(X_test)

predicted_classes = np.argmax(
    predictions,
    axis=1
)

accuracy = accuracy_score(
    y_test,
    predicted_classes
)

print(f"\nWeather Accuracy: {accuracy:.2f}")

# ==========================================
# TEMPERATURE FORECASTING MODEL
# ==========================================

print("\nTraining Temperature Forecasting Model...")

temp_data = df[
    ["temp_max", "temp_min"]
]

temp_scaler = MinMaxScaler()

scaled_temp = temp_scaler.fit_transform(
    temp_data
)

joblib.dump(
    temp_scaler,
    "models/temp_scaler.pkl"
)

sequence_length = 7

X_seq = []
y_seq = []

for i in range(sequence_length, len(scaled_temp)):
    X_seq.append(
        scaled_temp[
            i-sequence_length:i
        ]
    )

    y_seq.append(
        scaled_temp[i]
    )

X_seq = np.array(X_seq)
y_seq = np.array(y_seq)

X_train_seq, X_test_seq, y_train_seq, y_test_seq = train_test_split(
    X_seq,
    y_seq,
    test_size=0.2,
    random_state=42
)

# Build LSTM model
forecast_model = Sequential()

forecast_model.add(
    LSTM(
        64,
        return_sequences=True,
        input_shape=(
            X_train_seq.shape[1],
            X_train_seq.shape[2]
        )
    )
)

forecast_model.add(Dropout(0.2))

forecast_model.add(
    LSTM(32)
)

forecast_model.add(
    Dense(
        16,
        activation="relu"
    )
)

forecast_model.add(Dense(2))

# Compile
forecast_model.compile(
    optimizer="adam",
    loss="mean_squared_error",
    metrics=["mean_absolute_error"]
)

# Train
forecast_model.fit(
    X_train_seq,
    y_train_seq,
    epochs=30,
    batch_size=16,
    validation_split=0.2,
    verbose=1
)

# Save model
forecast_model.save(
    "models/temperature_forecaster.keras"
)

# Evaluate
temp_predictions = forecast_model.predict(
    X_test_seq
)

pred_actual = temp_scaler.inverse_transform(
    temp_predictions
)

actual = temp_scaler.inverse_transform(
    y_test_seq
)

mae = mean_absolute_error(
    actual,
    pred_actual
)

print(f"\nTemperature MAE: {mae:.2f}")

print("\nAll Models Saved Successfully!")