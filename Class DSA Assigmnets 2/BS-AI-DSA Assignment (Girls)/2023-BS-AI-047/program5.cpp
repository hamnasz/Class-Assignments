#include <iostream>
using namespace std;

int main() {
    const int rows = 2; // Number of rows
    const int cols = 3; // Number of columns

    // Declare and initialize two 2D arrays (matrices)
    int matrixA[rows][cols] = {{1, 2, 3}, {4, 5, 6}};
    int matrixB[rows][cols] = {{7, 8, 9}, {10, 11, 12}};
    int result[rows][cols]; // Array to store the result

    // Loop through each element to add the matrices
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrixA[i][j] + matrixB[i][j]; // Add corresponding elements
        }
    }

    // Output the result matrix
    cout << "Result of matrix addition:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << result[i][j] << " "; // Print each element
        }
        cout << endl; // New line after each row
    }

    return 0; // End of the program
}
