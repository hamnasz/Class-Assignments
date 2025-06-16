#include <iostream>
#include <stack>
#include <string>
using namespace std;
int main() 
{
    string word;
    cout << "Enter a word: ";
    cin >> word;
    stack<char> s;
    for(char c : word) 
	{
        s.push(c);
    }
    string reversedWord;
    while(!s.empty()) 
	{
        reversedWord += s.top();
        s.pop();
    }
    if(word == reversedWord) 
	{
        cout << word << " is a palindrome." << endl;
    } else 
	{
        cout << word << " is not a palindrome." << endl;
    }

    return 0;
}
