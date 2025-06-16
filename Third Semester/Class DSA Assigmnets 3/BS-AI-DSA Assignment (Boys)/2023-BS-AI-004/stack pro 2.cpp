#include <iostream>
#include <stack>
using namespace std;

bool isBalanced(const string &str) {
    stack<char> s;
    for (char c : str) {
        if (c == '(' || c == '{' || c == '[') s.push(c);
        else if ((c == ')' && !s.empty() && s.top() == '(') ||
                 (c == '}' && !s.empty() && s.top() == '{') ||
                 (c == ']' && !s.empty() && s.top() == '[')) {
            s.pop();
        } else return false;
    }
    return s.empty();
}

int main() {
    string expr;
    cout << "Enter parentheses string: ";
    cin >> expr;
    cout << (isBalanced(expr) ? "Balanced" : "Not Balanced") << endl;
    return 0;
}
