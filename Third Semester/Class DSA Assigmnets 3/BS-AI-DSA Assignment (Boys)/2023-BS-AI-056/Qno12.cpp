#include <iostream>
#include <stack>
using namespace std;

bool isBalanced(string expression) {
    stack<char> s;

    for (char c : expression) {
        if (c == '(' || c == '{' || c == '[') {
            s.push(c);
        }
        else if (c == ')' || c == '}' || c == ']') {
            if (s.empty()) return false;

            char top = s.top();
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                return false;
            }
            s.pop();
        }
    }

    return s.empty();
}
//
int main() {
    string expression;
    cout << "Enter an expression with parentheses: ";
    cin >> expression;

    if (isBalanced(expression)) {
        cout << "The expression is balanced." << endl;
    } else {
        cout << "The expression is not balanced." << endl;
    }

    return 0;
}
