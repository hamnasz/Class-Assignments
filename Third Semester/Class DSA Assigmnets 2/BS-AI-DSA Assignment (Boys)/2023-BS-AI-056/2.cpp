#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int element = 30, index = -1;

    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            index = i;
            break;
        }
    }

    if (index != -1)
        cout << "Index of " << element << ": " << index << endl;
    else
        cout << element << " not found in array." << endl;

    return 0;
}

