#include <iostream>
using namespace std;
int main() 
{
    int Arr[] = {2, 3, 4, 5, 6};
    int size = sizeof(Arr) / sizeof(Arr[0]);
        cout << "Elements of the array: " << endl;
    for (int i = 0; i < size; ++i) 
	{
        cout << Arr[i] << endl;
    }
    return 0;
}