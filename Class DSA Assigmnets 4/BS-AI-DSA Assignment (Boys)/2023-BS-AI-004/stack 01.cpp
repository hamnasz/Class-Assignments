#include <iostream>
#include <stack>

using namespace std;

void push(stack<int>& s, int x) {
    s.push(x);
    cout << x << " pushed to stack\n";
}

int pop(stack<int>& s) {
    if (s.empty()) {
        cout << "Stack empty\n";
        return -1;
    }
    int x = s.top();
    s.pop();
    return x;
}

int main() {
    stack<int> s;
    push(s, 10);
    push(s, 20);
    push(s, 30);

    cout << pop(s) << " popped from stack\n";
    cout << pop(s) << " popped from stack\n";
    cout << pop(s) << " popped from stack\n";

    return 0;
}