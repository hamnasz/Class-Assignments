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

    bool isFull()
    {
        return top == 4;
    }

    void push(int value)
    {
        if (isFull())
        {
            cout << "Stack is full!" << endl;
        }
        else
        {
            top++;
            arr[top] = value;
        }
    }
};

int main()
{
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.push(50);
    cout << "Trying to push another element:" << endl;
    stack.push(60); // Should display "Stack is full!"
    return 0;
}
