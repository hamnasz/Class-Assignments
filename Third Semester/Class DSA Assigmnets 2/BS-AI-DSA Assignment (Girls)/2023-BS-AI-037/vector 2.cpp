#include <iostream>
#include <vector>
#include <algorithm> // For std::min_element
using namespace std;

int main() {
    // Define a 2D vector
    vector<vector<int>> arr = {
        {3, 5, 7, 2},
        {8, -1, 4, 10},
        {12, 6, 9, 0}
    };

    
    int min_val = arr[0][0];

    
    for (const auto& row : arr) {
        
        int row_min = *min_element(row.begin(), row.end());
       
        if (row_min < min_val) {
            min_val = row_min;
        }
    }

    cout << "The minimum value in the 2D vector is: " << min_val << endl;

    return 0;
}