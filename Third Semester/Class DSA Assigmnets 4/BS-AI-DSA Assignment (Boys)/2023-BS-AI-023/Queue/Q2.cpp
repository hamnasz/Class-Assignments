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
    q.push(11);
    q.push(22);
    q.push(31);
    q.push(44);
    q.push(55);

    int totalElements = countElements(q);
    cout << "Total number of elements in the queue: " << totalElements << "\n";

    return 0;
}
