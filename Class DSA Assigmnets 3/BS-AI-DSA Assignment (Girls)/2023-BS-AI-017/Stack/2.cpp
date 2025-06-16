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

    int peek()
    {
        if (top == -1)
        {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        else
        {
            return arr[top];
        }
    }
};

int main()
{
    Stack stack;
    stack.push(30);
    stack.push(40);
    cout << "Top element is: " << stack.peek() << endl;
    return 0;
}
