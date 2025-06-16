#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 42, 12, 6, 23, 89, 21}; 
    int n = sizeof(arr) / sizeof(arr[0]); 

    int maxVal = arr[0];
    int minVal = arr[0];

    for (int i = 1; i < n; i++) {
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
