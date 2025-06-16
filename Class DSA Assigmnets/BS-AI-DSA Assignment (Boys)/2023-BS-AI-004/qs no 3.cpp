#include <iostream>
using namespace std;
int main() {
    bool flags[5] = {true, false, true, false, true};

    cout << "Boolean Array: ";
    for (int i = 0; i < 5; i++) {
       cout << (flags[i] ? "True" : "False") << " ";
    }
  cout <<endl;

    return 0;
}