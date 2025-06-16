#include <iostream>
#include <string>
using namespace std;

// Node structure for the linked list
struct Node {
    string songTitle;
    Node* next;
};

// Class for the playlist
class Playlist {
private:
    Node* head;

public:
    Playlist() : head(nullptr) {}

    // Function to add a song at the beginning
    void addSongAtBeginning(const string& title) {
        Node* newNode = new Node{title, head};
        head = newNode;
        cout << "Added song at the beginning: " << title << endl;
    }

    // Function to add a song at the end
    void addSongAtEnd(const string& title) {
        Node* newNode = new Node{title, nullptr};
        if (!head) {
            head = newNode; // If the list is empty
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode; // Add to the end
        }
        cout << "Added song at the end: " << title << endl;
    }

    // Function to add a song at a specific position
    void addSongAtPosition(const string& title, int position) {
        if (position < 1) {
            cout << "Invalid position. Please enter a position greater than 0." << endl;
            return;
        }

        Node* newNode = new Node{title, nullptr};

        if (position == 1) {
            newNode->next = head; // Insert at the beginning
            head = newNode;
            cout << "Added song at position " << position << ": " << title << endl;
            return;
        }

        Node* current = head;
        for (int i = 1; i < position - 1 && current; i++) {
            current = current->next;
        }

        if (!current) {
            cout << "Position out of bounds. Adding at the end instead." << endl;
            addSongAtEnd(title);
            return;
        }

        newNode->next = current->next;
        current->next = newNode; // Insert at the specified position
        cout << "Added song at position " << position << ": " << title << endl;
    }

    // Function to remove a song
    void removeSong(const string& title) {
        if (!head) {
            cout << "The playlist is empty." << endl;
            return;
        }

        Node* current = head;
        Node* prev = nullptr;

        while (current && current->songTitle != title) {
            prev = current;
            current = current->next;
        }

        if (!current) {
            cout << "Song '" << title << "' not found in the playlist." << endl;
            return;
        }

        if (prev) {
            prev->next = current->next; // Bypass the current node
        } else {
            head = current->next; // Remove the head node
        }

        delete current; // Free memory
        cout << "Removed song: " << title << endl;
    }

    // Function to display the playlist
    void displayPlaylist() const {
        if (!head) {
            cout << "The playlist is empty." << endl;
            return;
        }

        cout << "Current Playlist:" << endl;
        Node* current = head;
        while (current) {
            cout << "- " << current->songTitle << endl;
            current = current->next;
        }
    }

    // Destructor to free memory
    ~Playlist() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Playlist playlist;
    int choice;
    string songTitle;
    int position;

    while (true) {
        cout << "\nOptions:\n";
        cout << "1. Add Song at Beginning\n";
        cout << "2. Add Song at End\n";
        cout << "3. Add Song at Specific Position\n";
        cout << "4. Remove Song\n";
        cout << "5. Display Playlist\n";
        cout << "6. Exit\n";
        cout << "Choose an option (1-6): ";
        cin >> choice;
        cin.ignore(); // Clear newline character from input buffer

        switch (choice) {
            case 1:
                cout << "Enter song title to add at the beginning: ";
                getline(cin, songTitle);
                playlist.addSongAtBeginning(songTitle);
                break;
            case 2:
                cout << "Enter song title to add at the end: ";
                getline(cin, songTitle);
                playlist.addSongAtEnd(songTitle);
                break;
            case 3:
                cout << "Enter song title to add: ";
                getline(cin, songTitle);
                cout << "Enter position to add the song: ";
                cin >> position;
                playlist.addSongAtPosition(songTitle, position);
                break;
            case 4:
                cout << "Enter song title to remove: ";
                getline(cin, songTitle);
                playlist.removeSong(songTitle);
                break;
            case 5:
                playlist.displayPlaylist();
                break;
            case 6:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
