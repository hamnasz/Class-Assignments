// Adding Matrices Using Two Dimensional Array
#include <iostream>
using namespace std;

int main() 
{
    int rows, cols;

    // Input Dimensions of Both Matrices
    cout << "Enter the number of Rows: ";
    cin >> rows;
    cout << "Enter the number of Columns: ";
    cin >> cols;

    // Declaring Two Matrices and a Result Matrix
    int matrix1[rows][cols], matrix2[rows][cols], sumMatrix[rows][cols];

    // Input Elements of First Matrix
    cout << "Enter Elements of the First Matrix:" << endl;
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            cout << "Element [" << i << "][" << j << "]: ";
            cin >> matrix1[i][j];
        }
    }

    // Input Elements of Second Matrix
    cout << "Enter Elements of the Second Matrix:" << endl;
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            cout << "Element [" << i << "][" << j << "]: ";
            cin >> matrix2[i][j];
        }
    }

    // Adding Both Matrices
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            sumMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    // Displaying the Sum of Matrices
    cout << "Sum of the two matrices is:" << endl;
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            cout << sumMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}