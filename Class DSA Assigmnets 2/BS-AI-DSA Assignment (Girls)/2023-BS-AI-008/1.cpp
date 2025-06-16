#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int total_sum = 0;
    int size = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < size; i++) {
        total_sum += arr[i];
    }

    cout << "Sum of the array: " << total_sum << endl;
    return 0;
}

