#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    // Get the postfix expression from the user
    string expression;
    cout << "Enter a postfix expression (e.g., '5 1 2 + 4 * + 3 -'): ";
    getline(cin, expression);

    stack<int> s; // Stack to hold the operands
    stringstream ss(expression);
    string token;

    while (ss >> token) {
        // Check if the token is a number
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            // Convert the token to an integer and push it onto the stack
            s.push(stoi(token));
        } 
        else {
            // The token is an operator
            if (s.size() < 2) {
                cout << "Error: Insufficient values in the expression." << endl;
                return 1;
            }

            // Pop the top two operands from the stack
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            int result;

            // Perform the operation based on the operator
            switch (token[0]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    if (b == 0) {
                        cout << "Error: Division by zero." << endl;
                        return 1;
                    }
                    result = a / b;
                    break;
                default:
                    cout << "Error: Unknown operator '" << token << "'." << endl;
                    return 1;
            }

            // Push the result back onto the stack
            s.push(result);
        }
    }

    // The final result should be the only value left in the stack
    if (s.size() == 1) {
        cout << "The result of the postfix expression is: " << s.top() << endl;
    } else {
        cout << "Error: The expression was not valid." << endl;
    }

    return 0;
}

