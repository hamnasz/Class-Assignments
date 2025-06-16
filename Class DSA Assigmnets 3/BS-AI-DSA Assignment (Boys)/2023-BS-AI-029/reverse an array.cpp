#include <iostream>
using namespace std;

int main() {
    // Create an array of 8 integers
    int array[8];

    // Input values for the array
    cout << "Enter 8 integers: ";
    for (int i = 0; i < 8; i++) {
        cin >> array[i];
    }

    // Reverse the array
    for (int i = 0; i < 4; i++) { // Only need to swap half
        int temp = array[i];
        array[i] = array[7 - i];
        array[7 - i] = temp;
    }

    // Display the reversed array
    cout << "Reversed array: ";
    for (int i = 0; i < 8; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    return 0;
}

