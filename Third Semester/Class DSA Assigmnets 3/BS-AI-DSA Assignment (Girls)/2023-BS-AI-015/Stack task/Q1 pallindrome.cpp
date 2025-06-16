#include <iostream>
#include <stack>
#include <string>
using namespace std;
int main() {
    string word;
    cout<<"enter word: ";
    cin>>word;
    stack<char> w;
    for(char c : word) {
        w.push(c);
    }
    string rWord;
    while(!w.empty()) {
        rWord += w.top();
        w.pop();
    }
    if(word == rWord) {
        cout<<word<<" is a palindrome"<<endl;
    } else{
        cout<<word<<" is not a palindrome"<<endl;
    }
}
