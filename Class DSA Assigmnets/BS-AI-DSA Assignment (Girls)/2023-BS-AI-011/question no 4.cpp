// This program demonstrates how to use the `sizeof` operator to calculate the total size of an array
// in bytes, as well as the size of each element in the array

#include <iostream>
using namespace std;

int main() {
    // Declare an array of 6 floating-point numbers
    float myNumbers[6] = {2.5, 3.1, 4.6, 7.8, 9.2, 5.3};

    // Output the total size of the array in bytes
    cout << "Total size of the array in bytes: " << sizeof(myNumbers) << " bytes" << endl;

    // Output the size of a single element in the array
    cout << "Size of a single element in the array: " << sizeof(myNumbers[0]) << " bytes" << endl;


    return 0;
}
