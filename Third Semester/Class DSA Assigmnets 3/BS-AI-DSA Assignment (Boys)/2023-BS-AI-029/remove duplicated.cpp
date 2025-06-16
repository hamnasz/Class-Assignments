#include <iostream>
#include <set>
using namespace std;

int main() {
    // Create an array of integers
    int array[10];
    
    // Input values for the array
    cout << "Enter 10 integers: ";
    for (int i = 0; i < 10; i++) {
        cin >> array[i];
    }

    // Use a set to store unique values
    set<int> uniqueValues;

    // Insert elements into the set (duplicates are automatically removed)
    for (int i = 0; i < 10; i++) {
        uniqueValues.insert(array[i]);
    }

    // Display the unique values
    cout << "Unique values: ";
    for (const int &value : uniqueValues) {
        cout << value << " ";
    }
    cout << endl;

    return 0;
}

