#include <iostream>
#include <stack>
#include <string>

bool isBalanced(const std::string& expression) {
    std::stack<char> charStack;

    // Traverse each character in the expression
    for (char ch : expression) {
        // If the character is an opening bracket, push it onto the stack
        if (ch == '(' || ch == '{' || ch == '[') {
            charStack.push(ch);
        }
        // If the character is a closing bracket, check if it matches the top of the stack
        else if (ch == ')' || ch == '}' || ch == ']') {
            // If the stack is empty or the top doesn't match, it's unbalanced
            if (charStack.empty()) {
                return false;
            }

            char top = charStack.top();
            charStack.pop();

            // Check if the closing bracket matches the corresponding opening bracket
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;
            }
        }
    }

    // If the stack is empty at the end, all brackets were balanced
    return charStack.empty();
}

int main() {
    std::string expression;
    std::cout << "Enter an expression with parentheses: ";
    std::cin >> expression;

    // Check if the expression has balanced parentheses
    if (isBalanced(expression)) {
        std::cout << "The expression is balanced." << std::endl;
    } else {
        std::cout << "The expression is not balanced." << std::endl;
    }

    return 0;
}
