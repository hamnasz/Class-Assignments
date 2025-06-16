#include <iostream>
#include <list>
using namespace std;

int main() {
    list<string> playlist;

    playlist.push_back("Song A");
    playlist.push_front("Song B");
    playlist.remove("Song A");

    cout << "Playlist: ";
    for (const string& song : playlist) {
        cout << song << " ";
    }
    cout << endl;
    return 0;
}
