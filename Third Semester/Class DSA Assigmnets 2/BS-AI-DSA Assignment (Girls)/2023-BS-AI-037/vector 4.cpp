#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Define a 2D vector
    vector<vector<int>> arr = {
        {3, 5, 7, 2},
        {8, -1, 4, 10},
        {12, 6, 9, 0}
    };

    // Variable to hold the sum of all elements
    int sum = 0;

    // Iterate through the 2D vector to calculate the sum
    for (const auto& row : arr) {
        for (int value : row) {
            sum += value; // Add the current element to the sum
        }
    }

    cout << "The sum of all elements in the 2D vector is: " << sum << endl;

    return 0;
}