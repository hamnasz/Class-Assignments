#include <iostream>
#include <list>
using namespace std;
int main() 
{
    list<int> numbers;
    numbers.push_back(5);
    numbers.push_back(15);
    numbers.push_back(25);
    numbers.push_back(35);

    int searchValue = 15;
    bool found = false;

    for (int num : numbers) {
        if (num == searchValue) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << searchValue << " is found in the list." << endl;
    } else {
        cout << searchValue << " is not found in the list." << endl;
    }

    return 0;
}
