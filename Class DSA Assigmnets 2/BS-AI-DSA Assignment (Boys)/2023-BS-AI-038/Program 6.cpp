#include <iostream>
using namespace std;

int main() {
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int sumDiagonal = 0;

    for (int index = 0; index < 3; index++) {
        sumDiagonal += matrix[index][index];
    }

    cout << "The sum of the diagonal elements is: " << sumDiagonal << endl;
    return 0;
}
