#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec; // Create an empty vector of integers
    int element;
    char choice;

    do {
        cout << "Enter an element to add to the vector: ";
        cin >> element;
        vec.push_back(element); // Add the element to the vector

        // Display the size and capacity of the vector
        cout << "Current size: " << vec.size() << endl;
        cout << "Current capacity: " << vec.capacity() << endl;

        cout << "Do you want to add another element? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Final vector contents: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
