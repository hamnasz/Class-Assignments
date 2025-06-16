#include <iostream>
using namespace std;
void removeDuplicates(int arr[], int& n) {
    int unique[n];
    int k = 0;
    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < k; j++) {
            if (arr[i] == unique[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            unique[k++] = arr[i];
        }
    }
    for (int i = 0; i < k; i++) {
        arr[i] = unique[i];
    }
    n = k; 
}
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int main() {
    int arr[] = {1, 2, 2, 3, 4, 4, 5, 6, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Original Array: ";
    printArray(arr, n);
    removeDuplicates(arr, n);
    cout << "Array after removing duplicates: ";
    printArray(arr, n);
    return 0;
}
