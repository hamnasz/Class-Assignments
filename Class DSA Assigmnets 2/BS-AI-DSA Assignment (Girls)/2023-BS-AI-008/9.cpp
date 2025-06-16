#include <iostream>
using namespace std;

int main() {
    int arr[3][3] = {
        {23, 12, 9},
        {4, 56, 7},
        {3, 22, 5}
    };

    int max_element = arr[0][0];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] > max_element) {
                max_element = arr[i][j];
            }
        }
    }

    cout << "Maximum element: " << max_element << endl;
    return 0;
}

