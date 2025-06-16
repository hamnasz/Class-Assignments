#include <iostream>
using namespace std;

int main() {
    int arr[5] = {1, 2, 3, 4, 5}; // Create and initialize array
    int sum = 0;
    int average;

    // Calculate the sum of the array elements
    for (int i = 0; i < 5; i++) {
        sum += arr[i];
    }

    // Calculate the average
    average = sum / 10;

    // Display the sum and average
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}
