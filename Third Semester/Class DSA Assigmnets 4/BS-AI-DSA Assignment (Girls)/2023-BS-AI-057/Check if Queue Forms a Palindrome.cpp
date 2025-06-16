 #include <iostream>
#include <queue>
#include <stack>
using namespace std;

bool isPalindrome(queue<int> q) {
    stack<int> s;
    int n = q.size();
    for (int i = 0; i < n; i++) {
        int front = q.front();
        s.push(front);
        q.pop();
        q.push(front);
    }
    for (int i = 0; i < n; i++) {
        int front = q.front();
        if (front != s.top()) return false;
        q.pop();
        s.pop();
    }
    return true;
}

int main() {
    queue<int> q;
    q.push(1); q.push(2); q.push(3); q.push(2); q.push(1);

    if (isPalindrome(q)) cout << "Queue is a palindrome\n";
    else cout << "Queue is not a palindrome\n";

    return 0;
}
