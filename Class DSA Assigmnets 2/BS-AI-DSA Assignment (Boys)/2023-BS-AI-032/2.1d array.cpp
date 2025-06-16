#include <iostream>
using namespace std;
int main()
{
    int n;
    cout << "Enter Size of Array: ";
    cin >> n;

    int arr[n];
    cout << "Enter Values of Array: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Prime numbers in the array: ";
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > 1)
        {
            int j;
            for (j = 2; j < arr[i]; j++)
            {
                if (arr[i] % j == 0)
                {
                    break;
                }
            }
            if (j == arr[i])
            {
                cout << arr[i] << " ";
            }
        }
    }
    cout << endl;

    return 0;
}