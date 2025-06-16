#include <iostream>
using namespace std;

int main() {
    int arr[] = {34, 15, 88, 2, 43, 11, 77};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int max = arr[0];
    int min = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    cout << "Maximum value: " << max << endl;
    cout << "Minimum value: " << min << endl;

    return 0;
}