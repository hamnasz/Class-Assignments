#include <iostream>
#include <vector>
using namespace std;

int main() {
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> vectorOfRows;

    for (int row = 0; row < 3; row++) {
        vector<int> currentRow;
        for (int col = 0; col < 3; col++) {
            currentRow.push_back(matrix[row][col]);
        }
        vectorOfRows.push_back(currentRow);
    }

    cout << "2D Vector representation:" << endl;
    for (const auto& currentRow : vectorOfRows) {
        for (int element : currentRow) {
            cout << element << " ";
        }
        cout << endl;
    }

    return 0;
}
