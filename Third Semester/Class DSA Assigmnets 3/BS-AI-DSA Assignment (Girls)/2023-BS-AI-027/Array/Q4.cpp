#include <iostream>
using namespace std;

int main()
 {
    const int SIZE = 8;
    char arr[SIZE]; 
    char goal;
    int count = 0;

    // Input 8 characters
    cout << "Enter 8 characters of your choice:" << endl;
    for(int i = 0; i < SIZE; i++) 
	{
        cin >> arr[i];
    }

    // Input goal character
    cout << "Enter the character to count:" << endl;
    cin >> goal;

    // Count occurrences
    for(int i = 0; i < SIZE; i++) 
	{
        if(arr[i] == goal) 
		{
            count++;
        }
    }

    // Display result
    cout << "Character '" << goal << "' appears " << count << " times in the array." << endl;

    return 0;
}

