#include <iostream>
#include <vector>
using namespace std;
int main() 
{
    vector<vector<int>> matrix = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
    cout << "2D Vector (Matrix):" <<endl;
    for (const auto& row : matrix) {
        for (int num : row) {
            cout << num << " "<<endl;
        }
    }
    return 0;
}