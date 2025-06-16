#include <iostream>
#include <stack>
using namespace std;

// Function to reverse a string using a stack
string reverseString(string str) {
    stack<char> s;  // Stack to hold characters of the string

    // Push each character of the string onto the stack
    for (char ch : str) {
        s.push(ch);
    }

    // Pop each character from the stack and append it to the reversed string
    string reversed = "";
    while (!s.empty()) {
        reversed += s.top();  // Get the character at the top of the stack
        s.pop();              // Remove the character from the stack
    }

    return reversed;  // Return the reversed string
}

int main() {
    string input;

    // Get the input string from the user
    cout << "Enter a string to reverse: ";
    getline(cin, input);

    // Reverse the string using the stack-based function
    string reversed = reverseString(input);

    // Display the reversed string
    cout << "Reversed string: " << reversed << endl;

    return 0;
}
