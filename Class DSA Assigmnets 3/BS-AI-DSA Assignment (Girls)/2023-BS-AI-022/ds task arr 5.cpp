#include <iostream>
using namespace std;
int main() 
{
    int arr[6]; 
    int uniqueArr[6]; 
    int n = 6, uniqueCount = 0;

    cout << "Enter 6 integers: ";
    for (int i = 0; i < n; i++) 
	{
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++) 
	{
        bool isDuplicate = false;
        
        for (int j = 0; j < uniqueCount; j++) 
		{
            if (arr[i] == uniqueArr[j]) 
			{
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate)
		{
            uniqueArr[uniqueCount] = arr[i];
            uniqueCount++;
        }
    }

    cout << "Unique elements: ";
    for (int i = 0; i < uniqueCount; i++)
	{
        cout << uniqueArr[i] << " ";
    }
    cout << endl;

    return 0;
}
