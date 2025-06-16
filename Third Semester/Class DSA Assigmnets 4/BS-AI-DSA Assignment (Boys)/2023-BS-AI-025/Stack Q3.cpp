#include <iostream>
#include <stack>
#include <string>
using namespace std;
int main() {
    string input;
    cout<<"Original string: ";
    cin>>input;
    stack<char> s;
    for (char c : input) {
        s.push(c);
    }
    cout << "Reversed string: ";
    while (!s.empty()) {
        cout << s.top();
        s.pop();
    }
    cout << endl;

    return 0;
}
