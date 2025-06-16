#include <iostream>
#include <list>
#include <string>
using namespace std;

void addSong(list<string>& playlist, string song, int position = -1) {
    auto it = playlist.begin();
    if (position == -1) {
        playlist.push_back(song);
    } else if (position == 0) {
        playlist.push_front(song);
    } else {
        advance(it, position);
        playlist.insert(it, song);
    }
}

void removeSong(list<string>& playlist, string song) {
    playlist.remove(song);
}

void displayPlaylist(list<string>& playlist) {
    for (string song : playlist) {
        cout << song << endl;
    }
}

int main() {
    list<string> playlist;
    addSong(playlist, "Song A");
    addSong(playlist, "Song B");
    addSong(playlist, "Song C", 1);
    displayPlaylist(playlist);
    removeSong(playlist, "Song B");
    displayPlaylist(playlist);
    return 0;
}
