#include <iostream>
#include <queue>
using namespace std;
int main() {
    queue<int> q;
    q.push(3);
    q.push(5);
    q.push(4);
    cout << "elements in queue: " << q.size() << endl;
    return 0;
}