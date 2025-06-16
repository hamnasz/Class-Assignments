#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>

int evaluatePostfix(const std::string& expression) {
    std::stack<int> stack;
    std::istringstream tokens(expression);
    std::string token;

    while (tokens >> token) {
        if (isdigit(token[0])) {
            // Push the operand to the stack
            stack.push(std::stoi(token));
        } else {
            // Pop two operands from the stack
            int right = stack.top(); stack.pop();
            int left = stack.top(); stack.pop();

            // Perform the operation and push the result back to the stack
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
                    std::cerr << "Invalid operator: " << token << std::endl;
                    return -1;
            }
        }
    }
    return stack.top(); // The final result will be at the top of the stack
}

int main() {
    std::string expression = "6 4 1 + 8 * + 9 -";
    std::cout << "Postfix Evaluation Result: " << evaluatePostfix(expression) << std::endl;
    return 0;
}
