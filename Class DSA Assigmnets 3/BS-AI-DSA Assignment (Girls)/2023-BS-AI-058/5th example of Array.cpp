#include <iostream>
using namespace std;

int main() {
    int arr[10] = {1, 2, 2, 3, 4, 5, 5, 6, 7, 7};
    int n = 10;

    // Remove duplicates
    cout << "Array after removing duplicates: ";
    for (int i = 0; i < n; i++) {
        bool isDuplicate = false;
        for (int j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            cout << arr[i] << " ";
        }
    }
    cout << endl;

    return 0;
}
