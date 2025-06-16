#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec;

    for (int i = 1; i <= 5; ++i) {
        vec.push_back(i);
        std::cout << "After inserting " << i << ":" << std::endl;
        std::cout << "Size: " << vec.size() << std::endl;
        std::cout << "Capacity: " << vec.capacity() << std::endl;
    }

    return 0;
}
