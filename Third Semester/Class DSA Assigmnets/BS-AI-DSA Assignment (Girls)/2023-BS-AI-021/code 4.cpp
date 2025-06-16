#include <iostream>
#include <string>
using namespace std;
int main() 
{
    string colors[3];
    for (int i = 0; i < 3; i++) 
	{
        cout << "Enter a color: ";
        cin >> colors[i];
    }
    cout << "You entered:\n";
    for (int i = 0; i < 3; i++) 
	{
        cout << colors[i] << " "<<endl;
    }
    return 0;
}