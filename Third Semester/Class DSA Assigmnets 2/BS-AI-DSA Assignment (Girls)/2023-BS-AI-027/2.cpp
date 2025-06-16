#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 5, 40, 30};
    int maxVal = arr[0];
    for (int i = 1; i < 5; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }
    cout << "Maximum element: " << maxVal << endl;
    return 0;
}
