#include <iostream>
#include <vector>
#include <algorithm> // For std::sort

using namespace std;

int main() {
    vector<int> vec; // Vector to hold integers
    int n, element;

    cout << "Enter the number of elements in the vector: ";
    cin >> n;

    // Input elements into the vector
    cout << "Enter " << n << " integers:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> element;
        vec.push_back(element);
    }

    // Sort the vector in ascending order
    sort(vec.begin(), vec.end());

    // Output the sorted vector
    cout << "Sorted vector in ascending order: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
