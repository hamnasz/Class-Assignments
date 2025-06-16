#include <iostream>
#include <algorithm> // for std::reverse
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

    // Use the standard library function to reverse the array
    reverse(arr, arr + size);

    // Print the reversed array
    cout << "Reversed array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
