#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Define a 2D vector
    vector<vector<int>> arr = {
        {3, 5, 7, 2},
        {8, 1, 4, 10},
        {12, 6, 9, 0}
    };

    // Variable to hold the product of all elements
    long long product = 1; // Use long long to prevent overflow

    // Iterate through the 2D vector to calculate the product
    for (const auto& row : arr) {
        for (int value : row) {
            product *= value; // Multiply the current element to the product
        }
    }

    cout << "The product of all elements in the 2D vector is: " << product << endl;

    return 0;
}