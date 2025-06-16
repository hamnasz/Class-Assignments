#include <iostream>
using namespace std;

int main() {
    
    int arr[] = {12, 45, 2, 8, 23, 56, 1, 9};
    int size = sizeof(arr) / sizeof(arr[0]);  
    
    int maxVal = arr[0];
    int minVal = arr[0];

    
    for (int i = 1; i < size; ++i) {
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
