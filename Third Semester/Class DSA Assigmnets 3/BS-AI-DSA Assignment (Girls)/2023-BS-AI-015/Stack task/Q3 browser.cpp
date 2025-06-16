#include <iostream>
#include <stack>
using namespace std;
int main() {
    stack<string> browse;
    int option;
    string pg;
    while(true) {
        cout << "1.visit new page\n";
        cout << "2.go back\n";
        cout << "3.exit\n";
        cout << "choose an option: ";
        cin >> option;

        if(option == 1) {
            cout << "enter name of page: ";
            cin >> pg;
            browse.push(pg);
            cout << "opened: " << pg << endl;
        } 
		else if(option == 2) {
            if(browse.empty()) {
                cout << "No previous page \n";
            } else {
                cout << "Going back from: " << browse.top() << endl;
                browse.pop();
            }
        } 
		else if(option == 3) {
            break;
        } else {
            cout << "invalid choice\n";
        }
    }
}
