#include <iostream>
#include <queue>
#include <stack>
using namespace std;

bool isPalindrome(queue<int> q) {
    stack<int> s;
    int size = q.size();

    // Push all elements to stack
    for (int i = 0; i < size; i++) {
        s.push(q.front());
        q.push(q.front());
        q.pop();
    }

    // Check for palindrome
    for (int i = 0; i < size; i++) {
        if (q.front() != s.top()) return false;
        q.pop();
        s.pop();
    }
    return true;
}

int main() {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(2);
    q.push(1);

    if (isPalindrome(q)) {
        cout << "Queue is a palindrome" << endl;
    } else {
        cout << "Queue is not a palindrome" << endl;
    }
    return 0;
}