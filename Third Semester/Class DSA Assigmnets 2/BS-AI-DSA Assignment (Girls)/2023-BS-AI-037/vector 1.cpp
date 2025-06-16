#include <iostream>
#include <vector>
#include <algorithm> // For std::max_element
using namespace std;

int main() {
    // Define a 2D vector
    vector<vector<int>> arr = {
        {3, 5, 7, 2},
        {8, -1, 4, 10},
        {12, 6, 9, 0}
    };

    
    int max_val = arr[0][0];

   
    for (const auto& row : arr) {
       
        int row_max = *max_element(row.begin(), row.end());
        
        if (row_max > max_val) {
            max_val = row_max;
        }
    }

    cout << "The maximum value in the 2D vector is: " << max_val << endl;

    return 0;
}
