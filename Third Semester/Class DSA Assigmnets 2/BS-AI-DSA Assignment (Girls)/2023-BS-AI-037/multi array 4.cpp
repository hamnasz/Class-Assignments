#include <iostream>
using namespace std;

int main() {
    int arr[3][4] = {
        {3, 5, 7, 2},
        {8, -1, 4, 10},
        {12, 6, 9, 0}
    };
    int rows = 3;
    int cols = 4;

  
    int row1 = 0, col1 = 2; 
    int row2 = 1, col2 = 3; 

    
    if (row1 >= 0 && row1 < rows && col1 >= 0 && col1 < cols &&
        row2 >= 0 && row2 < rows && col2 >= 0 && col2 < cols) {
        int sum = arr[row1][col1] + arr[row2][col2];
        cout << "The sum of elements at (" << row1 << "," << col1 << ") and ("
             << row2 << "," << col2 << ") is: " << sum << endl;
    } else {
        cout << "Invalid indices!" << endl;
    }

    return 0;
}