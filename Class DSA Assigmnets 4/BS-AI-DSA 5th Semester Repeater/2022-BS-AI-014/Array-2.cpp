#include <iostream>
#include <limits.h>
using namespace std;

int main() {
    int arr[] = {1, 7, 3, 9, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int maxVal = INT_MIN, minVal = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
        if (arr[i] < minVal) minVal = arr[i];
    }

    cout << "Maximum: " << maxVal << ", Minimum: " << minVal << endl;

    return 0;
}
