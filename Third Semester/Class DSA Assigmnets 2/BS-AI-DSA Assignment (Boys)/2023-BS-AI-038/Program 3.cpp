#include <iostream>
using namespace std;

int main() {
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int transposed[3][3];

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            transposed[col][row] = matrix[row][col];
        }
    }

    cout << "The transposed matrix is: " << endl;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            cout << transposed[row][col] << " ";
        }
        cout << endl;
    }

    return 0;
}
