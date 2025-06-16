#include <iostream>
#include <vector>
using namespace std;
int main() {
    std::vector<string> car;
    car.push_back("honda");
    car.push_back("toyota");
    car.push_back("suzuki");
    std::cout << "Vector elements: ";
    for (int i = 0; i < car.size(); i++) {
        std::cout << car[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}

