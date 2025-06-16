#include <iostream>
using namespace std;

int main() {
    // Declare and initialize a single-dimensional array
    int numbers[] = {4, 2, 4, 3, 4, 5, 1};
    int length = sizeof(numbers) / sizeof(numbers[0]); // Calculate the number of elements
    int target = 4; // Element to count
    int count = 0; // Variable to store the count of occurrences

    // Loop through the array to count occurrences of the target element
    for (int i = 0; i < length; i++) {
        if (numbers[i] == target) {
            count++; // Increment count if the current element matches the target
        }
    }

    // Output the result
    cout << "The element " << target << " occurs " << count << " times in the array." << endl;

    return 0; // End of the program
}
