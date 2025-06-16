#include <iostream>
#include <queue>
#include <stack>
using namespace std;
bool checkPalindrome(queue<int> Queue) {
    stack<int> Stack;
    int length = Queue.size();

    for (int i = 0; i < length; i++) {
        Stack.push(Queue.front());
        Queue.push(Queue.front());
        Queue.pop();
    }

    for (int i = 0; i < length; i++) {
        if (Queue.front() != Stack.top()) {
            return false;
        }
        Queue.pop();
        Stack.pop();
    }
    return true;
}

int main() {
    queue<int> numQueue;
    numQueue.push(1);
    numQueue.push(2);
    numQueue.push(3);
    numQueue.push(2);
    numQueue.push(1);

    if (checkPalindrome(numQueue)) {
        cout << "The queue is a palindrome." << endl;
    } else {
        cout << "The queue is not a palindrome." << endl;
    }
    return 0;
}
