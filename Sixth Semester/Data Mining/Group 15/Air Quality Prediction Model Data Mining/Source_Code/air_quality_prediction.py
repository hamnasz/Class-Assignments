# =============================================================================
#  Air Quality Prediction Using Machine Learning and Data Mining Techniques
#  Plain-Python version (for VS Code / command line).
#  Student: Abdul Manan Tanveer  |  Reg #: 2023-BS-AI-173
#
#  Run from inside the Source_Code folder:   python air_quality_prediction.py
#  It prints results to the screen and saves graphs into the "figures" folder.
# =============================================================================

import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import r2_score, mean_absolute_error, mean_squared_error

sns.set_style("whitegrid")
os.makedirs("figures", exist_ok=True)

# ---------------------------------------------------------------- 1. LOAD
print("Step 1: Loading dataset ...")
df = pd.read_csv("../Dataset/AirQualityUCI.csv")
df = df.loc[:, ~df.columns.str.contains("^Unnamed")].dropna(how="all").reset_index(drop=True)
print("   shape:", df.shape)

# ---------------------------------------------------------------- 2. CLEAN
print("Step 2: Cleaning data (missing code -200, dropping NMHC) ...")
df = df.replace(-200, np.nan).drop(columns=["NMHC(GT)"])
num_cols = df.select_dtypes(include=[np.number]).columns
df[num_cols] = df[num_cols].fillna(df[num_cols].median())
dt = pd.to_datetime(df["Date"] + " " + df["Time"], format="%d-%m-%Y %H:%M:%S", errors="coerce")
df["Hour"], df["Month"] = dt.dt.hour, dt.dt.month
df.to_csv("../Dataset/air_quality_cleaned.csv", index=False)

# ---------------------------------------------------------------- 3. EDA
print("Step 3: Exploratory Data Analysis (saving graphs) ...")
plt.figure(figsize=(9, 7))
corr = df.drop(columns=["Hour", "Month"]).select_dtypes(include=[np.number]).corr()
sns.heatmap(corr, annot=True, fmt=".2f", cmap="coolwarm", annot_kws={"size": 7})
plt.title("Correlation heatmap")
plt.tight_layout(); plt.savefig("figures/eda_corr.png", dpi=130); plt.close()

# ---------------------------------------------------------------- 4. FEATURES + SPLIT
target = "CO(GT)"
X = df.drop(columns=["Date", "Time", target])
y = df[target]
X_tr, X_te, y_tr, y_te = train_test_split(X, y, test_size=0.2, random_state=42)
scaler = StandardScaler()
X_tr_s = scaler.fit_transform(X_tr)
X_te_s = scaler.transform(X_te)

# ---------------------------------------------------------------- 5. TRAIN + EVALUATE
print("Step 4: Training and evaluating models ...")
models = {
    "Linear Regression": LinearRegression(),
    "Decision Tree":      DecisionTreeRegressor(max_depth=10, random_state=42),
    "Random Forest":      RandomForestRegressor(n_estimators=150, random_state=42),
}
results = []
for name, model in models.items():
    model.fit(X_tr_s, y_tr)
    pred = model.predict(X_te_s)
    results.append({
        "Model": name,
        "R2":   round(r2_score(y_te, pred), 3),
        "MAE":  round(mean_absolute_error(y_te, pred), 3),
        "RMSE": round(np.sqrt(mean_squared_error(y_te, pred)), 3),
    })

res_df = pd.DataFrame(results).sort_values("R2", ascending=False)
print("\n===== MODEL COMPARISON =====")
print(res_df.to_string(index=False))
best = res_df.iloc[0]["Model"]
print("\nBest model:", best)

plt.figure(figsize=(6, 3.5))
sns.barplot(data=res_df, x="Model", y="R2", palette="viridis")
plt.ylim(0, 1.05); plt.title("Model comparison - R2 score")
plt.tight_layout(); plt.savefig("figures/model_compare.png", dpi=130); plt.close()

print("\nDone! Graphs saved in the 'figures' folder.")
