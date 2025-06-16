#include <iostream>
using namespace std;

int main() {
    int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int diagonalSum = 0;

    for (int i = 0; i < 3; i++) {
        diagonalSum += arr[i][i]; 
    }

    cout << "Sum of diagonal elements: " << diagonalSum << endl;
    return 0;
}
