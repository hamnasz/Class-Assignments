#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>

int evaluatePostfix(const std::string& expression) {
    std::stack<int> stack;
    std::istringstream tokens(expression);
    std::string token;

    // Read each token from the expression
    while (tokens >> token) {
        if (std::isdigit(token[0])) {
            // If the token is a number, push it onto the stack
            stack.push(std::stoi(token));
        } else {
            // Otherwise, the token is an operator
            int operand2 = stack.top();
            stack.pop();
            int operand1 = stack.top();
            stack.pop();

            // Perform the corresponding operation
            if (token == "+") {
                stack.push(operand1 + operand2);
            } else if (token == "-") {
                stack.push(operand1 - operand2);
            } else if (token == "*") {
                stack.push(operand1 * operand2);
            } else if (token == "/") {
                stack.push(operand1 / operand2);
            } else {
                std::cerr << "Unknown operator: " << token << std::endl;
                return -1;
            }
        }
    }

    // The result should be the only element left in the stack
    return stack.top();
}

int main() {
    std::string expression = "5 1 2 + 4 * + 3 -";
    int result = evaluatePostfix(expression);
    std::cout << "The result of the postfix expression \"" << expression << "\" is: " << result << std::endl;
    return 0;
}