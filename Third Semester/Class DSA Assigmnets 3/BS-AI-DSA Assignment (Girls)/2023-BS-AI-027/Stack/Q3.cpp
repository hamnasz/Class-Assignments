#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> history;
    string command, url;

    while (true)
	 {
        cout << "\nEnter command (visit, back, exit): ";
        cin >> command;

        if (command == "visit")
		 {
            cout << "Enter URL: ";
            cin >> url;
            history.push(url);
            cout << "Visited " << url << endl;
        } 
        else if (command == "back") 
		{
            if (history.empty())
			 {
                cout << "No pages in history." << endl;
            } 
			else 
			{
                cout << "Going back from " << history.top() << endl;
                history.pop();
                if (!history.empty()) 
				{
                    cout << "Now at " << history.top() << endl;
                } else 
				{
                    cout << "No more pages in history." << endl;
                }
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

