#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

bool isPalindrome(queue<int> q) {
    vector<int> elements;

    // Transfer elements from queue to vector
    while (!q.empty()) {
        elements.push_back(q.front());
        q.pop();
    }

    // Check if the elements in the vector form a palindrome
    int n = elements.size();
    for (int i = 0; i < n / 2; i++) {
        if (elements[i] != elements[n - 1 - i]) {
            return false; // Mismatch found
        }
    }
    
    return true; // All elements matched
}

int main() {
    queue<int> q;
    int n, value;

    cout << "Enter the number of elements in the queue: ";
    cin >> n;

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        q.push(value);
    }

    if (isPalindrome(q)) {
        cout << "The queue forms a palindrome." << endl;
    } else {
        cout << "The queue does not form a palindrome." << endl;
    }

    return 0;
}
