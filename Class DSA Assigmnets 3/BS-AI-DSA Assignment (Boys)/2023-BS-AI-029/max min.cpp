#include <iostream>
using namespace std;

int main() {
    // Create an array of 5 integers
    int array[5];

    // Input values for the array
    cout << "Enter 5 integers: ";
    for (int i = 0; i < 5; i++) {
        cin >> array[i];
    }

    // Initialize max and min with the first element
    int max_value = array[0];
    int min_value = array[0];

    // Find the maximum and minimum values
    for (int i = 1; i < 5; i++) {
        if (array[i] > max_value) {
            max_value = array[i];
        }
        if (array[i] < min_value) {
            min_value = array[i];
        }
    }

    // Display the results
    cout << "Maximum value: " << max_value << endl;
    cout << "Minimum value: " << min_value << endl;

    return 0;
}
