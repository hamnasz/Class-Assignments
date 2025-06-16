#include <iostream>
using namespace std;

int main() {
    int arr[4];

    cout << "Enter 4 integers: ";
    for (int i = 0; i < 4; i++) {
        cin >> arr[i];
    }

    cout << "Original Array: ";
    for (int i = 0; i < 4; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Reversed Array: ";
    for (int i = 3; i >= 0; i--) {
        cout << arr[i] << " ";
    }
    cout << endl;
}