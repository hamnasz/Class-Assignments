#include <iostream>
#include <queue>
#include <stack>
using namespace std;

bool isPalindrome(queue<int> q) {
    stack<int> s;
    queue<int> originalQueue = q;

    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }

    while (!originalQueue.empty()) {
        if (originalQueue.front() != s.top()) {
            return false;
        }
        originalQueue.pop();
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
        cout << "The queue forms a palindrome." << endl;
    } else {
        cout << "The queue does not form a palindrome." << endl;
    }

    return 0;
}
