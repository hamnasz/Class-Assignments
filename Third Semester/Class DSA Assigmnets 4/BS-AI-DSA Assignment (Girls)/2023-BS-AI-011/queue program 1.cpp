//Write a program to check if the elements in a queue form a palindrome.A palindrome reads the same forwards and backwards (e.g., `{1, 2, 3, 2,1}`)
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

bool isPalindrome(queue<int> q) {
    stack<int> s;

    // Push elements from the queue to the stack
    for (int i = q.size(); i > 0; i--) {
        s.push(q.front());
        q.pop();
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