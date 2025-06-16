#include <iostream>
using namespace std;

int main() {
    int arr[] = {23, 1, 56, 3, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int max_element = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] > max_element) {
            max_element = arr[i];
        }
    }

    cout << "Maximum element: " << max_element << endl;
    return 0;
}

