#include <iostream>
using namespace std;
int main() {
    int arr[3][3] = {
        {3, 5, 1},
        {7, 2, 8},
        {4, 6, 9}
    };
    int max = arr[0][0];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] > max) {
                max = arr[i][j];
            }
        }
    }
    cout << "Maximum: " << max <<endl;
    return 0;
}
