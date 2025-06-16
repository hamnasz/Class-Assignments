#include <iostream>
#include <queue>
using namespace std;

int countQueue(queue<int> q) {
    return q.size();
}

int main() {
    queue<int> q;
    q.push(1); q.push(2); q.push(3);

    cout << "Total elements: " << countQueue(q) << endl;

    return 0;
}
