#include <iostream>
#include <queue>
#include <stack>
using namespace std;

bool isPalindrome(queue<int> q) {
    stack<int> s;
    int size = q.size();
    for (int i = 0; i < size / 2; i++) {
        s.push(q.front());
        q.pop();
    }
    if (size % 2 != 0) q.pop(); // Remove middle element for odd-sized queue
    while (!q.empty()) {
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
    cout << "Is the queue a palindrome? " << (isPalindrome(q) ? "Yes" : "No") << endl;

    return 0;
}