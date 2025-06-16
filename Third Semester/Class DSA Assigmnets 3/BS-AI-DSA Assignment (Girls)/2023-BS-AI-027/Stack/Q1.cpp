#include <iostream>
#include <stack>
using namespace std;

bool isPalindrome(const string& word) 
{
    stack<char> s;

    // Push each character of the word onto the stack
    for (int i = 0; i < word.length(); i++) 
	{
        s.push(word[i]);
    }

    // Check if the word reads the same forward and backward
    for (int i = 0; i < word.length(); i++) 
	{
        if (word[i] != s.top()) 
		{
            return false;  // If characters don’t match, it's not a palindrome
        }
        s.pop();
    }

    return true;
}

int main()
 {
    string word;
    cout << "Enter a word: ";
    cin >> word;

    if (isPalindrome(word)) 
	{
        cout << word << " is a palindrome." << endl;
    } else 
	{
        cout << word << " is not a palindrome." << endl;
    }

    return 0;
}

