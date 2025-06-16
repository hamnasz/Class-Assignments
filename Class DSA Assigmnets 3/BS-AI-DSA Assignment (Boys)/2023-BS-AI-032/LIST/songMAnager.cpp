#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Include algorithm for std::remove
using namespace std;

class Playlist {
private:
    vector<string> songs;

public:
    void addSong(const string& song) {
        cout << "Adding song: " << song << endl; // Debug statement
        songs.push_back(song);
    }

    void removeSong(const string& song) {
        cout << "Attempting to remove song: " << song << endl; // Debug statement
        auto it = remove(songs.begin(), songs.end(), song);
        if (it != songs.end()) {
            songs.erase(it, songs.end());
            cout << "Song removed: " << song << endl; // Debug statement
        } else {
            cout << "Song not found.\n";
        }
    }

    void displayPlaylist() {
        cout << "Displaying playlist:" << endl; // Debug statement
        if (songs.empty()) {
            cout << "Playlist is empty.\n";
            return;
        }
        for (const auto& song : songs) {
            cout << song << endl;
        }
    }
};

int main() {
    Playlist playlist;
    playlist.addSong("Song A");
    playlist.addSong("Song B");
    playlist.displayPlaylist();
    playlist.removeSong("Song A");
    playlist.displayPlaylist();
    return 0;
}

