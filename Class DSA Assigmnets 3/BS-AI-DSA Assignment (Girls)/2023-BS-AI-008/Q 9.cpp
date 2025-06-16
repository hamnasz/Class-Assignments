
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    string expression;
    cout << "Enter a postfix expression: ";
    cin >> ws; // Consume leading whitespace
    getline(cin, expression);

    stack<int> evalStack;

    for (char c : expression) {
        if (isdigit(c)) {
            evalStack.push(c - '0');
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            int b = evalStack.top();
            evalStack.pop();
            int a = evalStack.top();
            evalStack.pop();

            switch (c) {
                case '+': evalStack.push(a + b); break;
                case '-': evalStack.push(a - b); break;
                case '*': evalStack.push(a * b); break;
                case '/': evalStack.push(a / b); break;
            }
        }
    }

    cout << "Result: " << evalStack.top() << endl;
 }