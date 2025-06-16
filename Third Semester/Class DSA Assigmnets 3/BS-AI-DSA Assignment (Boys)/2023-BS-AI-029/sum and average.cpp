#include <iostream>
using namespace std;

int main() {
    // Create an array of 10 integers
    int array[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    // Variable to hold the sum
    int total_sum = 0;

    // Calculate the sum of the array elements
    for (int i = 0; i < 10; i++) {
        total_sum += array[i];
    }

    // Calculate the average of the array elements
    double average = static_cast<double>(total_sum) / 10;

    // Display the results
    cout << "Array elements: ";
    for (int i = 0; i < 10; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    
    cout << "Sum of elements: " << total_sum << endl;
    cout << "Average of elements: " << average << endl;

    return 0;
}

