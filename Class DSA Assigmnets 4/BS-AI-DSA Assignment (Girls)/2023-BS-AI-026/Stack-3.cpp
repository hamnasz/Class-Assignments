#include <iostream>
#include <stack>
using namespace std;

string reverseString(const string& str) {
    stack<char> s;

    // Push each character onto the stack
    for (char ch : str) {
        s.push(ch);
    }

    string reversed;
    
    // Pop each character from the stack to reverse the string
    while (!s.empty()) {
        reversed += s.top();
        s.pop();
    }

    return reversed;
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input); // Use getline to allow spaces

    string reversed = reverseString(input);
    cout << "Reversed string: " << reversed << endl;

    return 0;
}
