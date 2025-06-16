#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> numbers;
    numbers.push_back(3);
    numbers.push_back(10);
    numbers.push_back(15);
    cout << "Vector elements: ";
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
	cout << endl;
    return 0;
}

