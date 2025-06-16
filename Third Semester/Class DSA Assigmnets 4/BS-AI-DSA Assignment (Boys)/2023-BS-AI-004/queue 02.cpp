#include <iostream>
#include <queue>

using namespace std;

int countElements(queue<int>& q) {
    queue<int> temp = q;
    int count = 0;

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

    int count = countElements(q);
    cout << "Number of elements in the queue: " << count << endl;

    return 0;
}