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

    bool isEmpty()
    {
        return top == -1;
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

    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack is already empty!" << endl;
        }
        else
        {
            top--;
        }
    }
};

int main()
{
    Stack stack;
    cout << "Is stack empty? " << (stack.isEmpty() ? "Yes" : "No") << endl;
    stack.push(50);
    cout << "Is stack empty? " << (stack.isEmpty() ? "Yes" : "No") << endl;
    stack.pop();
    cout << "Is stack empty? " << (stack.isEmpty() ? "Yes" : "No") << endl;
    return 0;
}
