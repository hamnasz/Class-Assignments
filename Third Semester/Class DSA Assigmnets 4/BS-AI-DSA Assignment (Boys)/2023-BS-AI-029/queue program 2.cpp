#include <iostream>
#include <queue>

using namespace std;

// Function to count the number of elements in the queue
int countElements(queue<int> q) {
    int count = 0;

    // Use a temporary queue to hold elements while counting
    while (!q.empty()) {
        count++;        // Increment the count
        q.pop();        // Remove the front element from the queue
    }

    return count; // Return the total count
}

int main() {
    queue<int> q;

    // Sample input for the queue
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);

    // Count the number of elements in the queue
    int totalCount = countElements(q);
    
    cout << "Total number of elements in the queue: " << totalCount << endl;

    return 0;
}
