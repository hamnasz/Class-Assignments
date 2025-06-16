#include <iostream>
using namespace std;

int main()
{

    int n, m;
    cout << "Enter rows: ";
    cin >> n;
    cout << "Enter columns: ";
    cin >> m;

    int arr[n][m];
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> arr[i][j];
        }
    }

    cout << "Matrix is: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }

    int transposed[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            transposed[i][j] = arr[j][i];
        }
    }

    n = n + m;
    m = n - m;
    n = n - m;
    cout << "Transpose Matrix is: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << transposed[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
