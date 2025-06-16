#include <iostream>
using namespace std;

int main() {
    int arr[] = {3, 5, 7, 2, 8, -1, 4, 10, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    int index1 = 2; // First index (example: 7)
    int index2 = 4; // Second index (example: 8)

    // Check if indices are within bounds
    if (index1 >= 0 && index1 < n && index2 >= 0 && index2 < n) {
        int sum = arr[index1] + arr[index2];
        cout << "The sum of elements at indices " << index1 << " and " << index2 << " is: " << sum << endl;
    } else {
        cout << "Invalid indices!" << endl;
    }

    return 0;
}
