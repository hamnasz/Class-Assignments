#include <iostream>
using namespace std;

int main() {
    int array[2][2][2] = {
        {{9, 2}, {3, 7}},
        {{5, 6}, {1, 8}}
    };
    
    int minElement = array[0][0][0]; 
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                if (array[i][j][k] < minElement)
                    minElement = array[i][j][k];

    cout << "Minimum element in 3D array: " << minElement << endl;
    return 0;
}
