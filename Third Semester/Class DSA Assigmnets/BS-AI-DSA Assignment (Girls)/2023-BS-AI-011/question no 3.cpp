// This program demonstrates how to manually assign values to an array of strings
// and print each value using a `for` loop.

#include <iostream>
#include <string>
using namespace std;

int main() {
    // Declare an array of strings to hold 4 names of animals
    string animals[4];

    // Manually assign values to each index of the array
    animals[0] = "Lion";
    animals[1] = "Tiger";
    animals[2] = "Elephant";
    animals[3] = "Giraffe";

    // Use a for loop to print each animal name in the array
    for (int i = 0; i < 4; i++) {
        // Output the value at each index
        cout << "Animal at index " << i << ": " << animals[i] << endl;
    }

    return 0;
}
