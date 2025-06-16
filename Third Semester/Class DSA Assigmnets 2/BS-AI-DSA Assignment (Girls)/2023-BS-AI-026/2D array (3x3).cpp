#include <iostream>
using namespace std;

int main() {
    // 2D array (3x3)
    int array[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    cout << "Element at [0][1]: " << array[0][1] << endl;  // Output: 2
    cout << "Element at [2][2]: " << array[2][2] << endl;  // Output: 9
    
    cout << "2D Array:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

}
