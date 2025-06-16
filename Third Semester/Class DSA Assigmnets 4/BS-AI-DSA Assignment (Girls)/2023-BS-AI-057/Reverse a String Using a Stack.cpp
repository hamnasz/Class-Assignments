#include <iostream>
#include <stack>
using namespace std;

void reverseString(string str) {
    stack<char> s;
    for (char ch : str) s.push(ch);
    while (!s.empty()) {
        cout << s.top();
        s.pop();
    }
    cout << endl;
}

int main() {
    string str = "hello";
    cout << "Reversed: ";
    reverseString(str);

    return 0;
}
