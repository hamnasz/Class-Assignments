#include <iostream>
#include <queue>
using namespace std;
int main() 
{
    queue<string> customerQueue;
    customerQueue.push("John");
    customerQueue.push("Emma");
    customerQueue.push("Michael");

    cout << "Processing the queue:" << endl;
    while (!customerQueue.empty()) {
        cout << customerQueue.front() << " is being served." << endl;
        customerQueue.pop();
    }
    return 0;
}
