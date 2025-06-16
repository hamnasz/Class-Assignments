#include <iostream>
#include <queue>
#include <stack>
using namespace std;
bool isPalindrome(queue<int> q) {
    stack<int> s;
    queue<int> original = q;
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }
    while (!original.empty()) {
        if (original.front() != s.top()) {
            return false;
        }
        original.pop();
        s.pop();
    }
    return true;
}
int main() {
    queue<int> q;
    q.push(4);
    q.push(3);
    q.push(1);
    q.push(3);
    q.push(4);

    if (isPalindrome(q)) {
        cout << "The queue is a palindrome." << endl;
    } else {
        cout << "The queue is not a palindrome." << endl;
    }

    return 0;
}
