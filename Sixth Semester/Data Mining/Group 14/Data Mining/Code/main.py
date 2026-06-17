# healthcare_ai_suite.py
# Complete Healthcare AI Suite - Patient Segmentation & Heart Attack Prediction

import streamlit as st
import pandas as pd
import numpy as np
import time
import warnings
warnings.filterwarnings('ignore')

from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.cluster import KMeans, DBSCAN, AgglomerativeClustering
from sklearn.metrics import silhouette_score, davies_bouldin_score
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.ensemble import RandomForestClassifier, GradientBoostingClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import precision_score, recall_score, f1_score, confusion_matrix, roc_auc_score
from sklearn.impute import SimpleImputer
from sklearn.decomposition import PCA

import matplotlib.pyplot as plt
import seaborn as sns

# Page config
st.set_page_config(
    page_title="Healthcare AI Suite", 
    page_icon="🏥", 
    layout="wide",
    initial_sidebar_state="expanded"
)

# Custom CSS for professional look
st.markdown("""
<style>
    /* Main container styling */
    .main {
        padding: 0rem 1rem;
    }
    
    /* Card styling */
    .css-1r6slb0, .css-1v0mbdj {
        background-color: #f8f9fa;
        border-radius: 12px;
        padding: 1.5rem;
        box-shadow: 0 2px 4px rgba(0,0,0,0.1);
    }
    
    /* Metric cards */
    .metric-card {
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        padding: 1rem;
        border-radius: 10px;
        color: white;
        text-align: center;
    }
    
    /* Headers */
    h1, h2, h3 {
        color: #2c3e50;
        font-weight: 600;
    }
    
    /* Sidebar styling */
    .css-1d391kg {
        background-color: #2c3e50;
    }
    
    /* Button styling */
    .stButton > button {
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        color: white;
        border: none;
        border-radius: 8px;
        padding: 0.5rem 1rem;
        font-weight: 500;
        transition: all 0.3s ease;
    }
    
    .stButton > button:hover {
        transform: translateY(-2px);
        box-shadow: 0 4px 12px rgba(102, 126, 234, 0.4);
    }
    
    /* Success/Info/Warning boxes */
    .stAlert {
        border-radius: 8px;
        border-left: 4px solid;
    }
    
    /* Dataframe styling */
    .dataframe {
        border-radius: 8px;
        overflow: hidden;
    }
    
    /* Risk level indicators */
    .risk-high {
        background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%);
        padding: 1rem;
        border-radius: 10px;
        color: white;
    }
    
    .risk-moderate {
        background: linear-gradient(135deg, #fa709a 0%, #fee140 100%);
        padding: 1rem;
        border-radius: 10px;
        color: #2c3e50;
    }
    
    .risk-low {
        background: linear-gradient(135deg, #a8edea 0%, #fed6e3 100%);
        padding: 1rem;
        border-radius: 10px;
        color: #2c3e50;
    }
    
    /* Tabs styling */
    .stTabs [data-baseweb="tab-list"] {
        gap: 2rem;
        background-color: #f8f9fa;
        padding: 0.5rem;
        border-radius: 8px;
    }
    
    .stTabs [data-baseweb="tab"] {
        border-radius: 6px;
        padding: 0.5rem 1rem;
        font-weight: 500;
    }
</style>
""", unsafe_allow_html=True)

# Sidebar
with st.sidebar:
    st.markdown("# 🏥 Healthcare AI Suite")
    st.markdown("---")
    
    app_mode = st.radio(
        "Navigation",
        ["🎯 Patient Segmentation", "❤️ Heart Risk Predictor"],
        label_visibility="collapsed"
    )
    
    st.markdown("---")
    st.markdown("### ℹ️ About")
    st.markdown("""
    **Patient Segmentation**  
    Unsupervised clustering to identify patient groups based on health characteristics
    
    **Heart Risk Predictor**  
    ML classification to assess heart attack risk using clinical parameters
    """)
    
    st.markdown("---")
    st.markdown("### 📊 Dataset Info")
    if app_mode == "🎯 Patient Segmentation":
        st.markdown("- **Stroke Dataset**")
        st.markdown("- 5,110 patients")
        st.markdown("- 11 clinical features")
    else:
        st.markdown("- **Heart Attack Dataset**")
        st.markdown("- 8,763 patients")
        st.markdown("- 25 clinical features")
    
    st.markdown("---")
    st.caption("Made with ❤️ for Healthcare Analytics")

