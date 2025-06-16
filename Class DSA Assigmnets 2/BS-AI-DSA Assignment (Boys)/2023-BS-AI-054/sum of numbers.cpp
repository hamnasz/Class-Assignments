#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> numbers;
    int num, sum = 0;

    cout << "Enter numbers (type -1 to stop):" << endl;
    while (true) {
        cin >> num;
        if (num == -1) {
            break;
        }
        numbers.push_back(num);
    }

    for (int number : numbers) {
        sum += number;
    }

    cout << "The sum of the numbers is: " << sum << endl;
    return 0;
}
