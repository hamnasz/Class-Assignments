#include <iostream>
using namespace std;

int main() {
    // Declare and initialize a single-dimensional array
    int numbers[] = {1, 2, 3, 4, 5};
    int length = sizeof(numbers) / sizeof(numbers[0]); // Calculate the number of elements

    // Loop to reverse the array
    for (int i = 0; i < length / 2; i++) {
        // Swap elements
        int temp = numbers[i];
        numbers[i] = numbers[length - 1 - i];
        numbers[length - 1 - i] = temp;
    }

    // Output the reversed array
    cout << "Reversed array: ";
    for (int i = 0; i < length; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0; // End of the program
}
