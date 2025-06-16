#include <iostream>
#include <stack>
#include <string>
using namespace std;

string revstr(string str) {
    stack<char> s;
    for (char ch : str) {
        s.push(ch);
    }

    string reversed = "";
    while (!s.empty()) {
        reversed += s.top();
        s.pop();
    }
    return reversed;
}

int main() {
    string str = "Hello, World!";
    string reversed = revstr(str);
    cout << "Original string: " << str << endl;
    cout << "Reversed string: " << reversed << endl;

    return 0;
}
