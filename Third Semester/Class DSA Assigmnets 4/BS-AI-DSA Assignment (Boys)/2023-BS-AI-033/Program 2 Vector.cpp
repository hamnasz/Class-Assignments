#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 2, 4, 5, 1, 6, 3};

    // Sort the vector
    std::sort(vec.begin(), vec.end());

    // Remove duplicates
    auto last = std::unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());

    // Display the vector without duplicates
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
