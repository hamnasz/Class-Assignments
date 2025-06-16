#include<iostream>
#include<stack>
using namespace std;
int main(){
	stack<string> browser;
	string choice;
	cout<<"Enter your choice(Visit,Back,Exit): ";
	cin>>choice;
	while (true) {
	if(choice=="Visit"){
		string name;
		cout<<"Enter name of website: ";
		cin>>name;
		browser.push(name);
		 cout << "You visited: " << name << endl;
	}
	else if (choice == "Back") {
            if (!browser.empty()) {
                cout << "Going back from: " << browser.top() << endl;
                browser.pop();
                if (!browser.empty()) {
                    cout << "Current page: " << browser.top() << endl;
                } else {
                    cout << "No more history. You're on a blank page.\n";
                }
            } else {
                cout << "No history to go back to.\n";
            }

        } else if (choice == "Exit") {
            break;

        } else {
            cout << "Invalid command. Please enter 'visit', 'back', or 'exit'.\n";
        }
    }

    return 0;
}
