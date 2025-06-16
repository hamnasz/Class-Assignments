#include <iostream>
#include <string>

using namespace std;

struct SongNode {
    string songTitle;     // Title of the song
    SongNode* next;      // Pointer to the next song in the playlist
};

class Playlist {
private:
    SongNode* head;      // Pointer to the head of the playlist

public:
    Playlist() : head(nullptr) {}

    // Add a song to the beginning of the playlist
    void addSongAtBeginning(const string& title) {
        SongNode* newSong = new SongNode{title, head};
        head = newSong;
        cout << "\"" << title << "\" added to the beginning of the playlist.\n";
    }

    // Add a song to the end of the playlist
    void addSongAtEnd(const string& title) {
        SongNode* newSong = new SongNode{title, nullptr};
        
        if (!head) {
            head = newSong;  // If the playlist is empty, set head to new song
        } else {
            SongNode* temp = head;
            while (temp->next) {  // Traverse to the end of the playlist
                temp = temp->next;
            }
            temp->next = newSong;  // Link the last song to the new song
        }

        cout << "\"" << title << "\" added to the end of the playlist.\n";
    }

    // Add a song at a specific position
    void addSongAtPosition(const string& title, int position) {
        if (position <= 0) {
            addSongAtBeginning(title);  // Position 0 or negative, add to the beginning
            return;
        }

        SongNode* newSong = new SongNode{title, nullptr};
        SongNode* temp = head;

        for (int i = 0; i < position - 1 && temp; ++i) {  // Traverse to the desired position
            temp = temp->next;
        }

        if (!temp) {
            cout << "Position out of bounds. Adding to the end instead.\n";
            addSongAtEnd(title);  // If position is out of bounds, add to the end
            return;
        }

        newSong->next = temp->next;  // Link the new song to the next song
        temp->next = newSong;         // Link the previous song to the new song
        cout << "\"" << title << "\" added at position " << position << ".\n";
    }

    // Remove a song by title
    void removeSong(const string& title) {
        if (!head) {
            cout << "The playlist is empty.\n";
            return;
        }

        // Check if the song to remove is at the head
        if (head->songTitle == title) {
            SongNode* temp = head;
            head = head->next;
            delete temp;
            cout << "\"" << title << "\" removed from the playlist.\n";
            return;
        }

        SongNode* current = head;
        while (current->next && current->next->songTitle != title) {  // Search for the song
            current = current->next;
        }

        if (current->next) {
            SongNode* temp = current->next;
            current->next = current->next->next;  // Bypass the song to remove
            delete temp;
            cout << "\"" << title << "\" removed from the playlist.\n";
        } else {
            cout << "\"" << title << "\" not found in the playlist.\n";
        }
    }

    // Display the playlist
    void displayPlaylist() const {
        if (!head) {
            cout << "The playlist is empty.\n";
            return;
        }

        cout << "Current playlist:\n";
        SongNode* temp = head;
        while (temp) {
            cout << "- " << temp->songTitle << endl;
            temp = temp->next;
        }
    }

    // Destructor to clean up the playlist
    ~Playlist() {
        while (head) {
            SongNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Playlist playlist;
    int choice;
    string title;
    int position;

    do {
        cout << "\nMusic Playlist Manager Menu:\n";
        cout << "1. Add song at beginning\n";
        cout << "2. Add song at end\n";
        cout << "3. Add song at specific position\n";
        cout << "4. Remove song\n";
        cout << "5. Display playlist\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore newline from the input buffer

        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                getline(cin, title);
                playlist.addSongAtBeginning(title);
                break;

            case 2:
                cout << "Enter song title: ";
                getline(cin, title);
                playlist.addSongAtEnd(title);
                break;

            case 3:
                cout << "Enter song title: ";
                getline(cin, title);
                cout << "Enter position: ";
                cin >> position;
                cin.ignore();
                playlist.addSongAtPosition(title, position);
                break;

            case 4:
                cout << "Enter song title to remove: ";
                getline(cin, title);
                playlist.removeSong(title);
                break;

            case 5:
                playlist.displayPlaylist();
                break;

            case 6:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

