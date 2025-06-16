#include <iostream>
#include <stack>
using namespace std;

bool isBalanced(string str) {
    stack<char> s;
    for (char c : str) {
        if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

int main() {
    cout << "Is \"(())\" balanced? " << (isBalanced("(())") ? "Yes" : "No") << endl;
    cout << "Is \"(()\" balanced? " << (isBalanced("(()") ? "Yes" : "No") << endl;

    return 0;
}