# Sixth Semester

This folder contains coursework, lab manuals, and code projects for the Sixth Semester of the BS Artificial Intelligence program. The materials are primarily Jupyter Notebooks and cover topics such as Data Mining and related assignments.

Language composition in this folder (approximate):
- Jupyter Notebooks
- C++
- Python

Contents
- Data Mining/
  - Notebooks, assignments and lab manuals for the Data Mining course.

How to use
1. Clone the repository:
   ```bash
   git clone https://github.com/hamnasz/Class-Assignments.git
   cd "Class-Assignments/Sixth Semester"
   ```
2. Recommended environment (conda):
   ```bash
   conda create -n ai-s6 python=3.10 -y
   conda activate ai-s6
   pip install -r requirements.txt  # if a requirements file is present
   # common packages:
   pip install jupyterlab numpy pandas scikit-learn matplotlib seaborn
   ```
3. Start JupyterLab or Jupyter Notebook and open the .ipynb files:
   ```bash
   jupyter lab
   ```

Notes
- Notebooks may require datasets stored in subfolders; open the notebooks in the repository root so relative paths resolve correctly.
- If a `requirements.txt` or environment file is present in a subfolder, prefer using that for reproducing results.

Contact
If you find errors or want to contribute improvements, please open an issue or submit a pull request on the repository.
