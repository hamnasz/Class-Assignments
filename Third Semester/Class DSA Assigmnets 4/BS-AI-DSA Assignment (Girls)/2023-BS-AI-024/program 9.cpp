#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// Function to check if the elements in the queue form a palindrome
bool isPalindrome(queue<int> q) {
    stack<int> s;
    queue<int> originalQueue = q;  // Make a copy of the original queue

    // Push all elements of the queue onto a stack
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }

    // Compare elements of the stack with the elements of the original queue
    while (!originalQueue.empty()) {
        if (originalQueue.front() != s.top()) {
            return false;  // If any mismatch is found, it is not a palindrome
        }
        originalQueue.pop();
        s.pop();
    }

    return true;  // If all elements match, it is a palindrome
}

int main() {
    queue<int> q;

    // Example input: {1, 2, 3, 2, 1}
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(2);
    q.push(1);

    // Check if the queue elements form a palindrome
    if (isPalindrome(q)) {
        cout << "The elements in the queue form a palindrome." << endl;
    } else {
        cout << "The elements in the queue do not form a palindrome." << endl;
    }

    return 0;
}
