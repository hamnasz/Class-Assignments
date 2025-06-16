#include <iostream>
#include <vector>
using namespace std;

int main() {
    int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> vec;

    for (int i = 0; i < 3; i++) {
        vector<int> row;
        for (int j = 0; j < 3; j++) {
            row.push_back(arr[i][j]);
        }
        vec.push_back(row);
    }

    cout << "Vector of 1D arrays:" << endl;
    for (const auto& row : vec) {
        for (int elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }

    return 0;
}
