//- Implement a simple program that counts the total number of elements in a queue without modifying the queue's order.

#include <iostream>
#include <queue>

using namespace std;

int countElements(queue<int> q) {
    int count = 0;
    queue<int> tempQ = q;

    while (!tempQ.empty()) {
        tempQ.pop();
        count++;
    }

    return count;
}

int main() {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    int numElements = countElements(q);
    cout << "Number of elements in the queue: " << numElements << endl;

    return 0;
}