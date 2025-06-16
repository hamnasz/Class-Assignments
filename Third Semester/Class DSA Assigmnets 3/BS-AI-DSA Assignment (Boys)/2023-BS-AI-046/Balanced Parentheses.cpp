#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;

bool is_balanced(const string& expression) {
    stack<char> s;
    unordered_map<char, char> pairs = {{')', '('}, {'}', '{'}, {']', '['}};

    for (char c : expression) {
        if (pairs.count(c)) {
            if (s.empty() || s.top() != pairs[c]) return false;
            s.pop();
        } else if (c == '(' || c == '{' || c == '[') {
            s.push(c);
        }
    }
    return s.empty();
}

int main() {
    string expression;
    cout << "Enter expression with parentheses: ";
    cin >> expression;

    if (is_balanced(expression)) cout << "Balanced." << endl;
    else cout << "Not balanced." << endl;
    return 0;
}
