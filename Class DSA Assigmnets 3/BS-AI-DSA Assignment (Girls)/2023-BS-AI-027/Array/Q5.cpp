#include <iostream>
#include <string>
using namespace std;

const int MAX_SONGS = 100;
string playlist[MAX_SONGS];
int songCount = 0;  // Keeps track of the number of songs in the playlist

void addSongAtEnd(const string& song) {
    if (songCount < MAX_SONGS) {
        playlist[songCount++] = song;
        cout << "Song \"" << song << "\" added at the end.\n";
    } else {
        cout << "Playlist is full. Cannot add more songs.\n";
    }
}

void addSongAtBeginning(const string& song) {
    if (songCount < MAX_SONGS) {
        // Shift all songs to the right to make space at the beginning
        for (int i = songCount; i > 0; i--) {
            playlist[i] = playlist[i - 1];
        }
        playlist[0] = song;
        songCount++;
        cout << "Song \"" << song << "\" added at the beginning.\n";
    } else {
        cout << "Playlist is full. Cannot add more songs.\n";
    }
}

void addSongAtPosition(const string& song, int position) {
    if (position < 0 || position > songCount || songCount >= MAX_SONGS) {
        cout << "Invalid position or playlist is full.\n";
        return;
    }
    // Shift songs to the right to make space at the specified position
    for (int i = songCount; i > position; i--) {
        playlist[i] = playlist[i - 1];
    }
    playlist[position] = song;
    songCount++;
    cout << "Song \"" << song << "\" added at position " << position << ".\n";
}

void removeSong(const string& song) {
    bool found = false;
    for (int i = 0; i < songCount; i++) {
        if (playlist[i] == song) {
            found = true;
            // Shift songs to the left to fill the gap
            for (int j = i; j < songCount - 1; j++) {
                playlist[j] = playlist[j + 1];
            }
            songCount--;
            cout << "Song \"" << song << "\" removed from the playlist.\n";
            break;
        }
    }
    if (!found) {
        cout << "Song \"" << song << "\" not found in the playlist.\n";
    }
}

void displayPlaylist() {
    if (songCount == 0) {
        cout << "The playlist is empty.\n";
    } else {
        cout << "Playlist:\n";
        for (int i = 0; i < songCount; i++) {
            cout << i + 1 << ". " << playlist[i] << endl;
        }
    }
}

int main() {
    int choice, position;
    string song;

    while (true) {
        cout << "\nOptions:\n";
        cout << "1. Add song at end\n";
        cout << "2. Add song at beginning\n";
        cout << "3. Add song at specific position\n";
        cout << "4. Remove song\n";
        cout << "5. Display playlist\n";
        cout << "6. Exit\n";
        cout << "Choose an option (1-6): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter song name to add at end: ";
                getline(cin, song);
                addSongAtEnd(song);
                break;
            case 2:
                cout << "Enter song name to add at beginning: ";
                getline(cin, song);
                addSongAtBeginning(song);
                break;
            case 3:
                cout << "Enter song name to add: ";
                getline(cin, song);
                cout << "Enter position (0 to " << songCount << "): ";
                cin >> position;
                cin.ignore();
                addSongAtPosition(song, position);
                break;
            case 4:
                cout << "Enter song name to remove: ";
                getline(cin, song);
                removeSong(song);
                break;
            case 5:
                displayPlaylist();
                break;
            case 6:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid option. Please choose again.\n";
                break;
        }
    }
}
