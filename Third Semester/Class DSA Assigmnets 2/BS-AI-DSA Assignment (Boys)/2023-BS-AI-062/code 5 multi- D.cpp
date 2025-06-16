#include <iostream>
using namespace std;
int main() {
    int arr[3][4] = {{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12}};
    long long product = 1; 
    int rows = 3;
    int cols = 4;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            product *= arr[i][j];
        }
    }
     cout << "Product of all elements: " << product <<endl;
    return 0;
}
