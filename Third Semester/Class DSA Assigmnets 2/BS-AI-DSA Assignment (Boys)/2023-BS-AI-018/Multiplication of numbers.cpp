#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> numbers;
    int num;
    long long product = 1; // Initialize product to 1

    cout << "Enter numbers (type -1 to stop):" << endl;

    while (true) {
        cin >> num;
        if (num == -1) {
            break;
        }
        numbers.push_back(num);
    }

    for (int number : numbers) {
        product *= number;  // Multiply each number
    }

    cout << "The product of the numbers is: " << product << endl;
    return 0;
}
