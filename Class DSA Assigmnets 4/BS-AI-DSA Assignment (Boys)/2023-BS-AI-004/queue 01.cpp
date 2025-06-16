#include <iostream>
#include <queue>
#include<stack>

using namespace std;

bool isPalindrome(queue<int>& q) {
    stack<int> s;
    queue<int> temp = q;

    // Push elements from the queue onto the stack
    while (!temp.empty()) {
        s.push(temp.front());
        temp.pop();
    }

    // Compare elements from the queue and stack
    while (!q.empty()) {
        if (q.front() != s.top()) {
            return false;
        }
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
        cout << "The queue is a palindrome." << endl;
    } else {
        cout << "The queue is not a palindrome." << endl;
    }

    return 0;
}