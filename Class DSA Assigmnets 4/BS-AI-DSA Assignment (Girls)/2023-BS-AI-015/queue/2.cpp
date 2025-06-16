#include <iostream>
#include <queue>
using namespace std;
int main() {
    queue<int> q;
    q.push(45);
    q.push(35);
    q.push(30);
    cout << "elements in queue: " << q.size() << endl;
    return 0;
}