#include <iostream>
using namespace std;

int main() {
    int array[2][2][2] = {
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}}
    };
    
    int maxElement = array[0][0][0];
  
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                if (array[i][j][k] > maxElement)
                    maxElement = array[i][j][k];

    cout << "Maximum element in 3D array: " << maxElement << endl;
    return 0;
}
