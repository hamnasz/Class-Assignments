#include <iostream>
#include <stack>
#include <string>

bool isPalindrome(const std::string& word) {
    std::stack<char> charStack;
    int length = word.length();

    // Push all characters of the word onto the stack
    for (int i = 0; i < length; ++i) {
        charStack.push(word[i]);
    }

    // Pop characters from the stack and compare with the original word
    for (int i = 0; i < length; ++i) {
        if (charStack.top() != word[i]) {
            return false; // If any character doesn't match, it's not a palindrome
        }
        charStack.pop();
    }
    return true;}

int main() {
    std::string word;
    std::cout << "Enter a word: ";
    std::cin >> word;

    
    if (isPalindrome(word)) {
        std::cout << word << " is a palindrome." << std::endl;
    } else {
        std::cout << word << " is not a palindrome." << std::endl;
    }

    return 0;
}
