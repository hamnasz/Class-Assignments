#include <iostream>
#include <queue>
using namespace std;

int countElements(queue<int> q) {
    int count = 0;
    while (!q.empty()) {
        count++;
        q.pop();
    }
    return count;
}

int main() {
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);

    cout << "Total number of elements in the queue: " << countElements(q) << endl;

    return 0;
}
