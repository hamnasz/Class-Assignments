#include <iostream>
using namespace std;

int main() {
    int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8}; // Example array
    int n = 8; // Size of the array

    // Reverse the array
    for (int i = 0; i < n / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }

    // Display the reversed array
    cout << "Reversed array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