# File paths
STROKE_FILE = "healthcare-dataset-stroke-data.csv"
HEART_FILE = "heart_attack_prediction_dataset.csv"

def load_stroke_data():
    if os.path.exists(STROKE_FILE):
        return pd.read_csv(STROKE_FILE)
    return None

def load_heart_data():
    if os.path.exists(HEART_FILE):
        return pd.read_csv(HEART_FILE)
    return None

import os

# ============================================================================
# PATIENT SEGMENTATION MODULE
# ============================================================================

def patient_segmentation():
    st.title("🎯 Patient Segmentation")
    st.markdown("#### Unsupervised clustering to identify patient groups and stroke risk patterns")
    st.markdown("---")
    
    df = load_stroke_data()
    
    if df is not None:
        # Preprocessing
        with st.spinner("Loading and preprocessing data..."):
            df_clean = df.copy()
            if 'id' in df_clean.columns:
                df_clean.drop('id', axis=1, inplace=True)
            
            # Handle missing values
            original_len = len(df_clean)
            df_clean = df_clean.dropna()
            
            # Encode categorical variables
            label_cols = df_clean.select_dtypes(include=['object']).columns
            for col in label_cols:
                df_clean[col] = LabelEncoder().fit_transform(df_clean[col].astype(str))
            
            # Prepare features
            target_col = 'stroke' if 'stroke' in df_clean.columns else None
            if target_col:
                X = df_clean.drop(target_col, axis=1)
                y = df_clean[target_col]
            else:
                X = df_clean
            
            # Scale features
            scaler = StandardScaler()
            X_scaled = scaler.fit_transform(X)
        
        # Display dataset stats
        col1, col2, col3, col4 = st.columns(4)
        with col1:
            st.metric("Total Patients", f"{len(df_clean):,}")
        with col2:
            st.metric("Features", len(X.columns))
        with col3:
            st.metric("Missing Values", f"{df.isnull().sum().sum():,}")
        with col4:
            if target_col:
                stroke_rate = df_clean[target_col].mean() * 100
                st.metric("Stroke Rate", f"{stroke_rate:.1f}%")
        
        st.markdown("---")
        
        # Model selection
        col1, col2 = st.columns([1, 2])
        with col1:
            algo = st.selectbox(
                "Algorithm",
                ["KMeans", "Hierarchical", "DBSCAN"],
                help="Choose clustering algorithm based on your data characteristics"
            )
        
        with col2:
            if algo == "KMeans":
                n_clusters = st.slider("Number of Clusters", 2, 8, 3)
            elif algo == "Hierarchical":
                n_clusters = st.slider("Number of Clusters", 2, 8, 3)
                linkage = st.selectbox("Linkage", ["ward", "complete", "average"])
            else:
                eps = st.slider("Epsilon", 0.5, 2.5, 1.2, 0.1)
                min_samples = st.slider("Min Samples", 2, 10, 5)
        
        if st.button("Run Clustering", use_container_width=True):
            with st.spinner("Clustering in progress..."):
                if algo == "KMeans":
                    model = KMeans(n_clusters=n_clusters, random_state=42, n_init=10)
                elif algo == "Hierarchical":
                    model = AgglomerativeClustering(n_clusters=n_clusters, linkage=linkage)
                else:
                    model = DBSCAN(eps=eps, min_samples=min_samples)
                
                labels = model.fit_predict(X_scaled)
            
            # Results
            st.markdown("---")
            st.subheader("📊 Clustering Results")
            
            n_clusters_found = len(set(labels)) - (1 if -1 in labels else 0)
            
            col1, col2, col3 = st.columns(3)
            with col1:
                st.metric("Clusters Found", n_clusters_found)
            with col2:
                if len(set(labels)) > 1 and -1 not in labels:
                    sil_score = silhouette_score(X_scaled, labels)
                    st.metric("Silhouette Score", f"{sil_score:.3f}")
                else:
                    st.metric("Silhouette Score", "N/A")
            with col3:
                if algo == "DBSCAN":
                    noise = sum(labels == -1)
                    st.metric("Noise Points", f"{noise} ({noise/len(labels)*100:.1f}%)")
            
            # Visualization
            st.subheader("📈 Cluster Visualization")
            if X_scaled.shape[1] > 2:
                pca = PCA(n_components=2)
                X_vis = pca.fit_transform(X_scaled)
                exp_var = pca.explained_variance_ratio_.sum()
                st.caption(f"PCA - Explained variance: {exp_var:.1%}")
            else:
                X_vis = X_scaled
            
            fig, ax = plt.subplots(figsize=(10, 6))
            scatter = ax.scatter(X_vis[:, 0], X_vis[:, 1], c=labels, cmap='tab10', alpha=0.6, s=50)
            ax.set_title("Patient Clusters", fontsize=14, fontweight='bold')
            ax.set_xlabel("Component 1")
            ax.set_ylabel("Component 2")
            plt.colorbar(scatter, label='Cluster')
            st.pyplot(fig)
            
            # Risk analysis
            st.subheader("🎯 Risk Analysis by Cluster")
            df_result = df_clean.copy()
            df_result['Cluster'] = labels
            
            # Calculate risk scores
            risk_data = []
            for cluster in sorted(set(labels)):
                if cluster == -1:
                    continue
                cluster_data = df_result[df_result['Cluster'] == cluster]
                risk_score = 0
                if 'age' in cluster_data.columns:
                    risk_score += (cluster_data['age'].mean() > 60) * 2
                if 'bmi' in cluster_data.columns and cluster_data['bmi'].mean() > 30:
                    risk_score += 2
                if 'hypertension' in cluster_data.columns:
                    risk_score += cluster_data['hypertension'].mean() * 2
                if 'heart_disease' in cluster_data.columns:
                    risk_score += cluster_data['heart_disease'].mean() * 2
                
                risk_data.append({
                    'Cluster': cluster,
                    'Size': len(cluster_data),
                    'Risk Score': risk_score,
                    'Risk Level': 'High' if risk_score >= 4 else ('Moderate' if risk_score >= 2 else 'Low')
                })
            
            risk_df = pd.DataFrame(risk_data)
            st.dataframe(risk_df, use_container_width=True, hide_index=True)
            
            # Download
            st.download_button(
                label="📥 Download Results",
                data=df_result.to_csv(index=False),
                file_name="segmented_patients.csv",
                mime="text/csv",
                use_container_width=True
            )
    else:
        st.error("Stroke dataset not found. Please ensure 'healthcare-dataset-stroke-data.csv' is in the directory.")

