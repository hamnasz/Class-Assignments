"""
=============================================================================
  Spam Email Detection System  Streamlit Web App
=============================================================================
  Run with:   streamlit run spam_detection_app.py
  Requirements:
      pip install streamlit scikit-learn nltk joblib
=============================================================================
"""

import os
import re
import string
import warnings
warnings.filterwarnings("ignore")

import streamlit as st
import joblib
import nltk
from nltk.corpus import stopwords
from nltk.stem import PorterStemmer
from nltk.tokenize import word_tokenize

# ─────────────────────────────────────────────────────────────────────────────
# Page configuration  (must be the FIRST Streamlit call)
# ─────────────────────────────────────────────────────────────────────────────
st.set_page_config(
    page_title="Spam Email Detection System",
    page_icon="📧",
    layout="centered",
    initial_sidebar_state="collapsed",
)


# ─────────────────────────────────────────────────────────────────────────────
# Download NLTK resources (silent, runs only if not already present)
# ─────────────────────────────────────────────────────────────────────────────
@st.cache_resource(show_spinner=False)
def _download_nltk():
    for resource in ["punkt", "stopwords", "punkt_tab"]:
        nltk.download(resource, quiet=True)

_download_nltk()


# ─────────────────────────────────────────────────────────────────────────────
# Load model & vectoriser (cached so they load only once)
# ─────────────────────────────────────────────────────────────────────────────
MODEL_DIR  = "models"
MODEL_PATH = os.path.join(MODEL_DIR, "best_model.pkl")
TFIDF_PATH = os.path.join(MODEL_DIR, "tfidf_vectorizer.pkl")
NAME_PATH  = os.path.join(MODEL_DIR, "best_model_name.txt")


@st.cache_resource(show_spinner="Loading model…")
def load_artifacts():
    """Load the trained model and TF-IDF vectoriser from disk."""
    if not os.path.exists(MODEL_PATH):
        raise FileNotFoundError(
            f"Model file not found at '{MODEL_PATH}'. "
            "Please run the Jupyter Notebook first to train and save the model."
        )
    if not os.path.exists(TFIDF_PATH):
        raise FileNotFoundError(
            f"Vectoriser file not found at '{TFIDF_PATH}'. "
            "Please run the Jupyter Notebook first."
        )

    model  = joblib.load(MODEL_PATH)
    tfidf  = joblib.load(TFIDF_PATH)

    model_name = "Best Model"
    if os.path.exists(NAME_PATH):
        with open(NAME_PATH, "r") as f:
            model_name = f.read().strip()

    return model, tfidf, model_name


# ─────────────────────────────────────────────────────────────────────────────
# Text preprocessing  (IDENTICAL to the notebook pipeline)
# ─────────────────────────────────────────────────────────────────────────────
@st.cache_resource(show_spinner=False)
def _get_preprocessor():
    """Return shared stopwords set and stemmer (cached)."""
    sw = set(stopwords.words("english"))
    ps = PorterStemmer()
    return sw, ps


def preprocess_text(text: str) -> str:
    """
    Preprocess a single email string using the same pipeline as the notebook:
      1. Lowercase
      2. Remove URLs
      3. Remove email addresses
      4. Remove punctuation & digits
      5. Tokenise
      6. Remove stopwords and very short tokens
      7. Stem
      8. Re-join
    """
    STOPWORDS, stemmer = _get_preprocessor()

    text = str(text).lower()
    text = re.sub(r"http\S+|www\.\S+", "", text)           # remove URLs
    text = re.sub(r"\S+@\S+", "", text)                     # remove emails
    text = re.sub(r"[^a-z\s]", "", text)                    # remove non-alpha
    tokens = word_tokenize(text)
    tokens = [t for t in tokens if t not in STOPWORDS and len(t) > 2]
    tokens = [stemmer.stem(t) for t in tokens]
    return " ".join(tokens)


# ─────────────────────────────────────────────────────────────────────────────
# Prediction helper
# ─────────────────────────────────────────────────────────────────────────────
def predict_email(text: str, model, tfidf):
    """
    Preprocess → vectorise → predict.

    Returns:
        label       (str)  : 'Spam' or 'Ham'
        confidence  (float): probability between 0 and 1 (if available)
        has_proba   (bool) : whether confidence is available
    """
    cleaned    = preprocess_text(text)
    vectorised = tfidf.transform([cleaned])
    prediction = model.predict(vectorised)[0]

    label = "Spam" if prediction == 1 else "Ham"

    # Try to get probability (not all models support predict_proba)
    has_proba  = False
    confidence = None
    if hasattr(model, "predict_proba"):
        proba      = model.predict_proba(vectorised)[0]
        confidence = proba[prediction]          # confidence in the predicted class
        has_proba  = True
    elif hasattr(model, "decision_function"):
        # LinearSVC: use distance from hyperplane, convert to 0-1 range via sigmoid
        import math
        raw_score  = model.decision_function(vectorised)[0]
        confidence = 1 / (1 + math.exp(-raw_score))
        # For ham (class 0) the score is negative, so flip
        if prediction == 0:
            confidence = 1 - confidence
        has_proba  = True

    return label, confidence, has_proba


