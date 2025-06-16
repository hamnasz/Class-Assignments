#include <iostream>
using namespace std;
int main() 
{
    int numbers[] = {10, 20, 30, 40, 50};
    int sum = 0;

    for (int num : numbers) 
	{
        sum += num;
    }
    float average = sum / 5.0; 
    cout << "Average: " << average; 
    return 0;
}