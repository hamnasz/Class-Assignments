#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int palindrome(queue<int> q) {
    stack<int> s;
    
    for (int i = 0; i < q.size(); i++) {
        s.push(q.front());
        q.push(q.front());  
        q.pop();
    }

    for (int i = 0; i < q.size(); i++) {
        if (q.front() != s.top()) {
            cout<<"It is not a Palindrome!";
            return 2;
        }
        q.pop();
        s.pop();
    }
    cout<<"It is a Palindrome!";
    return 1;
}

int main() {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(1);

    palindrome(q);

    return 0;
}