# ─────────────────────────────────────────────────────────────────────────────
# UI Layout
# ─────────────────────────────────────────────────────────────────────────────
def main():
    # ── Header ───────────────────────────────────────────────────────────────
    st.title("📧 Spam Email Detection System")
    st.markdown(
        "Paste any email text below and click **Check Email** to instantly "
        "detect whether it is **Spam** or **Legitimate (Ham)**."
    )
    st.divider()

    # ── Load model ───────────────────────────────────────────────────────────
    try:
        model, tfidf, model_name = load_artifacts()
    except FileNotFoundError as e:
        st.error(f"⚠️ {e}")
        st.info(
            "**How to fix:** Run all cells in `spam_detection_notebook.ipynb` first. "
            "This will create the `models/` folder with the trained model and vectoriser."
        )
        st.stop()
    except Exception as e:
        st.error(f"Unexpected error loading model: {e}")
        st.stop()

    # Show active model in sidebar
    with st.sidebar:
        st.header("ℹ️ About")
        st.markdown(
            f"**Active Model:** {model_name}\n\n"
            "This app uses a machine-learning model trained on 190k+ spam/ham "
            "emails. The text is preprocessed (lowercasing, stopword removal, "
            "stemming) before being vectorised with TF-IDF."
        )
        st.divider()
        st.markdown("**Labels:**\n- 🔴 Spam — unwanted / malicious email\n- 🟢 Ham — legitimate email")

    # ── Email input ──────────────────────────────────────────────────────────
    email_text = st.text_area(
        label="✉️ Paste email text here:",
        height=250,
        placeholder=(
            "Example:\n"
            "Congratulations! You have been selected as a winner. "
            "Click here to claim your FREE prize now!"
        ),
    )

    col_btn, col_clear = st.columns([2, 1])
    check_clicked = col_btn.button("🔍 Check Email", type="primary", use_container_width=True)
    clear_clicked = col_clear.button("🗑️ Clear", use_container_width=True)

    if clear_clicked:
        st.rerun()

    # ── Prediction ───────────────────────────────────────────────────────────
    if check_clicked:
        if not email_text.strip():
            st.warning("⚠️ Please paste some email text before clicking **Check Email**.")
            st.stop()

        with st.spinner("Analysing email…"):
            try:
                label, confidence, has_proba = predict_email(email_text, model, tfidf)
            except Exception as e:
                st.error(f"Error during prediction: {e}")
                st.stop()

        st.divider()
        st.subheader("📊 Detection Result")

        # ── Result banner ────────────────────────────────────────────────────
        if label == "Spam":
            st.error(
                f"🔴  **SPAM DETECTED**\n\n"
                f"This email appears to be **spam**. Exercise caution."
            )
        else:
            st.success(
                f"🟢  **LEGITIMATE EMAIL (Ham)**\n\n"
                f"This email appears to be **safe**."
            )

        # ── Confidence score ─────────────────────────────────────────────────
        if has_proba and confidence is not None:
            pct = confidence * 100
            st.markdown(f"**Prediction Confidence:** `{pct:.1f}%`")
            st.progress(confidence)

            # Friendly interpretation
            if pct >= 95:
                st.caption("Very high confidence — model is almost certain.")
            elif pct >= 80:
                st.caption("High confidence — model is fairly sure.")
            elif pct >= 60:
                st.caption("Moderate confidence — review manually if in doubt.")
            else:
                st.caption("Low confidence — this email is borderline; review manually.")
        else:
            st.caption("Confidence score not available for this model type.")

        # ── Preprocessing details (expander) ─────────────────────────────────
        with st.expander("🔬 See how the email was preprocessed"):
            cleaned = preprocess_text(email_text)
            st.markdown("**Original text (first 500 chars):**")
            st.code(email_text[:500], language=None)
            st.markdown("**After preprocessing:**")
            st.code(cleaned[:500] if cleaned else "(empty after preprocessing)", language=None)
            token_count = len(cleaned.split())
            st.caption(f"Token count after preprocessing: **{token_count}**")

    # ── Footer ────────────────────────────────────────────────────────────────
    st.divider()
    st.caption(
        f"Model: {model_name}  |  Dataset: 190k Spam/Ham Email Dataset  |  "
        "Built with Python · NLTK · Scikit-learn · Streamlit"
    )


if __name__ == "__main__":
    main()
