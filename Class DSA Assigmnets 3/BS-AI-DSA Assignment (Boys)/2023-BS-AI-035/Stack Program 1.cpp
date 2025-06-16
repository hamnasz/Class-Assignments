#include <iostream>
#include <stack>
using namespace std;

int main() {
    string inputWord;
    cout << "Please enter a word: ";
    cin >> inputWord;
    stack<char> charStack;
    
    for(char character : inputWord) charStack.push(character);
    
    string reversedWord;
    while(!charStack.empty()) {
        reversedWord += charStack.top();
        charStack.pop();
    }
    
    if(inputWord == reversedWord) 
        cout << inputWord << " is a palindrome." << endl;
    else 
        cout << inputWord << " is not a palindrome." << endl;
    
    return 0;
}
