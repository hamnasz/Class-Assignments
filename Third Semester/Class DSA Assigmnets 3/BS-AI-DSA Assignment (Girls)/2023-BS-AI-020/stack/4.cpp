#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

int evaluatePostfix(const string& expression) {
    stack<int> s;
    istringstream iss(expression);
    string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            // If the token is a number, push it to the stack
            s.push(stoi(token));
        } else {
            // The token is an operator
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            switch (token[0]) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
            }
        }
    }

    return s.top(); // The final result
}

int main() {
    string expression;
    cout << "Enter a postfix expression (e.g., '5 1 2 + 4 * + 3 -'): ";
    getline(cin, expression);

    int result = evaluatePostfix(expression);
    cout << "Result: " << result << endl;

    return 0;
}
