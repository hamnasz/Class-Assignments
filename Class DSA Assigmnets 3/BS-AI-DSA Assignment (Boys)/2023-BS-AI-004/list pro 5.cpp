#include <iostream>
#include <list>

using namespace std;

int main() {
    list<string> playlist;
    int choice;
    string song;
    int position;

    do {
        cout << "1. Add song to start\n2. Add song to end\n3. Add song at position\n4. Remove song\n5. Show playlist\n6. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter song: ";
            cin >> song;
            playlist.push_front(song);
        } else if (choice == 2) {
            cout << "Enter song: ";
            cin >> song;
            playlist.push_back(song);
        } else if (choice == 3) {
            cout << "Enter song and position: ";
            cin >> song >> position;

            // Use a loop to iterate to the desired position
            list<string>::iterator it = playlist.begin();
            for (int i = 0; i < position - 1; ++i) {
                ++it;
            }
            playlist.insert(it, song);
        } else if (choice == 4) {
            cout << "Enter song to remove: ";
            cin >> song;
            playlist.remove(song);
        } else if (choice == 5) {
            cout << "Playlist:\n";
            for (const string& s : playlist) {
                cout << s << endl;
            }
        }
    } while (choice != 6);

    return 0;
}