#include <iostream>
using namespace std;

int main() {
    int arr[5];
    int maxVal, minVal;

    cout << "Enter 5 integers: ";
    for (int i = 0; i < 5; i++) {
        cin >> arr[i];
    }

    maxVal = minVal = arr[0];

    for (int i = 1; i < 5; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }

    cout << "Maximum value: " << maxVal << endl;
    cout << "Minimum value: " << minVal << endl;

    return 0;
}
