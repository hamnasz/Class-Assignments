#include <iostream>
using namespace std;
int main() {
    int arr[3][4] = {{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12}};
    int rows = 3;
    int cols = 4;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swap(arr[i][j], arr[i][cols - 1 - j]);
        }
    } 
    cout << "Reversed Array:" <<endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout <<endl;
    }
    return 0;
}
