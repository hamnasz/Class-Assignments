#include <iostream>
using namespace std;

int main() {
    int n;

    // Ask the user to input the number of elements in the array
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    int arr[n];

    // Taking input from the user
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Initialize max and min with the first element of the array
    int maxElement = arr[0];
    int minElement = arr[0];

    // Loop through the array to find the max and min
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxElement) {
            maxElement = arr[i];
        }
        if (arr[i] < minElement) {
            minElement = arr[i];
        }
    }

    // Display the results
    cout << "Maximum element in the array: " << maxElement << endl;
    cout << "Minimum element in the array: " << minElement << endl;

    return 0;
}
