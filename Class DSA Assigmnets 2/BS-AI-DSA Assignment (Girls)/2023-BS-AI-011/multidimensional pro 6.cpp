//Finding Maximum Element in a 2D Array

#include <iostream>
using namespace std;

int main() {
    int arr[3][3] = {{5, 9, 1}, {4, 7, 3}, {8, 2, 6}};
    int maxElement = arr[0][0];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] > maxElement) {
                maxElement = arr[i][j]; // Find maximum element
            }
        }
    }

    cout << "Maximum element in 2D array: " << maxElement << endl;
    return 0;
}
