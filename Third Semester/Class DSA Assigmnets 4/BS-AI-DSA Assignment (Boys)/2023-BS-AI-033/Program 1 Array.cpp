#include <iostream>

int main() {
    int arr[] = {1, 2, 3, 4, 5}; // initializing the array
    int length = sizeof(arr) / sizeof(arr[0]); // calculating the length of the array

    for(int i = 0; i < length; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
}
