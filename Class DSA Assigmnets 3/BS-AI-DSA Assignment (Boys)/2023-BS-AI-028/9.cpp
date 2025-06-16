#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

int evaluatePostfix(string expr) {
    stack<int> s;
    stringstream ss(expr);
    string token;

    while (ss >> token) {
        if (isdigit(token[0])) {
            s.push(stoi(token));
        } else {
            int val2 = s.top(); s.pop();
            int val1 = s.top(); s.pop();
            switch (token[0]) {
                case '+': s.push(val1 + val2); break;
                case '-': s.push(val1 - val2); break;
                case '*': s.push(val1 * val2); break;
                case '/': s.push(val1 / val2); break;
            }
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
