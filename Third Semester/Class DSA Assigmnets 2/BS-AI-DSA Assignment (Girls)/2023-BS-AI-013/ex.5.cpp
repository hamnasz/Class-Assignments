#include <iostream>
#include <vector>
using namespace std;
int main() {
    std::vector<int> numbers;
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    std::cout << "Vector elements: ";
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}

