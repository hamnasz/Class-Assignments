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

    // Variables to hold the sum and total count of elements
    int sum = 0;
    int total_elements = 0;

    // Iterate through the 2D vector to calculate the sum and total elements
    for (const auto& row : arr) {
        for (int value : row) {
            sum += value;          
            total_elements++;        // Increment the total count of elements
        }
    }

    // Calculate the average
    double average = static_cast<double>(sum) / total_elements;

    cout << "The average value in the 2D vector is: " << average << endl;

    return 0;
}