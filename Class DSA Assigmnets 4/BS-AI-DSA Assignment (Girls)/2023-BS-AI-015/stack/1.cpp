#include <iostream>
#include <stack>
using namespace std;
int main() {
    stack<int> s;
    s.push(5);
    s.push(10);
    s.push(15);
    cout << "Top element: " << s.top() << endl;
    s.pop();
    cout << "Top element after pop: " << s.top() << endl;
}