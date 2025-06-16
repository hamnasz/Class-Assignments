#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(const string& str) 
{
    stack<char> s;

    for (char ch : str) 
	{
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch); 
        } 
		else if (ch == ')' || ch == '}' || ch == ']') 
		{
            if (s.empty()) return false;  
            char top = s.top();
            s.pop();
          
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) 
			{
                return false;
            }
        }
    }
    return s.empty(); 
}
int main() 
{
    string str;
    cout << "Enter a string of parentheses: ";
    cin >> str;

    if (isBalanced(str)) 
	{
        cout << "The parentheses are balanced." << endl;
    } else 
	{
        cout << "The parentheses are not balanced." << endl;
    }
    return 0;
}
