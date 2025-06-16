#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

int evaluatePostfix(const string &expression) {
    stack<int> stk;
    istringstream iss(expression);
    string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            stk.push(stoi(token));
        } else {
            int op2 = stk.top(); stk.pop();
            int op1 = stk.top(); stk.pop();
            switch (token[0]) {
                case '+': stk.push(op1 + op2); break;
                case '-': stk.push(op1 - op2); break;
                case '*': stk.push(op1 * op2); break;
                case '/': stk.push(op1 / op2); break;
            }
        }
    }
    return stk.top();
}

int main() {
    string expression = "5 1 2 + 4 * + 3 -";
    cout << "The result is: " << evaluatePostfix(expression) << "\n";
    return 0;
}
