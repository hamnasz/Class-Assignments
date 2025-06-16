#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    list<string> playlist;
    string song;
    int choice, position;

    do {
        cout << "1. Add song at beginning\n2. Add song at end\n3. Remove song\n4. Display playlist\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter song to add at the beginning: ";
                cin >> song;
                playlist.push_front(song);
                break;
            case 2:
                cout << "Enter song to add at the end: ";
                cin >> song;
                playlist.push_back(song);
                break;
            case 3:
                cout << "Enter song to remove: ";
                cin >> song;
                playlist.remove(song);
                break;
            case 4:
                cout << "Current playlist:\n";
                for (const auto& s : playlist) {
                    cout << s << " ";
                }
                cout << endl;
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
