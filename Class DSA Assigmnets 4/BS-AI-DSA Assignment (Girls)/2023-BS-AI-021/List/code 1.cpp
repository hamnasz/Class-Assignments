#include <iostream>
#include <list>
using namespace std;
int main() 
{
    list<int> numbers;

    numbers.push_back(5);
    numbers.push_back(15);
    numbers.push_back(25);

    cout << "Initial Numbers: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    numbers.remove(15);

    cout << "Numbers after removal: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}