#include <iostream>
using namespace std;

int main() {
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    for (int row = 0; row < 3; row++) {
        int sumRow = 0;
        for (int col = 0; col < 3; col++) {
            sumRow += matrix[row][col];
        }
        cout << "The sum of elements in row " << row + 1 << ": " << sumRow << endl;
    }

    return 0;
}
