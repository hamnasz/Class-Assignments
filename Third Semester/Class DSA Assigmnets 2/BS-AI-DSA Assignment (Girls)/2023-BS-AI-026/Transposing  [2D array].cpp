#include <iostream>
using namespace std;

int main() {
    int rows = 2, cols = 3;
    int array[2][3] = { {1, 2, 3}, {4, 5, 6} };

    cout << "Original Array:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nTransposed Array:" << endl;
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
