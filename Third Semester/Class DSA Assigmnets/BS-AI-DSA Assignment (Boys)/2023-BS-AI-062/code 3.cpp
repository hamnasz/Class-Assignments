#include <iostream>
using namespace std;
int main() 
{
    int arr[5] = {1, 2, 3, 4, 5};
    int reversed[5];

    for (int i = 0; i < 5; i++) 
	{
        reversed[i] = arr[4 - i];
    }

    cout << "Reversed Array: ";
    for (int i = 0; i < 5; i++) {
        cout << reversed[i] << " "; 
    }
    return 0;
}