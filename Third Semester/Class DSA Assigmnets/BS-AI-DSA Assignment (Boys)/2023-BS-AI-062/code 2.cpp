#include <iostream>
using namespace std;
int main() 
{
    int numbers[6] = {23, 45, 12, 78, 34, 90};
    int max = numbers[0];

    for (int i = 1; i < 6; i++) 
	{
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }

    cout << "Maximum Value: " << max; 
    return 0;
}