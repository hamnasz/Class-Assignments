#include <iostream>
#include <vector>
using namespace std;

void removeDuplicates(vector<int>& vec) {
    vector<int> uniqueVec; // Vector to store unique elements

    for (int value : vec) {
        // Check if the value is already in uniqueVec
        bool isDuplicate = false;
        for (int uniqueValue : uniqueVec) {
            if (value == uniqueValue) {
                isDuplicate = true;
                break;
            }
        }
        // If not a duplicate, add it to the uniqueVec
        if (!isDuplicate) {
            uniqueVec.push_back(value);
        }
    }

    // Clear the original vector and copy the unique elements back
    vec.clear();
    for (int uniqueValue : uniqueVec) {
        vec.push_back(uniqueValue);
    }
}

int main() {
    vector<int> vec;
    int n, value;

    cout << "Enter the number of elements in the vector: ";
    cin >> n;

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        vec.push_back(value);
    }

    removeDuplicates(vec);

    cout << "Vector after removing duplicates: ";
    for (const int& elem : vec) {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}
