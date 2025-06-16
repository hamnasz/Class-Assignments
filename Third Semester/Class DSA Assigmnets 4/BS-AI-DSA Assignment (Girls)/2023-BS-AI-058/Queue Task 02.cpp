#include <iostream>
#include <queue>
using namespace std;

int countElements(queue<int> q) {
    int count = 0;
    queue<int> temp = q;
    while (!temp.empty()) {
        temp.pop();
        count++;
    }
    return count;
}

int main() {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << "Total elements in the queue: " << countElements(q) << endl;

    return 0;
}