#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;
    
    int arr[n];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Remove duplicates and store unique elements
    int unique[n];
    int uniqueCount = 0;

    for (int i = 0; i < n; i++) {
        bool isDuplicate = false;

        // Check if arr[i] is already in the unique array
        for (int j = 0; j < uniqueCount; j++) {
            if (arr[i] == unique[j]) {
                isDuplicate = true;
                break;
            }
        }

        // If it's not a duplicate, add it to the unique array
        if (!isDuplicate) {
            unique[uniqueCount] = arr[i];
            uniqueCount++;
        }
    }

    
    cout << "Array with unique elements: ";
    for (int i = 0; i < uniqueCount; i++) {
        cout << unique[i] << " ";
    }
    cout << endl;

    return 0;
}
