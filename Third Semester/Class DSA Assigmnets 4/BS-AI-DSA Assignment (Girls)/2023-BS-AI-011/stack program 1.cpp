//- Implement a stack using an array and perform push and pop operations.
#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<int> s;

    // Push elements
    s.push(10);
    s.push(20);
    s.push(30);

    // Display elements by popping them
    cout << "Stack elements: ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    return 0;
}
