#include <iostream>
using namespace std;

int main() {
    int rows, cols;

    cout << "Enter number of Rows: ";
    cin >> rows;
    cout << "Enter number of Columns: ";
    cin >> cols;

    int matrix1[rows][cols], matrix2[rows][cols], sumMatrix[rows][cols];

    cout << "Enter First Matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Element [" << i << "][" << j << "]: ";
            cin >> matrix1[i][j];
        }
    }

    cout << "Enter Second Matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Element [" << i << "][" << j << "]: ";
            cin >> matrix2[i][j];
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sumMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    cout << "Sum:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << sumMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}