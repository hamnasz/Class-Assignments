#include <iostream>
#include <limits>
using namespace std;
int main() {
    int arr[3][3] = {{3, 5, 1},{7, 2, 8},{4, 6, 9}};
    int min = numeric_limits<int>::max(); 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] < min) {
                min = arr[i][j]; 
            }
        }
    }
    cout << "Minimum: " << min <<endl; 
    return 0;
}
