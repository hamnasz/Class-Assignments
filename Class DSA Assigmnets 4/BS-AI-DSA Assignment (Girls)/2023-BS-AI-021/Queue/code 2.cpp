#include <iostream>
#include <queue>
using namespace std;
int main() 
{
    queue<int> numbers;
    numbers.push(10);
    numbers.push(20);
    numbers.push(30);
    
    cout << "Total number of elements in the queue: " << numbers.size() << endl;
    return 0;
}