# ============================================================================
# HEART RISK PREDICTOR MODULE
# ============================================================================

def heart_risk_predictor():
    st.title("❤️ Heart Risk Predictor")
    st.markdown("#### ML-based prediction of heart attack risk using clinical parameters")
    st.markdown("---")
    
    # Initialize session state
    if 'heart_model' not in st.session_state:
        st.session_state.heart_model = None
        st.session_state.heart_scaler = None
        st.session_state.heart_imputer = None
        st.session_state.heart_encoders = {}
        st.session_state.heart_features = None
        st.session_state.model_trained = False
    
    df = load_heart_data()
    
    if df is not None:
        # Preprocessing pipeline
        with st.spinner("Preprocessing data..."):
            df_processed = df.copy()
            
            # Store patient IDs for search
            if 'Patient ID' in df_processed.columns:
                patient_ids = df_processed['Patient ID'].tolist()
                patient_id_col = 'Patient ID'
            elif 'patient_id' in df_processed.columns:
                patient_ids = df_processed['patient_id'].tolist()
                patient_id_col = 'patient_id'
            else:
                patient_ids = [f"P{i+1:04d}" for i in range(len(df_processed))]
                df_processed['patient_id'] = patient_ids
                patient_id_col = 'patient_id'
            
            # Column names to lowercase
            df_processed.columns = df_processed.columns.str.lower().str.replace(' ', '_')
            
            # Drop patient ID from features
            if 'patient_id' in df_processed.columns:
                df_processed = df_processed.drop('patient_id', axis=1)
            
            # Parse blood pressure
            if 'blood_pressure' in df_processed.columns:
                bp_split = df_processed['blood_pressure'].str.split('/', expand=True)
                df_processed['systolic_bp'] = pd.to_numeric(bp_split[0], errors='coerce')
                df_processed['diastolic_bp'] = pd.to_numeric(bp_split[1], errors='coerce')
                df_processed = df_processed.drop('blood_pressure', axis=1)
            
            # Target column
            target_col = 'heart_attack_risk'
            if target_col not in df_processed.columns:
                for col in ['target', 'output', 'heartdisease']:
                    if col in df_processed.columns:
                        target_col = col
                        break
            
            X = df_processed.drop(target_col, axis=1)
            y = df_processed[target_col]
            
            # Encode categorical
            categorical_cols = X.select_dtypes(include=['object']).columns
            encoders = {}
            for col in categorical_cols:
                le = LabelEncoder()
                X[col] = le.fit_transform(X[col].astype(str))
                encoders[col] = le
            
            # Convert to numeric
            for col in X.columns:
                X[col] = pd.to_numeric(X[col], errors='coerce')
            
            # Impute
            imputer = SimpleImputer(strategy='median')
            X_imputed = pd.DataFrame(imputer.fit_transform(X), columns=X.columns)
            
            # Scale
            scaler = StandardScaler()
            X_scaled = scaler.fit_transform(X_imputed)
            
            feature_names = X.columns.tolist()
        
        # Dataset stats
        col1, col2, col3, col4 = st.columns(4)
        with col1:
            st.metric("Total Patients", f"{len(df):,}")
        with col2:
            st.metric("Features", len(feature_names))
        with col3:
            risk_count = y.sum()
            st.metric("High Risk", f"{risk_count} ({risk_count/len(y)*100:.1f}%)")
        with col4:
            st.metric("No Risk", f"{len(y)-risk_count} ({(len(y)-risk_count)/len(y)*100:.1f}%)")
        
        st.markdown("---")
        
        # Model training section
        with st.expander("⚙️ Model Configuration", expanded=not st.session_state.model_trained):
            col1, col2 = st.columns(2)
            with col1:
                model_choice = st.selectbox(
                    "Algorithm",
                    ["Random Forest", "Logistic Regression", "Gradient Boosting"]
                )
            with col2:
                test_size = st.slider("Test Split", 0.15, 0.35, 0.2, 0.05)
            
            if st.button("🚀 Train Model", use_container_width=True):
                with st.spinner("Training model..."):
                    X_train, X_test, y_train, y_test = train_test_split(
                        X_scaled, y, test_size=test_size, random_state=42, stratify=y
                    )
                    
                    if model_choice == "Random Forest":
                        model = RandomForestClassifier(n_estimators=100, random_state=42, class_weight='balanced')
                    elif model_choice == "Logistic Regression":
                        model = LogisticRegression(random_state=42, max_iter=1000, class_weight='balanced')
                    else:
                        model = GradientBoostingClassifier(n_estimators=100, random_state=42)
                    
                    model.fit(X_train, y_train)
                    
                    # Evaluate
                    y_pred = model.predict(X_test)
                    y_proba = model.predict_proba(X_test)[:, 1]
                    
                    
                    precision = precision_score(y_test, y_pred, zero_division=0)
                    recall = recall_score(y_test, y_pred, zero_division=0)
                    f1 = f1_score(y_test, y_pred, zero_division=0)
                    auc = roc_auc_score(y_test, y_proba)
                    
                    # Store in session
                    st.session_state.heart_model = model
                    st.session_state.heart_scaler = scaler
                    st.session_state.heart_imputer = imputer
                    st.session_state.heart_encoders = encoders
                    st.session_state.heart_features = feature_names
                    st.session_state.model_trained = True
                    
                    # Display metrics
                    st.subheader("📊 Model Performance")
                    
                    mcol1, mcol2, mcol3, mcol4 = st.columns(4)
                    mcol1.metric("Precision", f"{precision:.2%}")
                    mcol2.metric("Recall", f"{recall:.2%}")
                    mcol3.metric("F1 Score", f"{f1:.2%}")
                    mcol4.metric("AUC-ROC", f"{auc:.2%}")
                    
                    # Confusion matrix
                    fig, axes = plt.subplots(1, 2, figsize=(12, 4))
                    cm = confusion_matrix(y_test, y_pred)
                    sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', ax=axes[0])
                    axes[0].set_title('Confusion Matrix', fontweight='bold')
                    axes[0].set_xlabel('Predicted')
                    axes[0].set_ylabel('Actual')
                    
                    if hasattr(model, 'feature_importances_'):
                        importance = pd.DataFrame({
                            'Feature': feature_names[:len(model.feature_importances_)],
                            'Importance': model.feature_importances_
                        }).sort_values('Importance', ascending=False).head(10)
                        axes[1].barh(importance['Feature'], importance['Importance'], color='#667eea')
                        axes[1].set_title('Top Features', fontweight='bold')
                    else:
                        coef_df = pd.DataFrame({
                            'Feature': feature_names[:len(model.coef_[0])],
                            'Coefficient': model.coef_[0]
                        }).sort_values('Coefficient', ascending=False).head(10)
                        axes[1].barh(coef_df['Feature'], coef_df['Coefficient'], color='#667eea')
                        axes[1].set_title('Top Features', fontweight='bold')
                    
                    plt.tight_layout()
                    st.pyplot(fig)
        
        # Patient search and prediction
        if st.session_state.model_trained:
            st.markdown("---")
            st.subheader("🔍 Patient Risk Assessment")
            
            # Search
            search_col1, search_col2 = st.columns([3, 1])
            with search_col1:
                search_term = st.text_input("", placeholder="Enter Patient ID...", label_visibility="collapsed")
            with search_col2:
                search_clicked = st.button("Search", use_container_width=True)
            
            # Dropdown for quick selection
            selected = st.selectbox("Quick Select", ["-- Choose Patient --"] + patient_ids[:50])
            if selected != "-- Choose Patient --":
                search_term = selected
                search_clicked = True
            
            if search_clicked and search_term:
                # Find patient
                patient_row = None
                patient_id_val = None
                
                pid_col = patient_id_col.lower().replace(' ', '_')
                if pid_col in df_processed.columns:
                    df_temp = df_processed.copy()
                    df_temp[pid_col] = patient_ids
                else:
                    df_temp = df_processed.copy()
                    df_temp['patient_id'] = patient_ids
                    pid_col = 'patient_id'
                
                mask = df_temp[pid_col].astype(str).str.contains(str(search_term), case=False, na=False)
                if mask.any():
                    idx = mask[mask].index[0]
                    patient_row = df.iloc[idx]
                    patient_id_val = patient_ids[idx]
            
            if search_clicked and patient_row is not None:
                # Display patient info
                st.markdown(f"### 👤 Patient: {patient_id_val}")
                
                info_col1, info_col2 = st.columns(2)
                
                with info_col1:
                    st.markdown("**📋 Demographics**")
                    demo_fields = ['Age', 'Sex', 'BMI', 'Cholesterol']
                    for field in demo_fields:
                        if field in patient_row.index:
                            val = patient_row[field]
                            if field == 'Sex' and isinstance(val, str):
                                val = val.title()
                            st.metric(field, val)
                
                with info_col2:
                    st.markdown("**❤️ Clinical Metrics**")
                    clinical_fields = ['Blood Pressure', 'Heart Rate', 'Diabetes', 'Smoking']
                    for field in clinical_fields:
                        if field in patient_row.index:
                            val = patient_row[field]
                            if field in ['Diabetes', 'Smoking', 'Obesity'] and val in [0, 1, '0', '1']:
                                val = "Yes" if str(val) == '1' else "No"
                            st.metric(field, val)
                
                # Prepare prediction
                input_data = {}
                processed_row = patient_row.copy()
                
                # Handle blood pressure
                if 'Blood Pressure' in processed_row.index:
                    bp = str(processed_row['Blood Pressure'])
                    if '/' in bp:
                        parts = bp.split('/')
                        systolic = float(parts[0]) if parts[0].replace('.', '').isdigit() else 0
                        diastolic = float(parts[1]) if parts[1].replace('.', '').isdigit() else 0
                    else:
                        systolic = diastolic = 0
                    processed_row['systolic_bp'] = systolic
                    processed_row['diastolic_bp'] = diastolic
                
                processed_row.index = processed_row.index.str.lower().str.replace(' ', '_')
                
                for feature in st.session_state.heart_features:
                    if feature in processed_row.index:
                        val = processed_row[feature]
                        if feature in st.session_state.heart_encoders:
                            try:
                                val = st.session_state.heart_encoders[feature].transform([str(val)])[0]
                            except:
                                val = 0
                        else:
                            try:
                                val = float(val)
                            except:
                                val = 0
                        input_data[feature] = val
                    else:
                        input_data[feature] = 0
                
                # Predict
                input_df = pd.DataFrame([input_data])
                input_df = input_df[st.session_state.heart_features]
                input_imputed = st.session_state.heart_imputer.transform(input_df)
                input_scaled = st.session_state.heart_scaler.transform(input_imputed)
                
                risk_proba = st.session_state.heart_model.predict_proba(input_scaled)[0, 1]
                
                # Display prediction
                st.markdown("---")
                st.markdown("### 🩺 Risk Assessment")
                
                # Risk gauge
                if risk_proba >= 0.7:
                    risk_level = "HIGH RISK"
                    risk_color = "#f5576c"
                    recommendation = "Immediate medical attention required. Consult a cardiologist urgently."
                elif risk_proba >= 0.4:
                    risk_level = "MODERATE RISK"
                    risk_color = "#fee140"
                    recommendation = "Schedule a check-up. Consider lifestyle modifications."
                elif risk_proba >= 0.2:
                    risk_level = "ELEVATED RISK"
                    risk_color = "#fa709a"
                    recommendation = "Monitor regularly. Maintain healthy habits."
                else:
                    risk_level = "LOW RISK"
                    risk_color = "#a8edea"
                    recommendation = "Continue healthy lifestyle. Annual check-ups recommended."
                
                # Display actual if available
                actual_col = 'heart_attack_risk' if 'heart_attack_risk' in patient_row.index else target_col
                actual_val = patient_row[actual_col] if actual_col in patient_row.index else None
                
                col1, col2, col3 = st.columns(3)
                with col1:
                    st.metric("Risk Probability", f"{risk_proba:.1%}")
                with col2:
                    st.metric("Risk Level", risk_level)
                with col3:
                    if actual_val is not None:
                        st.metric("Ground Truth", "Risk" if actual_val == 1 else "No Risk")
                
                st.markdown(f"""
                <div style='background: linear-gradient(135deg, {risk_color}20 0%, {risk_color}40 100%); 
                            padding: 1rem; border-radius: 10px; border-left: 4px solid {risk_color};'>
                    <strong>💡 Recommendation</strong><br>{recommendation}
                </div>
                """, unsafe_allow_html=True)
                
            elif search_clicked:
                st.warning(f"Patient '{search_term}' not found.")
        
        elif not st.session_state.model_trained:
            st.info("👆 Configure and train a model above to start predicting.")
    
    else:
        st.error("Heart attack dataset not found. Please ensure 'heart_attack_prediction_dataset.csv' is in the directory.")

# ============================================================================
# MAIN APP
# ============================================================================

if app_mode == "🎯 Patient Segmentation":
    patient_segmentation()
else:
    heart_risk_predictor()