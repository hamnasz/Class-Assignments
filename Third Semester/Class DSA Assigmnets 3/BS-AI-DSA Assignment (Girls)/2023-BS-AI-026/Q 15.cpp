
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define a structure for a song
struct Song {
    string title;
    string artist;
};

// PlaylistManager class
class PlaylistManager {
private:
    vector<Song> playlist;

public:
    // Add song at the beginning
    void addAtBeginning(const Song& song) {
        playlist.insert(playlist.begin(), song);
    }

    // Add song at the end
    void addAtEnd(const Song& song) {
        playlist.push_back(song);
    }

    // Add song at specific position
    void addAtPosition(const Song& song, int position) {
        if (position < 0 || position > playlist.size()) {
            cout << "Invalid position." << endl;
            return;
        }
        playlist.insert(playlist.begin() + position, song);
    }

    // Remove song from the playlist
    void removeSong(int position) {
        if (position < 0 || position >= playlist.size()) {
            cout << "Invalid position." << endl;
            return;
        }
        playlist.erase(playlist.begin() + position);
    }

    // Display the playlist
    void displayPlaylist() const {
        if (playlist.empty()) {
            cout << "Playlist is empty." << endl;
            return;
        }

        cout << "Playlist:" << endl;
        for (int i = 0; i < playlist.size(); ++i) {
            cout << i + 1 << ". " << playlist[i].title << " - " << playlist[i].artist << endl;
        }
    }
};

int main() {
    PlaylistManager playlistManager;

    // Test the playlist manager
    Song song1 = {"Happy", "Pharrell Williams"};
    Song song2 = {"Uptown Funk", "Mark Ronson ft. Bruno Mars"};
    Song song3 = {"Can't Stop the Feeling!", "Justin Timberlake"};

    playlistManager.addAtEnd(song1);
    playlistManager.addAtEnd(song2);
    playlistManager.addAtBeginning(song3);
    playlistManager.displayPlaylist();

    cout << "\nAdding song at position 2..." << endl;
    Song song4 = {"We Found Love", "Rihanna ft. Calvin Harris"};
    playlistManager.addAtPosition(song4, 2);
    playlistManager.displayPlaylist();

    cout << "\nRemoving song at position 2..." << endl;
    playlistManager.removeSong(2);
    playlistManager.displayPlaylist();

    return 0;
}
