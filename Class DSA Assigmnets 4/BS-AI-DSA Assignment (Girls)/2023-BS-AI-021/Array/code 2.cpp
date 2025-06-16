#include <iostream>
using namespace std;
int main() 
{
    int arr[] = {10, 20, 5, 14, 8, 12, 3, 16};
    int size = sizeof(arr) / sizeof(arr[0]);
    int maximum = arr[0];
    int minimum = arr[0];

    for (int i = 1; i < size; ++i) 
	{
        if (arr[i] > maximum) 
		{
            maximum = arr[i];
        }
        if (arr[i] < minimum) 
		{
            minimum = arr[i];
        }
    }
    
    cout << "Maximum value: " << maximum << endl;
    cout << "Minimum value: " << minimum << endl;
    return 0;
}