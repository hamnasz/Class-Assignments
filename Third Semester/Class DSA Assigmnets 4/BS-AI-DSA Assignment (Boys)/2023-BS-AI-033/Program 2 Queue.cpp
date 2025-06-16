#include <iostream>
#include <queue>

int countElements(std::queue<int> q) {
    int count = 0;
    while (!q.empty()) {
        count++;
        q.pop();
    }
    return count;
}

int main() {
    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    std::cout << "Total number of elements in the queue: " << countElements(q) << std::endl;

    return 0;
}
