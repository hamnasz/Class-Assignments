#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 2, 2, 5};
    int element = 2;
    int count = 0;
    int size = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            count++;
        }
    }

    cout << "Element " << element << " occurs " << count << " times." << endl;
    return 0;
}
