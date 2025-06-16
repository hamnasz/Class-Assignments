#include <iostream>
#include <stack>
using namespace std;

bool isBalanced(string str) {
    stack<char> s;
    for (char ch : str) {
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        } else {
            if (s.empty()) return false;
            char top = s.top();
            if ((ch == ')' && top == '(') || 
                (ch == '}' && top == '{') || 
                (ch == ']' && top == '[')) {
                s.pop();
            } else {
                return false;
            }
        }
    }
    return s.empty();
}

int main() {
    string expr;
    cout << "Enter a string of parentheses: ";
    cin >> expr;

    if (isBalanced(expr)) {
        cout << expr << " is balanced." << endl;
    } else {
        cout << expr << " is not balanced." << endl;
    }

    return 0;
}
