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
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);

    cout << "Total number in queue: " << countElements(q) << endl;

    return 0;
}
