#include <iostream>
#include <list>
using namespace std;

int main() {
    list<string> playlist;
    string song;
    int choice, position;

    do {
        cout << "1. Add Song to Beginning\n2. Add Song to End\n3. Add Song at Position\n";
        cout << "4. Remove Song\n5. Display Playlist\n6. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter song name: ";
            cin >> song;
            playlist.push_front(song);  // Add song to the beginning
        } else if (choice == 2) {
            cout << "Enter song name: ";
            cin >> song;
            playlist.push_back(song);  // Add song to the end
        } else if (choice == 3) {
            cout << "Enter song name: ";
            cin >> song;
            cout << "Enter position: ";
            cin >> position;

            auto it = playlist.begin();
            advance(it, position - 1);  // Move iterator to the specific position
            playlist.insert(it, song);
        } else if (choice == 4) {
            cout << "Enter song name to remove: ";
            cin >> song;
            playlist.remove(song);  // Remove the specified song
        } else if (choice == 5) {
            cout << "Playlist:\n";
            for (const string &s : playlist) {
                cout << s << endl;
            }
        }
    } while (choice != 6);

    return 0;
}
