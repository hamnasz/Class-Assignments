#include <iostream>
using namespace std;

int main() {
    int arr[8] = {5, 3, 7, 3, 9, 3, 6, 3};
    int target = 3;
    int count = 0;

    for (int i = 0; i < 8; i++) {
        if (arr[i] == target) {
            count++;
        }
    }

    cout << "The number " << target << " appears " << count << " times." << endl;
    return 0;
}
