#include <iostream>

using namespace std;

int main() {
    int arr[] = {90, 2, 30, 4, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Reversing the array
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        swap(arr[i], arr[j]);
    }

    cout << "Reversed array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}