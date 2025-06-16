//- Create a stack-based program to reverse a string (push each character and pop to reverse).
#include <iostream>
#include <stack>

using namespace std;

void reverseString(char str[]) {
    stack<char> s;

    // Push characters onto the stack
    int i = 0;
    while (str[i] != '\0') {
        s.push(str[i]);
        i++;
    }

    // Pop characters from the stack and assign them back to the string
    i = 0;
    while (!s.empty()) {
        str[i] = s.top();
        s.pop();
        i++;
    }
}

int main() {
    char input[100];
    cout << "Enter a string to reverse: ";
    cin.getline(input, 100);

    reverseString(input);

    cout << "Reversed string: " << input << endl;

    return 0;
}