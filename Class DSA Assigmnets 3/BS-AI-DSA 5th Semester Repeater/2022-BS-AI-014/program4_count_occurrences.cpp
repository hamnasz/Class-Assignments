#include <iostream>
#include <vector>
using namespace std;

void countOccurrences() {
    vector<char> array4 = {'a', 'b', 'c', 'a', 'd', 'a', 'b'};
    char char_to_count;

    cout << "Enter character to count: ";
    cin >> char_to_count;

    int count = std::count(array4.begin(), array4.end(), char_to_count);
    cout << "Character '" << char_to_count << "' occurs " << count << " times.\n";
}

int main() {
    countOccurrences();
    return 0;
}
