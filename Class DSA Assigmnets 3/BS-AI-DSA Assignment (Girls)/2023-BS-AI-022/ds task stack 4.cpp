#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

int evaluatePostfix(const string& expression) 
{
    stack<int> s;
    stringstream ss(expression);
    string token;

    while (ss >> token) 
	{
        if (isdigit(token[0])) 
		{  
            s.push(stoi(token));
        } 
		else 
		{  
            int operand2 = s.top(); s.pop();
            int operand1 = s.top(); s.pop();
            
            if (token == "+") s.push(operand1 + operand2);
            else if (token == "-") s.push(operand1 - operand2);
            else if (token == "*") s.push(operand1 * operand2);
            else if (token == "/") s.push(operand1 / operand2);
        }
    }
    return s.top(); 
}

int main() 
{
    string expression;
    cout << "Enter a postfix expression (e.g., '5 1 2 + 4 * + 3 -'): ";
    getline(cin, expression);

    int result = evaluatePostfix(expression);
    cout << "Result: " << result << endl;

    return 0;
}
