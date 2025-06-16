#include <iostream>
using namespace std;

int main() {
    int arr[] = {3, 5, 7, 2, 8, -1, 4, 10, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    int maxVal = arr[0]; 

    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    cout << "The maximum value in the array is: " << maxVal << endl;
    return 0;
}