#include <iostream>
using namespace std;
int main() {
    int numbers[5];
    std::cout << "Enter 5 integers: ";
    for (int i = 0; i < 5; i++) {
        std::cin >> numbers[i];
    }
    std::cout << "You entered: ";
    for (int i = 0; i < 5; i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl; 
    return 0;
}

