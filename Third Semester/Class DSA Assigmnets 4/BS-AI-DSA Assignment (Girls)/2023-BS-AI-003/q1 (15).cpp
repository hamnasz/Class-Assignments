#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;  // Declare a vector of integers
    int n, value;

    cout << "Enter the number of elements you want to add: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter element " << (i + 1) << ": ";
        cin >> value;
        vec.push_back(value); // Add the element to the vector

        // Display the size and capacity of the vector
        cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << endl;
    }

    return 0;
}
