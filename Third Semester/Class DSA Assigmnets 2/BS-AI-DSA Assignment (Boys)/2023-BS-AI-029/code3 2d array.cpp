#include <iostream>
using namespace std;

int main() {
    const int rows = 3;
    const int cols = 3;
    int matrix[rows][cols];

    // Input elements into the 2D array
    cout << "Enter " << rows * cols << " numbers for a " << rows << "x" << cols << " matrix:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrix[i][j];
        }
    }

    // Print the 2D array elements
    cout << "You entered the matrix:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
