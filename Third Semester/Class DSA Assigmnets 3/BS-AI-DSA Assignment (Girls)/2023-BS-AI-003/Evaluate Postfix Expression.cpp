#include <iostream>
#include <stack>
#include <sstream>
#include <string>
using namespace std;
int performOperation(int operand1, int operand2, char op) {
    switch (op) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        default: throw invalid_argument("Invalid operator");
    }
}
int evaluatePostfix(const string& expression) {
    stack<int> s;
    stringstream ss(expression);
    string token;
    while (ss >> token) {
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) { 
            s.push(stoi(token));
}
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            int operand2 = s.top(); s.pop();
            int operand1 = s.top(); s.pop();
            int result = performOperation(operand1, operand2, token[0]);
            s.push(result);
        } else {
            throw invalid_argument("Invalid token in expression");
        }
    }
    return s.top();
}
int main() {
    string expression;
    cout << "Enter a postfix expression: ";
    getline(cin, expression);
    try {
        int result = evaluatePostfix(expression);
        cout << "The result is: " << result << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}