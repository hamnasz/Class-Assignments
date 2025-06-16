//Single dimensional array
#include <iostream>
using namespace std;

int main() {
    // Declare and initialize a single-dimensional array
    int numbers[] = {10, 20, 30, 40, 50};
    int sum = 0; // Variable to store the sum of array elements
    int length = sizeof(numbers) / sizeof(numbers[0]); // Calculate the number of elements

    // Loop through the array to calculate the sum
    for (int i = 0; i < length; i++) {
        sum += numbers[i]; // Add each element to the sum
    }

    // Output the result
    cout << "The sum of the array elements is: " << sum << endl;

    return 0; // End of the program
}
