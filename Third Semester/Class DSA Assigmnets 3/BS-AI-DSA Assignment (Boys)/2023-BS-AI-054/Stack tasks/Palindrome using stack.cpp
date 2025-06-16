#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    string word;
    cout << "Enter a word: ";
    cin >> word;

    stack<char> charStack;
    
  
    for (char c : word) {
        charStack.push(c);
    }

    // Check if the word is a palindrome by comparing characters
    bool isPalindrome = true;
    for (char c : word) {
        
        if (c != charStack.top()) {
            isPalindrome = false;
            break;
        }
        charStack.pop();
    }

  
    if (isPalindrome) {
        cout << word << " is a palindrome." << endl;
    } else {
        cout << word << " is not a palindrome." << endl;
    }

    return 0;
}
