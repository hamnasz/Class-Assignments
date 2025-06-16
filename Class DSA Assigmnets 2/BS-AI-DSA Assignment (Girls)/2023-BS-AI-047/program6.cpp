#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Declare a vector of integers
    vector<int> numbers;

    // Adding elements to the vector
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);
    numbers.push_back(50);

    // Output the elements of the vector
    cout << "Elements in the vector:\n";
    for (size_t i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " "; // Print each element
    }
    cout << endl;

    // Calculate and display the sum of the elements
    int sum = 0;
    for (int num : numbers) {
        sum += num; // Add each element to sum
    }
    cout << "Sum of elements: " << sum << endl;

    return 0; // End of the program
}
