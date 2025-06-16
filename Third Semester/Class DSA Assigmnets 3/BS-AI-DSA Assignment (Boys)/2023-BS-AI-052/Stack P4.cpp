#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <cctype>
using namespace std;

// Function to evaluate postfix expression
int evaluatePostfix(const string& expression) {
    stack<int> stack;
    int i = 0;

    while (i < expression.size()) {
        char token = expression[i];

        // Skip spaces
        if (isspace(token)) {
            i++;
            continue;
        }

        // Push operand to stack
        if (isdigit(token)) {
            int operand = 0;
            while (i < expression.size() && isdigit(expression[i])) {
                operand = operand * 10 + (expression[i] - '0');
                i++;
            }
            stack.push(operand);
        } 
        // Pop operands, perform operation, and push result
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            if (stack.size() < 2) {
                throw invalid_argument("Invalid postfix expression");
            }
            int operand2 = stack.top();
            stack.pop();
            int operand1 = stack.top();
            stack.pop();

            switch (token) {
                case '+':
                    stack.push(operand1 + operand2);
                    break;
                case '-':
                    stack.push(operand1 - operand2);
                    break;
                case '*':
                    stack.push(operand1 * operand2);
                    break;
                case '/':
                    if (operand2 == 0) {
                        throw runtime_error("Division by zero");
                    }
                    stack.push(operand1 / operand2);
                    break;
            }
            i++;
        } 
        // Handle invalid token
        else {
            throw invalid_argument("Invalid token in postfix expression");
        }
    }
    if (stack.size() != 1) {
        throw invalid_argument("Invalid postfix expression");
    }

    return stack.top();
}

int main() {
    string expression;
    cout << "Enter postfix expression: ";
    getline(cin, expression);

    try {
        int result = evaluatePostfix(expression);
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
