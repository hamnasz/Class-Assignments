#include <iostream>
#include <queue>
#include <stack>
using namespace std;

bool isPalindrome(queue<int> q) {
    stack<int> s;
    queue<int> copyQ = q;

    while (!copyQ.empty()) {
        s.push(copyQ.front());
        copyQ.pop();
    }

    while (!q.empty()) {
        if (q.front() != s.top()) return false;
        q.pop();
        s.pop();
    }
    return true;
}

int main() {
    queue<int> q;
    q.push(1); q.push(2); q.push(3); q.push(2); q.push(1);
    cout << (isPalindrome(q) ? "Palindrome" : "Not a Palindrome") << endl;

    return 0;
}
