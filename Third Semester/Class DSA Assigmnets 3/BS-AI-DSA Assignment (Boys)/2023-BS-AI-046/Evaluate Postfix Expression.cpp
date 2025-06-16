#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

int evaluate_postfix(const string& expression) {
    stack<int> s;
    stringstream ss(expression);
    string token;

    while (ss >> token) {
        if (isdigit(token[0])) {
            s.push(stoi(token));
        } else {
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
    return s.top();
}

int main() {
    string expression = "5 1 2 + 4 * + 3 -";
    cout << "Result: " << evaluate_postfix(expression) << endl;
    return 0;
}
