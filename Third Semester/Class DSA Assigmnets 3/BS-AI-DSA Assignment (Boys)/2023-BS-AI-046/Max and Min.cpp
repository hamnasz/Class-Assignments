#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int array[5] = {4, 9, 1, 7, 5};
    int max_value = *max_element(array, array + 5);
    int min_value = *min_element(array, array + 5);

    cout << "Max: " << max_value << ", Min: " << min_value << endl;
    return 0;
}
