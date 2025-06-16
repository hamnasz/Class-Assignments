#include <iostream>
using namespace std;

int main() {
    const int SIZE = 5;
    int arr[SIZE];
    int unique[SIZE];
    int uniqueCount = 0;

    cout << "Enter " << SIZE << " integers: ";
    for (int i = 0; i < SIZE; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < SIZE; i++) {
        bool isUnique = true;
        for (int j = 0; j < uniqueCount; j++) {
            if (arr[i] == unique[j]) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            unique[uniqueCount++] = arr[i];
        }
    }
    
    cout << "Unique Values: ";
    for (int i = 0; i < uniqueCount; i++) {
        cout << unique[i] << " ";
    }
    cout << endl;
}