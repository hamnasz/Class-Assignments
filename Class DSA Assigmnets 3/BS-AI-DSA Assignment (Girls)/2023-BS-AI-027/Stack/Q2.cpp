#include <iostream>
#include <stack>
using namespace std;

bool isBalanced(const string& str) 
{
    stack<char> s;

    for (int i = 0; i < str.length(); i++) 
	{
        char ch = str[i];

        // If it's an opening bracket, push it onto the stack
        if (ch == '(' || ch == '{' || ch == '[') 
		{
            s.push(ch);
        } 
		else if (ch == ')' || ch == '}' || ch == ']') 
		{
            // If it's a closing bracket, check for balance
            if (s.empty()) return false;  // No matching opening bracket

            char top = s.top();
            s.pop();

            // Check if the top of the stack matches the corresponding opening bracket
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
        cout << "The string is balanced." << endl;
    } 
	else 
	{
        cout << "The string is not balanced." << endl;
    }

    return 0;
}

