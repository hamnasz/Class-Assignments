#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    int arr[8] = {1, 2, 2, 3, 4, 4, 5, 5};
    unordered_set<int> uniqueValues;

    cout << "Original array with duplicates: ";
    for (int i = 0; i < 8; i++) {
        cout << arr[i] << " ";
        uniqueValues.insert(arr[i]);
    }

    cout << endl;

    cout << "Array with unique values: ";
    for (int num : uniqueValues) {
        cout << num << " ";
    }

    return 0;
}
