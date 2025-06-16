// Write a program that reverses the elements of an array. 
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int length = 5;  // Define the length manually

    cout << "Original array: ";
    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Reversing the array
    for (int i = 0; i < length / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[length - i - 1];
        arr[length - i - 1] = temp;
    }

    cout << "Reversed array: ";
    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
