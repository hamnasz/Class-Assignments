#include <iostream>
using namespace std;

int main() {
    int size = 10;
    int arr[size] = {4, 6, 12, 64, 82, 4, 65, 42, 12, 10};
    int unique[size];
    int uniqueCount = 0;

    for (int i = 0; i < size; i++) {
        bool isDuplicate = false;
        for (int j = 0; j < uniqueCount; j++) {
            if (arr[i] == unique[j]) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            unique[uniqueCount] = arr[i];
            uniqueCount++;
        }
    }

    cout << "Unique elements: ";
    for (int i = 0; i < uniqueCount; i++) {
        cout << unique[i] << " ";
    }

    return 0;
}