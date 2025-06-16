#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(const string& expression) {
    stack<char> s;
    for (char ch : expression) {
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.empty()) return false;
            if ((ch == ')' && s.top() != '(') ||
                (ch == '}' && s.top() != '{') ||
                (ch == ']' && s.top() != '[')) {
                return false;
            }
            s.pop();
        }
    }
    return s.empty();
}

void balancedParentheses() {
    string expression;

    cout << "Enter an expression with parentheses: ";
    cin >> expression;

    cout << "Is Balanced: " << (isBalanced(expression) ? "Yes" : "No") << "\n";
}

int main() {
    balancedParentheses();
    return 0;
}
