#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<char> letters = {'a', 'b', 'c'};

    for (char letter : letters) {
        cout << letter << " ";
    }
    cout << endl;
    return 0;
}
