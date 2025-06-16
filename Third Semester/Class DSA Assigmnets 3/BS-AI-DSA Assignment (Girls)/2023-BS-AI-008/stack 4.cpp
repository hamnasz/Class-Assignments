#include <iostream>
#include <stack>
#include <sstream>
#include <string>
using namespace std;

int evaluatePostfix(const std::string& expression) {
    stack<int> stack;
    istringstream iss(expression);
    string token;

    while (iss >> token) {
        if (isdigit(token[0])) 
		{
            stack.push(std::stoi(token));
        } else {
            int right = stack.top(); stack.pop();
            int left = stack.top(); stack.pop();
            
            switch (token[0]) {
                case '+':
                    stack.push(left + right);
                    break;
                case '-':
                    stack.push(left - right);
                    break;
                case '*':
                    stack.push(left * right);
                    break;
                case '/':
                    stack.push(left / right);
                    break;
                default:
                    cerr << "Unknown operator: " << token <<endl;
                    return 0;
            }
        }
    }

    return stack.top();
}

int main() {
    string expression;

    cout << "Enter a postfix expression: ";
    getline(cin, expression);

    int result = evaluatePostfix(expression);
    cout << "The result is: " << result <<endl;

    return 0;
}
