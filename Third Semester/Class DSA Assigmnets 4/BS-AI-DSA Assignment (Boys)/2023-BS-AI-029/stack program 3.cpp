#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Function to reverse a string using a stack
string reverseString(const string& str) {
    stack<char> s;

    // Push each character of the string onto the stack
    for (char ch : str) {
        s.push(ch);
    }

    // Pop characters from the stack to form the reversed string
    string reversed;
    while (!s.empty()) {
        reversed += s.top(); // Get the top character
        s.pop();             // Remove it from the stack
    }

    return reversed;
}

int main() {
    string input;

    cout << "Enter a string to reverse: ";
    getline(cin, input); // Use getline to allow for spaces in the input

    string reversed = reverseString(input);

    cout << "Reversed string: " << reversed << endl;

    return 0;
}
