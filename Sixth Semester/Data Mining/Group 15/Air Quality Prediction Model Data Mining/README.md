# Air Quality Prediction Using Machine Learning and Data Mining Techniques

**Student:** Abdul Manan Tanveer  |  **Reg #:** 2023-BS-AI-173  
**Program:** BS Artificial Intelligence  |  **Subject:** Data Mining  |  **Submitted To:** Sir Arham

---

## What this project does
It predicts the **carbon-monoxide concentration `CO(GT)`** in the air from low-cost sensor
readings and weather data, using the real **UCI Air Quality dataset** (9,357 hourly records
from an Italian city, 2004–2005). Three models are compared; **Random Forest** wins with an
**R² of ~0.90**.

## Folder structure
```
Air_Quality_Prediction_Project/
├── Source_Code/
│   ├── Air_Quality_Prediction.ipynb   <- main notebook (already run, with outputs)
│   ├── air_quality_prediction.py      <- same project as a plain script
│   ├── requirements.txt               <- libraries to install
│   └── figures/                       <- graphs saved by the code
├── Dataset/
│   ├── AirQualityUCI.csv              <- the real dataset
│   └── air_quality_cleaned.csv       <- cleaned version (created when you run the code)
├── Project_Report/
│   └── Air_Quality_Prediction_Report.pdf
├── Research_Article/
│   └── Research_Article_References.pdf
├── Documentation/
│   └── User_Guide.pdf                 <- step-by-step running instructions
└── README.md                          <- this file
```

## Quick start (3 steps)
1. Install Anaconda (gives you Python + Jupyter).
2. In the Anaconda Prompt, go to `Source_Code` and run: `pip install -r requirements.txt`
3. Run `jupyter notebook`, open `Air_Quality_Prediction.ipynb`, then **Cell → Run All**.

Full beginner instructions are in **Documentation/User_Guide.pdf**.

## Dataset source
UCI Machine Learning Repository — Air Quality Data Set:
https://archive.ics.uci.edu/ml/datasets/Air+Quality
(Original paper: De Vito et al., *Sensors and Actuators B: Chemical*, 2008.)
