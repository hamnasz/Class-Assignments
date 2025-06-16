#include <iostream>

using namespace std;

int main() {
    // Initialize an array of integers
    int numbers[] = {15, 42, 7, 89, 23, 56, 12};
    int size = sizeof(numbers) / sizeof(numbers[0]); // Calculate the size of the array

    // Initialize max and min values
    int maxVal = numbers[0];
    int minVal = numbers[0];

    // Loop through the array to find max and min values
    for (int i = 1; i < size; ++i) {
        if (numbers[i] > maxVal) {
            maxVal = numbers[i];
        }
        if (numbers[i] < minVal) {
            minVal = numbers[i];
        }
    }

    // Output the results
    cout << "Maximum value: " << maxVal << endl;
    cout << "Minimum value: " << minVal << endl;

    return 0;
}
