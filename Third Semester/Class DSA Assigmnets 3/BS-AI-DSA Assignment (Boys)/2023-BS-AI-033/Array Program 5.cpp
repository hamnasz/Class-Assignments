#include <iostream>
using namespace std;

int main() {
    int arr[10] = {1, 2, 2, 3, 4, 4, 5, 6, 6, 7}; // Example array with duplicates
    int n = 10; // Size of the array
    bool found[101] = {0}; // Assuming the values are between 0 and 100

    cout << "Unique elements: ";
    for (int i = 0; i < n; i++) {
        if (!found[arr[i]]) {
            cout << arr[i] << " ";
            found[arr[i]] = true;
        }
    }
    cout << endl;

    return 0;
}
