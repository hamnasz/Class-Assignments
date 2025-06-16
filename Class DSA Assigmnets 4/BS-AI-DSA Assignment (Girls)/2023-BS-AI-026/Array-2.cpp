#include <iostream>
using namespace std;

int main() {
    int size;

    // Ask the user for the size of the array
    cout << "Enter the number of elements in the array: ";
    cin >> size;

    // Declare the array with the given size
    int arr[size];

    // Input the elements of the array
    cout << "Enter " << size << " elements: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    // Assume the first element is both the max and min
    int maxVal = arr[0];
    int minVal = arr[0];

    // Loop through the array to find the max and min values
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }

    // Output the results
    cout << "Maximum value: " << maxVal << endl;
    cout << "Minimum value: " << minVal << endl;

    return 0;
}
