#include <iostream>
#include <stack>
#include <string>
using namespace std;

int balanced(string expression) 
{
    stack<char> Stack;

    for (char ch : expression) 
    {
        // If it's an opening bracket, push to the stack
        if (ch == '(' || ch == '{' || ch == '[') 
        {
            Stack.push(ch);
        }
        // If it's a closing bracket, check for matching opening bracket
        else if (ch == ')' || ch == '}' || ch == ']') 
        {
            // Stack empty means unbalanced
            if (Stack.empty()) 
            {
                cout<<"It is not Balanced!";
                return 3;
            }

            char top = Stack.top();
            Stack.pop();

            // Check if the popped bracket matches the closing one
            if ((ch == ')' && top != '(') || (ch == '}' && top != '{') || (ch == ']' && top != '[')) 
            {
                cout<<"It is not Balanced!";
                return 2;
            }
        }
    }

    cout<<"It is Balanced!";
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
