#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    list<string> musicPlaylist;
    string action, song;
    int index;

    while (true) {
        cout << "\nChoose an action (add_start/add_end/add_index/remove/show/quit): ";
        cin >> action;

        if (action == "add_start") {
            cout << "Enter the song name to add at the start: ";
            cin.ignore();
            getline(cin, song);
            musicPlaylist.push_front(song);
        } 
        else if (action == "add_end") {
            cout << "Enter the song name to add at the end: ";
            cin.ignore();
            getline(cin, song);
            musicPlaylist.push_back(song);
        } 
        else if (action == "add_index") {
            cout << "Enter index (0 for start, 1 for first, etc.): ";
            cin >> index;
            cout << "Enter the song name to add at index " << index << ": ";
            cin.ignore();
            getline(cin, song);

            if (index < 0 || index > musicPlaylist.size()) {
                cout << "Invalid index!" << endl;
            } else {
                auto it = musicPlaylist.begin();
                advance(it, index); 
                musicPlaylist.insert(it, song);
            }
        } 
        else if (action == "remove") {
            cout << "Enter the song name to remove: ";
            cin.ignore();
            getline(cin, song);
            musicPlaylist.remove(song);
        } 
        else if (action == "show") {
            cout << "Current Playlist: ";
            for (const auto& s : musicPlaylist) {
                cout << s << " | ";
            }
            cout << endl;
        } 
        else if (action == "quit") {
            break;
        } 
        else {
            cout << "Invalid action. Please try again." << endl;
        }
    }

    return 0;
}
