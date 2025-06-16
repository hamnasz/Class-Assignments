#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int n = 5, target, found = 0;

    cout << "Enter the number to search: ";
    cin >> target;

    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            cout << "Number " << target << " found at index " << i << endl;
            found = 1;
            break;
        }
    }

    if (!found) {
        cout << "Number " << target << " not found in the array." << endl;
    }

    return 0;
}
