#include<iostream>
#include<stack>
using namespace std;
int main(){
	string word;
	cout<<"Enter your word: ";
	cin>>word;
	stack<char> x;
	for(char c : word) x.push(c);
    string rev;
    while(!x.empty()) {
        rev += x.top();
        x.pop();
    }
    if(word == rev) 
	cout <<"Your word is a palindrome."<<endl;
    else 
	cout<<"Your word is not a palindrome."<<endl;
}