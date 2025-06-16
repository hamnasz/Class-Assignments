#include <iostream>
using namespace std;
int main()
{
    int arr[8]; 
    cout << "Enter 8 integers: ";
    for (int i = 0; i < 8; i++)
	{
        cin >> arr[i];
    }

    cout << "Original array: ";
    for (int i = 0; i < 8; i++)
	{
        cout << arr[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < 4; i++) 
	{
        int temp = arr[i];
        arr[i] = arr[7 - i];
        arr[7 - i] = temp;
    }
    cout << "Reversed array: ";
    
    for (int i = 0; i < 8; i++)
	{
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
