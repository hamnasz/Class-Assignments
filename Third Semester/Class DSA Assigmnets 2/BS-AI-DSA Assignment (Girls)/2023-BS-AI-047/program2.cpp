#include <iostream>
using namespace std;

int main() {
    // Declare and initialize a single-dimensional array
    int numbers[] = {12, 45, 23, 67, 34};
    int maxElement = numbers[0]; // Assume the first element is the maximum
    int length = sizeof(numbers) / sizeof(numbers[0]); // Calculate the number of elements

    // Loop through the array to find the maximum element
    for (int i = 1; i < length; i++) {
        if (numbers[i] > maxElement) {
            maxElement = numbers[i]; // Update maxElement if current element is greater
        }
    }

    // Output the result
    cout << "The maximum element in the array is: " << maxElement << endl;

    return 0; // End of the program
}
