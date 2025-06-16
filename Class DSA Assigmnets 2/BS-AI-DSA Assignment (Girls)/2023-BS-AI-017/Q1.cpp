#include <iostream>
using namespace std;

int main()
{
    char arr1[5] = {'A', 'B', 'C', 'D', 'E'}, arr2[5];

    cout << "Array 1: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << arr1[i] << endl;
    }

    int n = 0;
    for (int i = 4; i >= 0; i--)
    {
        arr2[i] = arr1[n];
        n++;
    }

    cout << "Array 2: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << arr2[i] << endl;
    }

    return 0;
}