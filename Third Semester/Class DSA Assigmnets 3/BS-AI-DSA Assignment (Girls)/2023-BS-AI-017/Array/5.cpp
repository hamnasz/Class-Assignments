#include <iostream>
using namespace std;

int main()
{
    int numbers[10], uniqueNumbers[10], index = 0;

    cout << "Please enter 10 integers: ";
    for (int i = 0; i < 10; i++)
    {
        cin >> numbers[i];
    }

    for (int i = 0; i < 10; i++)
    {
        bool found = false;

        for (int j = 0; j < index; j++)
        {
            if (numbers[i] == uniqueNumbers[j])
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            uniqueNumbers[index] = numbers[i];
            index++;
        }
    }

    cout << "Unique integers: ";
    for (int i = 0; i < index; i++)
    {
        cout << uniqueNumbers[i] << " ";
    }
    cout << endl;

    return 0;
}