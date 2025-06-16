#include <iostream>
#include <list>
#include <tuple>
using namespace std;

int main() {
    list<tuple<string, string>> tasks;
    tasks.push_back({"High", "Do laundry"});
    tasks.push_back({"Medium", "Read book"});

    tasks.sort([](const auto& a, const auto& b) {
        return get<0>(a) > get<0>(b);
    });

    for (const auto& task : tasks) {
        cout << "[" << get<0>(task) << "] " << get<1>(task) << endl;
    }
    return 0;
}
