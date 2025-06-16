#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Function to remove duplicates from a vector
vector<int> removeDuplicates(const vector<int>& vec) {
    set<int> uniqueElements; // Set to store unique elements
    vector<int> result;      // Vector to store the result

    for (int value : vec) {
        // Insert value into the set (duplicates will be ignored)
        auto resultPair = uniqueElements.insert(value);
        if (resultPair.second) { // If insertion was successful (value was unique)
            result.push_back(value); // Add to the result vector
        }
    }

    return result; // Return the vector with duplicates removed
}

int main() {
    vector<int> vec = {1, 2, 3, 2, 4, 3, 5, 1, 6}; // Example vector with duplicates

    cout << "Original vector: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;

    vector<int> uniqueVec = removeDuplicates(vec); // Remove duplicates

    cout << "Vector after removing duplicates: ";
    for (int val : uniqueVec) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
