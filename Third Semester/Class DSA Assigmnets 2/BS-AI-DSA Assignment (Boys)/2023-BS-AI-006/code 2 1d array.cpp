#include <iostream>
using namespace std;

// Function to calculate the sum of the array elements
int sumArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    const int size = 5;
    int numbers[size] = {1, 2, 3, 4, 5};

    // Calculate the sum
    int total = sumArray(numbers, size);

    // Print the result
    cout << "Sum of array elements: " << total << endl;

    return 0;
}