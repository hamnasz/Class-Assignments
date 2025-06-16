#include <iostream>
using namespace std;

int main() {
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int largest = matrix[0][0];

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (matrix[row][col] > largest) {
                largest = matrix[row][col];
            }
        }
    }

    cout << "The largest element in the matrix is: " << largest << endl;
    return 0;
}
