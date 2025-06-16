#include <iostream>
using namespace std;

int main()
{
    int rows = 2, cols = 3;

    char matrix1[2][3] = {{'A', 'B', 'C'}, {'D', 'E', 'F'}};
    char matrix2[2][3] = {{'G', 'H', 'I'}, {'J', 'K', 'L'}};
    char sumMatrix[2][3];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sumMatrix[i][j] = matrix1[i][j] + matrix2[i][j] - 'A';
        }
    }

    cout << "Resulting matrix with modified characters is:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << sumMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
