#include <iostream>
using namespace std;

int main()
{
    int rows1 = 2, cols1 = 3, rows2 = 3, cols2 = 2;

    int matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int matrix2[3][2] = {{7, 8}, {9, 10}, {11, 12}};
    int resultMatrix[2][2] = {0};

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            for (int k = 0; k < cols1; k++)
            {
                resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    cout << "Resultant Matrix after multiplication is:" << endl;
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            cout << resultMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}