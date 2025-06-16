#include <iostream>
using namespace std;
int main() 
{
    int numbers[5] = {10, 20, 30, 40, 50};
    cout << "Original array: ";
    for (int i = 0; i < 5; i++) 
	{
        cout << numbers[i] << " "; 
    }
    cout << endl;

    int temp = numbers[0];
    numbers[0] = numbers[4];
    numbers[4] = temp;
    
    cout << "Array after swapping: ";
    for (int i = 0; i < 5; i++) 
	{
        cout << numbers[i] << " "; 
    }
    cout << endl;
    return 0;
}