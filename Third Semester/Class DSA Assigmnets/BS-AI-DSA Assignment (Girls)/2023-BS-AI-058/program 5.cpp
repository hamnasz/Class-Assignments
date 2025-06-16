#include <iostream>
using namespace std;

int main() {
    int arr[] = {15, 25, 35, 45, 55};
    int size = sizeof(arr) / sizeof(arr[0]);
    int key, found = 0;

    cout << "Enter the element to search: ";
    cin >> key;

    // Loop to search for the element
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            cout << "Element found at index: " << i << endl;
            found = 1;
            break;
        }
    }

    if (!found) {
        cout << "Element not found in the array" << endl;
    }

    return 0;
}