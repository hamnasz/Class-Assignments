#include <iostream>
#include <climits>

int main() {
    int arr[] = {3, 5, 2, 8, 6, 1, 4}; // Initialize the array
    int length = sizeof(arr) / sizeof(arr[0]); // Calculate the length of the array

    int max = INT_MIN; // Initialize max to the smallest integer value
    int min = INT_MAX; // Initialize min to the largest integer value

    for(int i = 0; i < length; i++) {
        if(arr[i] > max) {
            max = arr[i]; // Update max if the current element is larger
        }
        if(arr[i] < min) {
            min = arr[i]; // Update min if the current element is smaller
        }
    }

    std::cout << "Maximum value: " << max << std::endl;
    std::cout << "Minimum value: " << min << std::endl;

    return 0;
}
