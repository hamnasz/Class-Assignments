#include <iostream>
#include <vector>
#include <algorithm>  // For std::sort
using namespace std;

int main() {
    vector<int> vec;  // Vector to hold integers
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

    // Sort the vector in ascending order
    sort(vec.begin(), vec.end());

    // Display the sorted vector
    cout << "Sorted vector in ascending order: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
