#include <iostream>
using namespace std;

int main() {
    const int size = 5;
    int numbers[size];

    // Input elements into the array
    cout << "Enter " << size << " numbers: ";
    for (int i = 0; i < size; ++i) {
        cin >> numbers[i];
    }

    // Print the array elements
    cout << "You entered: ";
    for (int i = 0; i < size; ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}