// This program demonstrates how to find the smallest number in an array of integers
// by taking input from the user and using a `for` loop to compare the values.

#include <iostream>
using namespace std;

int main() {
    // Declare an array to hold 5 integers and a variable to store the smallest number
    int arr[5], smallest;

    // Prompt the user to enter 5 numbers
    cout << "Enter 5 numbers:" << endl;

    // Use a for loop to take input and store it in the array
    for (int i = 0; i < 5; i++) {
        cin >> arr[i];
    }

    // Assume the first element is the smallest
    smallest = arr[0];

    // Use a for loop to find the smallest number in the array
    for (int i = 1; i < 5; i++) {
        // If the current element is smaller than the smallest, update the smallest
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }

    // Output the smallest number
    cout << "The smallest number is: " << smallest << endl;

    return 0;
}
