#include <iostream>
#include <stack>

using namespace std;

bool isBalanced(string expr) {
    stack<char> s;
    char x;

    for (char& i : expr) {
        if (i == '(' || i == '[' || i == '{') {
            s.push(i);
            continue;
        }

        if (s.empty())
            return false;

        switch (i) {
            case ')':
                x = s.top();
                s.pop();
                if (x != '(')
                    return false;
                break;

            case '}':
                x = s.top();
                s.pop();
                if (x != '{')
                    return false;
                break;

            case ']':
                x = s.top();
                s.pop();
                if (x != '[')
                    return false;
                break;
        }
    }

    return s.empty();
}

int main() {
    string expr = "{()}[]";

    if (isBalanced(expr))
        cout << "Balanced\n";
    else
        cout << "Not Balanced\n";

    return 0;
}