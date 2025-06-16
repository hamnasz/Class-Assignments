// Stack-based program to reverse a string

#include <iostream>
#include <stack>
using namespace std;

// Function to Print stack
void printStack(stack<int> st)
{
    while (!st.empty()) 
    {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

int main()
{
    stack<int> Stack;

    Stack.push(1);
    Stack.push(2);
    Stack.push(3);
    Stack.push(4);
    Stack.push(5);

    // Print Original stack
    cout << "Original stack: ";
    printStack(Stack);

    // Store original stack to tempstack
    stack<int> tempStack;
    while (!Stack.empty()) 
    {
        tempStack.push(Stack.top());
        Stack.pop();
    }
    Stack = tempStack;

    // Print Reversed stack
    cout << "Reversed stack: ";
    printStack(Stack);

    return 0;
}