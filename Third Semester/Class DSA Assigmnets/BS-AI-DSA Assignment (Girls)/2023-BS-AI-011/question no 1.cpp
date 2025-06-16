// This program demonstrates how to use an array of strings to store names of fruits
// and access individual elements from the array.
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Declare an array of strings 
    string fruits[5] = {"Apple", "Banana", "Cherry", "Date", "Elderberry"};

   // print the second fruit in the array (index 1 since arrays are zero-indexed)
    cout << "The second fruit in the list is: " << fruits[1] << endl;

    // print the last fruit in the array
    cout << "The last fruit in the list is: " << fruits[4] << endl;

    return 0;
}
