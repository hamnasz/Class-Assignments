
#include <iostream>
using namespace std;

int main() {
    int arr[] = {12, 34, 9, 45, 23};
    int max = arr[0];  // Assume first element is the largest

    // Loop to find the maximum element
    for (int i = 1; i < 5; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    cout << "Largest element in the array: " << max << endl;

    return 0;
}
