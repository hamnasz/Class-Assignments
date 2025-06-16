#include <iostream>
#include <stack>
#include <string>
using namespace std;
int main() 
{
    stack<string> history;  
    string command, page;

    while (true) 
	{
        cout << "\nEnter command (visit, back, exit): ";
        cin >> command;

        if (command == "visit") 
		{
            cout << "Enter page URL: ";
            cin >> page;
            history.push(page);
            cout << "Visited " << page << endl;
        }
        else if (command == "back") 
		{
            if (!history.empty()) 
			{
                cout << "Going back from " << history.top() << endl;
                history.pop();
                if (!history.empty()) 
				{
                    cout << "Now on " << history.top() << endl;
                } 
				else 
				{
                    cout << "No more history to go back to." << endl;
                }
            } 
			else 
			{
                cout << "No history to go back to." << endl;
            }
        }
        else if (command == "exit") 
		{
            break;
        }
        else 
		{
            cout << "Invalid command. Try 'visit', 'back', or 'exit'." << endl;
        }
    }
    return 0;
}
