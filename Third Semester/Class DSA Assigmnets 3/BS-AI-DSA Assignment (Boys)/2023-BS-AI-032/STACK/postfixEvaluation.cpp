#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

int evaluatePostfix(const string &expression)
{
    stack<int> s;
    istringstream iss(expression);
    string token;

    while (iss >> token)
    {
        if (isdigit(token[0]))
        {
            s.push(stoi(token));
        }
        else
        {
            int operand2 = s.top();
            s.pop();
            int operand1 = s.top();
            s.pop();
            switch (token[0])
            {
            case '+':
                s.push(operand1 + operand2);
                break;
            case '-':
                s.push(operand1 - operand2);
                break;
            case '*':
                s.push(operand1 * operand2);
                break;
            case '/':
                s.push(operand1 / operand2);
                break;
            default:
                cout << "Invalid operator: " << token << endl;
                return 0;
            }
        }
    }

    return s.top();
}

int main()
{
    string postfixExpression;
    cout << "Enter a postfix expression: ";
    getline(cin, postfixExpression);

    int result = evaluatePostfix(postfixExpression);
    cout << "Result: " << result << endl;

    return 0;
}
