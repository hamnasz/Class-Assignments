#include <iostream>
using namespace std;
int main() {
    // Declare and initialize a 2x3 array (2 rows, 3 columns)
    int matrix[2][3] = {
        {1, 2, 3}, // First row
        {4, 5, 6}  // Second row
    };
    // Print the 2D array
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";  // Access elements using row and column indices
        }
        cout << endl;  // Newline after each row
    }
    return 0;
}
