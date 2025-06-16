#include <iostream>
using namespace std;

class Stack
{
private:
    int top;
    int arr[5];

public:
    Stack()
    {
        top = -1;
    }

    void push(int value)
    {
        if (top == 4)
        {
            cout << "Stack Overflow!" << endl;
        }
        else
        {
            top++;
            arr[top] = value;
        }
    }

    int size()
    {
        return top + 1;
    }
};

int main()
{
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    cout << "Stack size: " << stack.size() << endl;
    return 0;
}
