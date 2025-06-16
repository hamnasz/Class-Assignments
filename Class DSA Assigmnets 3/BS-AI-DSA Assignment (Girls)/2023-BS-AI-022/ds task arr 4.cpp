#include <iostream>
using namespace std;

int main() {
    char arr[10] = {'a', 'b', 'c', 'b', 'd', 'b', 'e', 'f', 'g', 'a'}; 
    char searchChar;
    int count = 0;
    cout << "Enter a character to search for: ";
    cin >> searchChar;
    for(int i = 0; i < 10; i++)
	{
        if(arr[i] == searchChar ) {
            count++;
        }
    }
    cout << "The character '" << searchChar << "' appears " << count << " times in the array." << endl;

    return 0;
}
