#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 2, 5, 2};
    int size = sizeof(arr) / sizeof(arr[0]);
    int element = 2, count = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            count++;
        }
    }

    cout << "Number of times " << element << " appears: " << count << endl;
    return 0;
}

