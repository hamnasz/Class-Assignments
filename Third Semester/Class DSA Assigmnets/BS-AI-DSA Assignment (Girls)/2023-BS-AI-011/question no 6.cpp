// This program generates and displays the multiplication table of a user-provided number
// by storing the results in an array and printing them using a loop.

#include <iostream>
using namespace std;

int main() {
    // Declare an array to hold the results of the multiplication table
    int table[10];

    // Declare a variable to store the user-provided number
    int number;

    // Ask the user to enter a number
    cout << "Enter a number to generate its multiplication table: ";
    cin >> number;

    // Use a for loop to calculate and store the table in the array
    for (int i = 0; i < 10; i++) {
        table[i] = number * (i + 1); // Store each result in the array
    }

    // Print the multiplication table
    cout << "Multiplication table of " << number << ":" << endl;
    for (int i = 0; i < 10; i++) {
        // Output the multiplication table in the format: number x i+1 = result
        cout << number << " x " << (i + 1) << " = " << table[i] << endl;
    }

    return 0;
}
