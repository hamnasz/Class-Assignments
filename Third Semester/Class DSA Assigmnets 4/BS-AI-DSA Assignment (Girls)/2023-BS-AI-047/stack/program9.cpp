#include <iostream>
#include <stack>
using namespace std;

string reverseString(string str) {
    stack<char> s;
    for (char ch : str) {
        s.push(ch);  // Push each character onto the stack
    }

    string reversedStr;
    while (!s.empty()) {
        reversedStr += s.top();  // Pop each character and add to reversedStr
        s.pop();
    }

    return reversedStr;
}

int main() {
    string str;
    cout << "Enter a string to reverse: ";
    cin >> str;

    string reversedStr = reverseString(str);
    cout << "Reversed string: " << reversedStr << endl;

    return 0;
}
