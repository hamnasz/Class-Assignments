#include <iostream>
using namespace std;

int main() {
    int values[3][3] = {
        {3, 1, 4},
        {1, 5, 9},
        {2, 6, 5}
    };
    int max = values[0][0];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (values[i][j] > max) {
                max = values[i][j];
            }
        }
    }
    
    cout << "Maximum value: " << max << endl;
    return 0;
}
