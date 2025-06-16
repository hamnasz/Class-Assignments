#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<string> grocery;
    grocery.push_back("vegetables");
    grocery.push_back("fruits");
    grocery.push_back("milk");
    cout << "Vector elements: ";
    for (int i = 0; i < grocery.size(); i++) {
        cout << grocery[i] << " ";
    }
	cout << endl;
    return 0;
}

