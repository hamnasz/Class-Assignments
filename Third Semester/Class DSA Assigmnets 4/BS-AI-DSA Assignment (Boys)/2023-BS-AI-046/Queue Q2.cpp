#include <iostream>
#include <queue>
using namespace std;
int countQueueElements(queue<int> q) {
    int count = 0;
    while (!q.empty()) {
        count++;
        q.pop();
    }
    return count;
}
int main() {
    queue<int> q;
    q.push(11);
    q.push(3);
    q.push(31);
    q.push(98);
    cout << "Total number of elements in the queue: " << countQueueElements(q) << endl;
    return 0;
}
