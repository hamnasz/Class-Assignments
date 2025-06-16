#include <iostream>
using namespace std;

int main() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int mergedSize = size1 + size2;
    int merged[mergedSize];

    // Copy elements of arr1 to merged array
    for (int i = 0; i < size1; i++) {
        merged[i] = arr1[i];
    }

    // Copy elements of arr2 to merged array
    for (int i = 0; i < size2; i++) {
        merged[size1 + i] = arr2[i];
    }

    cout << "Merged array: ";
    for (int i = 0; i < mergedSize; i++) {
        cout << merged[i] << " ";
    }
    cout << endl;

    return 0;
}
