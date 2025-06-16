#include <iostream>
#include <stack>

using namespace std;

void reverseString(string& str) {
    stack<char> s;

    for (char c : str) {
        s.push(c);
    }

    int i = 0;
    while (!s.empty()) {
        str[i++] = s.top();
        s.pop();
    }
}

int main() {
    string str = "hello";

    reverseString(str);

    cout << str << endl;

    return 0;
}