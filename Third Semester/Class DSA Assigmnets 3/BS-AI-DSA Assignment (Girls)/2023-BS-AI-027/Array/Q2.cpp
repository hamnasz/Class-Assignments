#include <iostream>
using namespace std;

int main() 
{
	//Array declaration
    int arr[5]; 
    int max, min;

    // Input 5 elements
    cout << "Enter 5 integers of your choice:" << endl;
    for(int i = 0; i < 5; i++) 
	{
        cin >> arr[i];
    }

    // Initialize max and min
    max = arr[0];
    min = arr[0];

    // Find max and min
    for(int i = 1; i < 5; i++) 
	{
        if(arr[i] > max) 
		{
            max = arr[i];
        }
        if(arr[i] < min) 
		{
            min = arr[i];
        }
    }

    // Display maximum and minimum values
    cout << "Maximum value is: " << max << endl;
    cout << "Minimum value is: " << min << endl;

    return 0;
}

