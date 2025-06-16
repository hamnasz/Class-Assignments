#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;  // Create a vector to hold integers
    int element;
    char choice;

    do {
        cout << "Enter an element to add to the vector: ";
        cin >> element;  // Read element from user
        vec.push_back(element);  // Add element to the vector

        // Display the current size and capacity of the vector
        cout << "Current size of the vector: " << vec.size() << endl;
        cout << "Current capacity of the vector: " << vec.capacity() << endl;

        // Ask if the user wants to add another element
        cout << "Do you want to add another element? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');  // Continue if user inputs 'y' or 'Y'

    cout << "Final size of the vector: " << vec.size() << endl;
    cout << "Final capacity of the vector: " << vec.capacity() << endl;

    return 0;
}