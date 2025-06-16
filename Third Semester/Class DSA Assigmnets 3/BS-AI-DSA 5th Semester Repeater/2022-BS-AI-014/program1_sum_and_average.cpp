#include <iostream>
#include <vector>
using namespace std;

void sumAndAverage() {
    vector<int> array1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = 0;

    for (int num : array1) {
        sum += num;
    }

    double average = sum / static_cast<double>(array1.size());

    cout << "Sum: " << sum << "\n";
    cout << "Average: " << average << "\n";
}

int main() {
    sumAndAverage();
    return 0;
}
