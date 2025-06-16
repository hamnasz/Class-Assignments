#include <iostream>
#include <queue>
using namespace std;

int countElements(queue<int> q) {
    int count = 0;

    // Count elements while preserving the queue
    while (!q.empty()) {
        count++;
        q.pop(); // Remove the element from the queue
    }

    return count;
}

int main() {
    queue<int> q;
    int n, value;

    cout << "Enter the number of elements in the queue: ";
    cin >> n;

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        q.push(value);
    }

    int totalCount = countElements(q);
    cout << "Total number of elements in the queue: " << totalCount << endl;

    return 0;
}
