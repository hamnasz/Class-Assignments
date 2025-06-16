#include <iostream>
using namespace std;

int main() {
    int arr[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for (int i = 0; i < 3; i++) {
        int col_sum = 0;
        for (int j = 0; j < 3; j++) {
            col_sum += arr[j][i];
        }
        cout << "Sum of column " << i + 1 << ": " << col_sum << endl;
    }

    return 0;
}

