#include <iostream>
using namespace std;

int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Create and initialize array
    int sum = 0;
    int average;

    // Calculate the sum of the array elements
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }

    // Calculate the average
    average = sum / 10;

    // Display the sum and average
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}
