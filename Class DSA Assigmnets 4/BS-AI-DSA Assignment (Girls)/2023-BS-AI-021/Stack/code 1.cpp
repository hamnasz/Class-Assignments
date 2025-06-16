#include <iostream>
#include <stack>
using namespace std;
int main() 
{
    stack<int> numbers;

    numbers.push(10);
    numbers.push(20);
    numbers.push(30);

    cout << "Top element: " << numbers.top() << endl;
    numbers.pop();
    
    cout << "Top element after pop: " << numbers.top() << endl;
    return 0;
}