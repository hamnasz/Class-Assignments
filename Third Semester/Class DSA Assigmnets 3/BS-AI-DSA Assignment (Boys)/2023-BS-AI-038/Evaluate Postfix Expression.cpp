#include <iostream>
#include <stack>
#include <string>
using namespace std;

int evaluatePostfix(const string &str) {
    stack<int> s;
    for (char ch : str) {
        if (ch >= '0' && ch <= '9') {
            s.push(ch - '0');
        } else {
            int op2 = s.top();
            s.pop();
            int op1 = s.top();
            s.pop();
            if (ch == '+') s.push(op1 + op2);
            else if (ch == '-') s.push(op1 - op2);
            else if (ch == '*') s.push(op1 * op2);
            else if (ch == '/') s.push(op1 / op2);
        }
    }
    return s.top();
}

int main() {
    string str;
    cout << "Enter a postfix expression: ";
    cin >> str;
    
    int result = evaluatePostfix(str);
    cout << "Result: " << result << endl;
    return 0;
}
