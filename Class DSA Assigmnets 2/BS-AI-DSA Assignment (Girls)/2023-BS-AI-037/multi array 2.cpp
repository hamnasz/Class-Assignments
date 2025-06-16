#include <iostream>
using namespace std;

int main() {
    int arr[3][4] = {
        {3, 5, 7, 2},
        {8, -1, 4, 10},
        {12, 6, 9, 0}
    };
    int rows = 3;
    int cols = 4;

    // Assume the first element is the minimum
    int min_val = arr[0][0];

    // Iterate through the 2D array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] < min_val) {
                min_val = arr[i][j]; // Update min_val if current element is smaller
            }
        }
    }

    cout << "The minimum value in the 2D array is: " << min_val << endl;

    return 0;
}