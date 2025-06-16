#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

int evaluatePostfix(string expression) {
    stack<int> s;
    stringstream ss(expression);
    string token;

    while (ss >> token) {
        if (isdigit(token[0])) {
            s.push(stoi(token));
        } else {
            int val2 = s.top(); s.pop();
            int val1 = s.top(); s.pop();

            if (token == "+") s.push(val1 + val2);
            else if (token == "-") s.push(val1 - val2);
            else if (token == "*") s.push(val1 * val2);
            else if (token == "/") s.push(val1 / val2);
        }
    }

    return s.top();
}

int main() {
    string expression = "5 1 2 + 4 * + 3 -";
    cout << "Postfix Expression: " << expression << endl;
    cout << "Result: " << evaluatePostfix(expression) << endl;

    return 0;
}
