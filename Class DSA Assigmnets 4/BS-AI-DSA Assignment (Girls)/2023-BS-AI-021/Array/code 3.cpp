#include <iostream>
using namespace std;
int main() 
{
    int arr[] = {10, 20, 30, 40, 50};
    int length = sizeof(arr) / sizeof(arr[0]);

    cout << "Initial array: ";
    for (int i=0; i<length; i++) 
	{
        cout << arr[i] << " ";
    }

    for (int i=0; i<length / 2; i++) {
        int Temp = arr[i];
        arr[i] = arr[length - i - 1];
        arr[length - i - 1] = Temp;
    }
    cout<<endl;
    cout << "Array after reversal: ";
    for (int i=0; i<length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}