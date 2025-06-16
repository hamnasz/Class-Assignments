// Check if a given string of parentheses is balanced

#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Function to check if the given expression has balanced parentheses
int balanced(string expression) 
{
    stack<char> Stack;

    for (char ch : expression) 
    {
        // If the character is an opening parenthesis, push it onto the stack
        if (ch == '(' || ch == '{' || ch == '[') 
        {
            Stack.push(ch);
        }

        // If the character is a closing parenthesis
        else if (ch == ')' || ch == '}' || ch == ']') 
        {
            // Check if the stack is empty, which means there's no matching opening parenthesis
            if (Stack.empty()) 
            {
                cout << "It is not Balanced!";
                return 3;
            }

            char top = Stack.top(); // Get the top element of the stack (the last opening parenthesis)
            Stack.pop(); // Remove the top element from the stack

            // Check if the closing parenthesis matches the corresponding opening parenthesis
            if ((ch == ')' && top != '(') || (ch == '}' && top != '{') || (ch == ']' && top != '[')) 
            {
                cout << "It is not Balanced!";
                return 2; 
            }
        }
    }

    cout << "It is Balanced!";
    return 1;
}

int main() 
{
    string expression;
    cout << "Enter a string of parentheses: ";
    cin >> expression;

    balanced(expression);

    return 0;
}
