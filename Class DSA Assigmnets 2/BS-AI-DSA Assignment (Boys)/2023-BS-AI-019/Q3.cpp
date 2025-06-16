// Multiplying Matrices Using Two Dimensional Array
#include <iostream>
using namespace std;

int main() 
{
    int rows1, cols1, rows2, cols2;

    // Input dimensions of First Matrix
    cout << "Enter number of rows for the first matrix: ";
    cin >> rows1;
    cout << "Enter number of columns for the first matrix: ";
    cin >> cols1;

    // Input dimensions of the Second Matrix
    cout << "Enter number of rows for the second matrix: ";
    cin >> rows2;
    cout << "Enter number of columns for the second matrix: ";
    cin >> cols2;

    // Check if Matrices can be Multiplied or Not!
    if (cols1 != rows2) 
    {
        cout << "Matrices cannot be multiplied!" << endl;
        return 0;
    }

    int matrix1[rows1][cols1], matrix2[rows1][cols1], resultMatrix[10][10] = {0};

    // Input Elements of First Matrix
    cout << "Enter elements of the first matrix:" << endl;
    for (int i = 0; i < rows1; i++) 
    {
        for (int j = 0; j < cols1; j++) 
        {
            cout << "Element [" << i << "][" << j << "]: ";
            cin >> matrix1[i][j];
        }
    }

    // Input Elements of Second Matrix
    cout << "Enter elements of the second matrix:" << endl;
    for (int i = 0; i < rows2; i++) 
    {
        for (int j = 0; j < cols2; j++) 
        {
            cout << "Element [" << i << "][" << j << "]: ";
            cin >> matrix2[i][j];
        }
    }

    // Multiplying the Matrices
    for (int i = 0; i < rows1; i++) 
    {
        for (int j = 0; j < cols2; j++) 
        {
            for (int k = 0; k < cols1; k++) 
            {
                resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    // Displaying the Result Matrix
    cout << "Resultant Matrix after multiplication is:" << endl;
    for (int i = 0; i < rows1; i++) 
    {
        for (int j = 0; j < cols2; j++) 
        {
            cout << resultMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}