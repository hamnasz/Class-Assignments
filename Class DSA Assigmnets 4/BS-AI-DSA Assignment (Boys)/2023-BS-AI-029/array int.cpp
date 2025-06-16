#include <iostream>

using namespace std; // Use the standard namespace

int main() {
    // Initialize an array of integers
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]); // Calculate the size of the array

    // Print all the elements of the array
    cout << "Elements of the array:" << endl;
    for (int i = 0; i < size; ++i) {
        cout << numbers[i] << endl;
    }

    return 0;
}
