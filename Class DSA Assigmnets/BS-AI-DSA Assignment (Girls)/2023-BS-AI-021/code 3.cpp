#include <iostream>
using namespace std;
int main() 
{
    float grades[4] = {85.5, 90.0, 78.5, 88.0};
    float total = 0;

    for (int i = 0; i < 4; i++) 
	{
        total += grades[i];
    }

    cout << "Average: " << total / 4; 
    return 0;
}