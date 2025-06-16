#include <iostream>
using namespace std;

int main() {
    // Initialize an array of integers
    int size = 5;
    int arr[size] = {1, 2, 3, 4, 5};

    // Print all elements of the array
    cout << "Array elements: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
