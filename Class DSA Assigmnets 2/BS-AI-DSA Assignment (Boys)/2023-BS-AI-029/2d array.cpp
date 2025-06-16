#include <iostream>
using namespace std;

// Function to calculate the sum of the 2D array elements
int sumMatrix(int arr[][3], int rows, int cols) {
    int sum = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum += arr[i][j];
        }
    }
    return sum;
}

int main() {
    const int rows = 3;
    const int cols = 3;
    int matrix[rows][cols] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Calculate the sum
    int total = sumMatrix(matrix, rows, cols);

    // Print the result
    cout << "Sum of matrix elements: " << total << endl;

    return 0;
}