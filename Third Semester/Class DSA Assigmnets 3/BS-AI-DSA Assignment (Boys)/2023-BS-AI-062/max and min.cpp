#include <iostream>
using namespace std;

int main() {
    int arr[5] = {12, 45, 7, 68, 2}; 
    int maxVal = arr[0];
    int minVal = arr[0];

    for (int i = 1; i < 5; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }

    cout << "Maximum value: " << maxVal << "\n";
    cout << "Minimum value: " << minVal << "\n";

    return 0;
}
