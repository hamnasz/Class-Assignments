#include <iostream>
#include <queue>
using namespace std;

int count(queue<int> q) {
    int count = 0;

    int size = q.size();
    for (int i = 0; i < size; ++i) {
        q.pop();
        count++;
    }

    return count; 
}

int main() {
    queue<int> q;
    q.push(19);
    q.push(33);
    q.push(52);
    q.push(16);
    q.push(56);

    cout<<"Total Number of Elements: "<< count(q);

    return 0;
}
