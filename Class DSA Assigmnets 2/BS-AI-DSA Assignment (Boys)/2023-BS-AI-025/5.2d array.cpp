#include <iostream>
using namespace std;
void addFiveAfterIndex(int arr[], int size, int index) {
    for (int i = index + 1; i < size; i++) {
        arr[i] += 5;
    }
}
int main() {
    int size, index;
    cout << "Enter the size of the array: ";
    cin >> size;
    int arr[size];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    cout << "Enter the index after which to add 5: ";
    cin >> index;
    addFiveAfterIndex(arr, size, index);
    cout << "Modified array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}