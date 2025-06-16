#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    list<string> playlist;
    
    while (true) {
        cout << "Playlist: ";
        for (auto song : playlist) {
            cout << song << " ";
        }
        cout << endl;
        cout << "1. Add song at beginning\n2. Add song at end\n3. Add song at specific position\n4. Remove song\n5. Quit" << endl;
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            string song;
            cout << "Enter song to add at beginning: ";
            cin >> song;
            playlist.push_front(song);
        } else if (choice == 2) {
            string song;
            cout << "Enter song to add at end: ";
            cin >> song;
            playlist.push_back(song);
        } else if (choice == 3) {
            string song;
            int position;
            cout << "Enter song to add: ";
            cin >> song;
            cout << "Enter position to add song: ";
            cin >> position;
            auto it = playlist.begin();
            advance(it, position - 1);
            playlist.insert(it, song);
        } else if (choice == 4) {
            string song;
            cout << "Enter song to remove: ";
            cin >> song;
            playlist.remove(song);
        } else if (choice == 5) {
            break;
        }
    }
    return 0;
}