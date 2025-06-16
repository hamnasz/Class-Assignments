#include <iostream>
using namespace std;

int main()
{
    float numbers[] = {10.5, 20.7, 5.2, 30.1, 25.9};
    float highestValue = numbers[0];
    int arraySize = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 1; i < arraySize; i++)
    {
        if (numbers[i] > highestValue)
        {
            highestValue = numbers[i];
        }
    }

    cout << "Maximum element: " << highestValue << endl;
    return 0;
}
