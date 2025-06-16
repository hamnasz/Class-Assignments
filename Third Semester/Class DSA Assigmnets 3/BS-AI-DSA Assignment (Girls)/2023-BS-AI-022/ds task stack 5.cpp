#include <iostream>
#include <stack>
#include <string>
using namespace std;
int main() 
{
    stack<string> actions;  
    string command, action;

    while (true) 
	{
        cout << "\nEnter command (type, undo, exit): ";
        cin >> command;

        if (command == "type") 
		{
            cout << "Enter text to add: ";
            cin.ignore();
            getline(cin, action);
            actions.push(action);
            cout << "Action added: " << action << endl;
        }
        else if (command == "undo") 
		{
            if (!actions.empty()) 
			{
                cout << "Undoing last action: " << actions.top() << endl;
                actions.pop();
            } 
			else 
			{
                cout << "No actions to undo." << endl;
            }
        }
        else if (command == "exit") 
		{
            break;
        }
        else 
		{
            cout << "Invalid command. Try 'type', 'undo', or 'exit'." << endl;
        }

        cout << "\nCurrent document state:\n";
        stack<string> temp = actions;  
        string document;
        while (!temp.empty()) 
		{
            document = temp.top() + "\n" + document;
            temp.pop();
        }
        cout << document;
    }

    return 0;
}
