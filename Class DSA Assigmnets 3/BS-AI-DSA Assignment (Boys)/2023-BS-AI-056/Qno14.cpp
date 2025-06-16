#include <iostream>
#include <stack>
#include <sstream>
#include <string>

using namespace std;

int evaluatePostfix(const string& expression) {
    stack<int> s; 
    stringstream ss(expression);
    string token;

    while (ss >> token) {
        if (isdigit(token[0])) {
            s.push(stoi(token));
        } else {
            int operand2 = s.top(); s.pop();
            int operand1 = s.top(); s.pop();

            switch (token[0]) {
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
                    cerr << "Unknown operator: " << token << endl;
                    return 0;
            }
        }
    }

    return s.top();
}

int main() {
    string expression;

    cout << "Enter a postfix expression: ";
    getline(cin, expression); // Read the entire line for the expression

    int result = evaluatePostfix(expression);
    cout << "The result of the postfix expression is: " << result << endl;

    return 0;
}
