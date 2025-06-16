#include <iostream>
using namespace std;

int main() {
    const int SIZE = 10; // Size of the array
    int numbers[SIZE];   // Array to hold integers
    int sum = 0;        // Variable to hold the sum of the elements
    double average;     // Variable to hold the average of the elements

    // Input: Getting 10 integers from the user
    cout << "Enter " << SIZE << " integers:\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "Element " << (i + 1) << ": ";
        cin >> numbers[i];
    }

    // Calculate sum of the elements
    for (int i = 0; i < SIZE; i++) {
        sum += numbers[i];
    }

    // Calculate average
    average = static_cast<double>(sum) / SIZE;

    // Output: Displaying the sum and average
    cout << "\nSum of the array elements: " << sum << endl;
    cout << "Average of the array elements: " << average << endl;

    return 0;
}