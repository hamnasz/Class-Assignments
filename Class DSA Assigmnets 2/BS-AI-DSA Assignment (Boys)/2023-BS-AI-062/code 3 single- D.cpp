#include <iostream>
using namespace std;
int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int evenCount = 0, oddCount = 0;

    for (int i = 0; i < 5; i++) {
        if (arr[i] % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }
    }

    cout << "Even Count: " << evenCount <<endl;
    cout << "Odd Count: " << oddCount <<endl;
    return 0;
}
