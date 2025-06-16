#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

int evaluatePostfix(const string &expr) {
    stack<int> s;
    stringstream ss(expr);
    string token;
    while (ss >> token) {
        if (isdigit(token[0])) s.push(stoi(token));
        else {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            if (token == "+") s.push(a + b);
            else if (token == "-") s.push(a - b);
            else if (token == "*") s.push(a * b);
            else if (token == "/") s.push(a / b);
        }
    }
    return s.top();
}

int main() {
    string expr;
    cout << "Enter postfix expression: ";
    getline(cin, expr);
    cout << "Result: " << evaluatePostfix(expr) << endl;
    return 0;
}
