#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    // Get the word from the user
    string word;
    cout << "Enter a word: ";
    cin >> word;

    // Create a stack to hold the characters
    stack<char> charStack;

    // Push each character of the word onto the stack
    for (char c : word) {
        charStack.push(c);
    }

    // Check if the word is a palindrome
    bool isPalindrome = true;
    for (char c : word) {
        if (c != charStack.top()) {
            isPalindrome = false;
            break;
        }
        charStack.pop(); // Remove the top character after comparison
    }

    // Display the result
    if (isPalindrome) {
        cout << word << " is a palindrome." << endl;
    } else {
        cout << word << " is not a palindrome." << endl;
    }

    return 0;
}

