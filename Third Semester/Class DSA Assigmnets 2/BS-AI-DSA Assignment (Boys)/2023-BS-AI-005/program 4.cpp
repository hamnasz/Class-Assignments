#include <iostream>
#include <vector> // Include the vector header
using namespace std;
int main() {
    // Create a vector to store integers
    vector<int> numbers;
    // Add elements to the vector
    numbers.push_back(10); // Add 10
    numbers.push_back(20); // Add 20
    numbers.push_back(30); // Add 30
    // Display the elements of the vector
    cout << "Vector elements: ";
    for (int i = 0; i < numbers.size(); i++) { // Use size() to get the number of elements
        cout << numbers[i] << " "; // Access elements using the index
    }
    cout << endl;
    // Remove the last element
    numbers.pop_back(); // Removes 30
    // Display the updated vector
    cout << "After pop_back, elements: ";
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " "; // Print updated vector
    }
    cout << endl;
    return 0;
}
