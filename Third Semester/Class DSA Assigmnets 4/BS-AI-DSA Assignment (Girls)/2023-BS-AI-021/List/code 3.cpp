#include <iostream>
#include <list>
using namespace std;
int main() 
{
    list<int> numbers;

    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    numbers.push_front(5);

    auto it = numbers.begin();
    advance(it, numbers.size() / 2);
    numbers.insert(it, 15);

    numbers.push_back(40);

    for (int value : numbers) {
        cout << value << " ";
    }
    return 0;
}