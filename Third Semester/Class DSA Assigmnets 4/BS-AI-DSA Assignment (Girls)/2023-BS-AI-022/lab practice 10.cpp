#include <iostream>
#include <queue>
using namespace std;

// Function to count the number of elements in the queue
int countQueueElements(queue<int> q) {
    int count = 0;

    // Iterate through the queue
    while (!q.empty()) {
        count++;         // Increment count for each element
        q.pop();         // Remove the element from the queue
    }

    return count;       // Return the total count
}

int main() {
    queue<int> q;

    // Adding elements to the queue
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);

    // Count the total number of elements in the queue
    int totalCount = countQueueElements(q);

    // Display the total count
    cout << "Total number of elements in the queue: " << totalCount << endl;

    // Verify that the original queue is still intact
    cout << "Elements in the queue after counting: ";
    while (!q.empty()) {
        cout << q.front() << " "; // Display elements of the original queue
        q.pop();                  // Pop the elements to display
    }
    cout << endl;

    return 0;
}
