#include <iostream>
#include <queue>
#include <stack>

bool isPalindrome(std::queue<int> q) {
    std::stack<int> s;
    std::queue<int> qCopy = q;

    // Push elements of the queue into the stack
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }

    // Compare elements of the original queue with the stack
    while (!qCopy.empty()) {
        if (qCopy.front() != s.top()) {
            return false;
        }
        qCopy.pop();
        s.pop();
    }

    return true;
}

int main() {
    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(2);
    q.push(1);

    if (isPalindrome(q)) {
        std::cout << "The queue is a palindrome." << std::endl;
    } else {
        std::cout << "The queue is not a palindrome." << std::endl;
    }

    return 0;
}
