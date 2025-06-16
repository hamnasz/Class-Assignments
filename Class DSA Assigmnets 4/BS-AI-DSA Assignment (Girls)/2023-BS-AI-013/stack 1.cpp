#include <iostream>
#include <stack>
using namespace std;
int main() {
    stack<int> s;
    s.push(50);
    s.push(40);
    s.push(30);
    cout << "Top element: " << s.top() << endl;
    s.pop();
    cout << "Top element after pop: " << s.top() << endl;
}