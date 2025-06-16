#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Function to remove duplicates from a vector
vector<int> removeDuplicates(const vector<int>& vec) {
    unordered_set<int> seen;  // Set to track seen elements
    vector<int> uniqueVec;     // Vector to hold unique elements

    for (int num : vec) {
        // If the number has not been seen before, add it to the unique vector
        if (seen.find(num) == seen.end()) {
            seen.insert(num);   // Mark this number as seen
            uniqueVec.push_back(num);  // Add to unique vector
        }
    }

    return uniqueVec;  // Return the vector containing unique elements
}

int main() {
    vector<int> vec;
    int n, element;

    // Input the number of elements in the vector
    cout << "Enter the number of elements in the vector: ";
    cin >> n;

    // Read elements into the vector
    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> element;
        vec.push_back(element);
    }

    // Remove duplicates
    vector<int> uniqueVec = removeDuplicates(vec);

    // Display the unique elements
    cout << "Vector after removing duplicates: ";
    for (int num : uniqueVec) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
