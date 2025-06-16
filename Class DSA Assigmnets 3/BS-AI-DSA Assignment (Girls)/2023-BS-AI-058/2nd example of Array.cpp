#include <iostream>
using namespace std;

int main() {
    int arr[5] = {9, 5, 2, 11, 3};
    int maxVal = arr[0];
    int minVal = arr[0];

    // Find max and min
    for (int i = 1; i < 5; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }

    // Output max and min
    cout << "Maximum: " << maxVal << endl;
    cout << "Minimum: " << minVal << endl;

    return 0;
}
