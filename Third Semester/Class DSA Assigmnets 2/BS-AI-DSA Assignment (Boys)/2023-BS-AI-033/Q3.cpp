#include <iostream>
using namespace std;

int main() {
    int values[5] = {3, 1, 4, 1, 5};
    int max = values[0];

    for (int i = 1; i < 5; i++) {
        if (values[i] > max) {
            max = values[i];
        }
    }
    
    cout << "Maximum value: " << max << endl;
    return 0;
}
