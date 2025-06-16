#include <iostream>
#include <queue>
using namespace std;
int main() {
    queue<string> line;
    line.push("person 1");
    line.push("person 2");
    line.push("person 3");
	cout << "entering:" << endl;
    while (!line.empty()) {
        cout << line.front() << " is entering." << endl;
        line.pop();
    }
}