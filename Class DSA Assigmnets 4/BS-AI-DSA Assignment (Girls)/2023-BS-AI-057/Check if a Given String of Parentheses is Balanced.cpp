#include <iostream>
#include <stack>
using namespace std;

bool isBalanced(string str) {
    stack<char> s;
    for (char ch : str) {
        if (ch == '(') s.push(ch);
        else if (ch == ')') {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

int main() {
    string str = "(())";
    if (isBalanced(str)) cout << "Balanced\n";
    else cout << "Not Balanced\n";

    return 0;
}
