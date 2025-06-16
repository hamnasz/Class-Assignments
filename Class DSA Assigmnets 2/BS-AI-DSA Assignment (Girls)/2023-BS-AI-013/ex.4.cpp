#include <iostream>
using namespace std;
int main() {
    int matrix[2][3];
    std::cout << "Enter 6 integers (2 rows and 3 columns):" << std::endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            std::cin >> matrix[i][j];
        }
    }
    std::cout << "You entered:" << std::endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl; 
    }
    return 0;
}

