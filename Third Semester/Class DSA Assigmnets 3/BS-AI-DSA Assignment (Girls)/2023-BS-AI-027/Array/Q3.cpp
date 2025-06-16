#include <iostream>
using namespace std;

int main() 
{
    int arr[8]; // Array of 8 elements

    // Input 8 elements
    cout << "Enter 8 integers of your choice:" << endl;
    for(int i = 0; i < 8; i++) 
	{
        cin >> arr[i];
    }

    // Reverse the array
    for(int i = 0; i < 4; i++)
	 { // Only need to iterate halfway
        int temp = arr[i];
        arr[i] = arr[7 - i];
        arr[7 - i] = temp;
    }

    // Display reversed array
    cout << "Reversed array:" << endl;
    for(int i = 0; i < 8; i++) 
	{
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}

