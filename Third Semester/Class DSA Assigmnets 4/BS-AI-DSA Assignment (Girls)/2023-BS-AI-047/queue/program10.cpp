#include <iostream>
#include <queue>
#include <stack>
using namespace std;

bool isPalindrome(queue<int> q) {
    stack<int> s;
    int size = q.size();

    // Push all elements of the queue onto a stack
    for (int i = 0; i < size; i++) {
        s.push(q.front());
        q.push(q.front());  // Re-enqueue the element
        q.pop();
    }

    // Check if elements form a palindrome
    for (int i = 0; i < size; i++) {
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
        cout << "The queue forms a palindrome." << endl;
    } else {
        cout << "The queue does not form a palindrome." << endl;
    }

    return 0;
}
