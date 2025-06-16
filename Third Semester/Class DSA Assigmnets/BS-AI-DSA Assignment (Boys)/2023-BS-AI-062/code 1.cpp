#include <iostream>
using namespace std;
int main() 
{
    int original[5] = {10, 20, 30, 40, 50};
    int copy[5];

    for (int i = 0; i < 5; i++) 
	{
        copy[i] = original[i];
    }

    cout << "Copied Array: ";
    for (int i = 0; i < 5; i++) 
	{
        cout << copy[i] << " "; 
    }
    return 0;
}