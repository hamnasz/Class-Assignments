#include <iostream>
using namespace std;

int main()
{
    char characters[10];
    char targetChar;
    cout << "Enter 10 characters: ";
    for (int i = 0; i < 10; i++)
    {
        cin >> characters[i];
    }
    cout << "Enter character to count: ";
    cin >> targetChar;

    int occurrenceCount = 0;
    
    for (int i = 0; i < 10; i++)
    {
        if (characters[i] == targetChar)
            occurrenceCount++;
    }
    cout << "Occurrences of " << targetChar << ": " << occurrenceCount << endl;
    return 0;
}
