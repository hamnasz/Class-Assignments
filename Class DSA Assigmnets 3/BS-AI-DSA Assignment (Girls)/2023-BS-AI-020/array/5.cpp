#include <iostream>
using namespace std;

int main() {
    int arr[10];
    int unique[10]; // Array to store unique values
    int uniqueCount = 0; // Counter for unique values

    cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; i++) {
        cin >> arr[i];
    }

    // Find unique values
    for (int i = 0; i < 10; i++) {
        bool isDuplicate = false;
        
        // Check if arr[i] is already in the unique array
        for (int j = 0; j < uniqueCount; j++) {
            if (arr[i] == unique[j]) {
                isDuplicate = true;
                break;
            }
        }
        
        // If not a duplicate, add to the unique array
        if (!isDuplicate) {
            unique[uniqueCount] = arr[i];
            uniqueCount++;
        }
    }

    // Display unique values
    cout << "Unique values: ";
    for (int i = 0; i < uniqueCount; i++) {
        cout << unique[i] << " ";
    }
    cout << endl;

    return 0;
}
