// This program demonstrates how to use a `for` loop to iterate through an array of integers
// and print each element along with its index.

#include <iostream>
using namespace std;

int main() {
    // Declare an array of integers 
    int numbers[6] = {5, 10, 15, 20, 25, 30};

    // Use a for loop to go through each element in the array
    for (int i = 0; i < 6; i++) {
        // Print the index and the corresponding element in the array
        cout << "Index " << i << " = " << numbers[i] << endl;
    }

    return 0;
}
