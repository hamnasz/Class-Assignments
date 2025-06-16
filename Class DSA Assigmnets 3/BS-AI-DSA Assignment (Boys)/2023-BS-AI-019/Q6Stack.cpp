#include <iostream>
#include <stack>
#include <string>
using namespace std;

int palindrome(string word) 
{
    stack<char> Stack;

    // Push all characters of the word onto the stack
    for (char c : word) 
    {
        Stack.push(c);
    }

    // Check if the word reads the same forward and backward
    for (char c : word) 
    {
        if (c != Stack.top()) 
        {
            cout<<"It is not a Palindrome!";
            return 2;  // Not a palindrome
        }
        Stack.pop();
    }

    cout<<"It is a Palindrome!";
    return 1; // It is a palindrome
}

int main() 
{
    string word;
    cout << "Enter a word: ";
    cin >> word;

    palindrome(word);
    return 0;
}
