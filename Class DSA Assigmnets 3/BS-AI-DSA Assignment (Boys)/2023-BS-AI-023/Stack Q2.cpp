#include <iostream>
#include <stack>
using namespace std;

bool isBalanced(string expr) {
    stack<char> s;
    for(char ch : expr) {
        if(ch == '(' || ch == '{' || ch == '[') s.push(ch);
        else {
            if(s.empty()) return false;
            char top = s.top();
            s.pop();
            if((ch == ')' && top != '(') || (ch == '}' && top != '{') || (ch == ']' && top != '[')) return false;
        }
    }
    return s.empty();
}

int main() {
    string expr;
    cout << "Enter an expression with parentheses: ";
    cin >> expr;
    if(isBalanced(expr)) cout << "The parentheses are balanced." << endl;
    else cout << "The parentheses are not balanced." << endl;
    return 0;
}
