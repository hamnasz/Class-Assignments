#include <iostream>
#include <queue>
#include <stack>

using namespace std;

// Function to check if the queue forms a palindrome
bool isPalindrome(queue<int> q) {
    stack<int> s;

    // Transfer elements from queue to stack
    while (!q.empty()) {
        int elem = q.front();
        s.push(elem);  // Push onto the stack
        q.pop();       // Remove from the queue
    }

    // Check elements from the queue and stack
    while (!s.empty()) {
        if (s.top() != q.front()) {
            return false; // Not a palindrome
        }
        s.pop();          // Pop from the stack
        q.pop();         // Remove from the queue
    }

    return true; // All elements matched
}

int main() {
    queue<int> q;

    // Sample input for the queue
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(2);
    q.push(1);

    // Check if the queue forms a palindrome
    if (isPalindrome(q)) {
        cout << "The queue forms a palindrome." << endl;
    } else {
        cout << "The queue does not form a palindrome." << endl;
    }

    return 0;
}

