#include <iostream>

int main() {
    int arr[] = {1, 2, 3, 4, 5}; // Initialize the array
    int length = sizeof(arr) / sizeof(arr[0]); // Calculate the length of the array

    // Reverse the array
    for(int i = 0; i < length / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[length - 1 - i];
        arr[length - 1 - i] = temp;
    }

    // Print the reversed array
    for(int i = 0; i < length; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
}
