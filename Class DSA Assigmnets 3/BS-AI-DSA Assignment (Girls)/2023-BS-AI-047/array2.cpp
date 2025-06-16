#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 5, 30, 25};
    int maxElement = arr[0];
    int size = sizeof(arr) / sizeof(arr[0]);

    for (int i = 1; i < size; i++) {
        if (arr[i] > maxElement) {
            maxElement = arr[i];
        }
    }

    cout << "Maximum element: " << maxElement << endl;
    return 0;
}
