#include <iostream>
#include <string>
using namespace std;
struct Node {
    string song;
    Node* next;
    Node* prev;
};
class Playlist {
private:
    Node* head;
    Node* tail;
public:
    Playlist() : head(nullptr), tail(nullptr) {}
    void addAtBeginning(const string& song) {
        Node* newNode = new Node{song, nullptr, nullptr};
        if (!head) {
            head = tail = newNode; 
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        cout << song << " added to the beginning of the playlist." << endl;
    }
    void addAtEnd(const string& song) {
        Node* newNode = new Node{song, nullptr, nullptr};
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << song << " added to the end of the playlist." << endl;
    }
    void addAtPosition(const string& song, int position) {
        Node* newNode = new Node{song, nullptr, nullptr};

        if (position <= 0) {
            addAtBeginning(song);
            return;
        }

        Node* current = head;
        for (int i = 0; i < position && current != nullptr; i++) {
            current = current->next;
        }

        if (current == nullptr) {
            addAtEnd(song);
        } else {
            newNode->next = current;
            newNode->prev = current->prev;
            if (current->prev) {
                current->prev->next = newNode;
            }
            current->prev = newNode;
            if (current == head) {
                head = newNode; 
            }
            cout << song << " added at position " << position << "." << endl;
        }
    }
    void removeSong(const string& song) {
        Node* current = head;

        while (current != nullptr) {
            if (current->song == song) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next; 
                }
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev; 
                }
                delete current;
                cout << song << " has been removed from the playlist." << endl;
                return;
            }
            current = current->next;
        }
        cout << song << " not found in the playlist." << endl;
    }
    void displayPlaylist() const {
        if (!head) {
            cout << "The playlist is empty." << endl;
            return;
        }

        cout << "Current Playlist:" << endl;
        Node* current = head;
        while (current != nullptr) {
            cout << "- " << current->song << endl;
            current = current->next;
        }
    }
    ~Playlist() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    Playlist playlist;
    string command, song;
    int position;

    while (true) {
        cout << "\nEnter command (add_beg/add_end/add_pos/remove/display/exit): ";
        cin >> command;

        if (command == "add_beg") {
            cout << "Enter song name to add at beginning: ";
            cin.ignore();
            getline(cin, song);
            playlist.addAtBeginning(song);
        } 
        else if (command == "add_end") {
            cout << "Enter song name to add at end: ";
            cin.ignore();
            getline(cin, song);
            playlist.addAtEnd(song);
        } 
        else if (command == "add_pos") {
            cout << "Enter song name to add: ";
            cin.ignore();
            getline(cin, song);
            cout << "Enter position to add the song: ";
            cin >> position;
            playlist.addAtPosition(song, position);
        } 
        else if (command == "remove") {
            cout << "Enter song name to remove: ";
            cin.ignore();
            getline(cin, song);
            playlist.removeSong(song);
        } 
        else if (command == "display") {
            playlist.displayPlaylist();
        } 
        else if (command == "exit") {
            cout << "Exiting program." << endl;
            break;
        } 
        else {
            cout << "Invalid command. Please enter 'add_beg', 'add_end', 'add_pos', 'remove', 'display', or 'exit'." << endl;
        }
    }

    return 0;
}