#include <iostream>
#include <string>
#include <thread>
#include <limits>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void receiveMessages(SOCKET clientSocket) {
    char buffer[1024];
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            cerr << "[INFO] Disconnected from server.\n";
            break;
        }
        buffer[bytesReceived] = '\0';
        cout << buffer;  // The server may have ANSI color codes; we just print them out
    }
}

int main() {
    // 1) Init WinSock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "[ERROR] WSAStartup failed.\n";
        return 1;
    }

    // 2) Create socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "[ERROR] Socket creation failed.\n";
        WSACleanup();
        return 1;
    }

    // 3) Server info
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port   = htons(54000);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.1.14"); // or another IP if needed

    // 4) Connect
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "[ERROR] Connection failed.\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    cout << "[INFO] Connected to server.\n";

    // 5) Prompt for R/L
    cout << "Choose an option (R for Register, L for Login): ";
    string option;
    cin >> option;
    cout << "Enter username: ";
    string username;
    cin >> username;
    cout << "Enter password: ";
    string password;
    cin >> password;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover

    // Send credentials
    string credentials = option + " " + username + " " + password;
    send(clientSocket, credentials.c_str(), credentials.size(), 0);

    // Check response
    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived <= 0) {
        cerr << "[ERROR] No response from server.\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    buffer[bytesReceived] = '\0';
    string resp(buffer);
    if (resp != "Success") {
        cerr << "[ERROR] " << resp << "\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    cout << "[INFO] Login/Register successful. Welcome, " << username << "!\n\n";

    // 6) Start thread to receive messages
    thread recvThread(receiveMessages, clientSocket);
    recvThread.detach();

    // 7) Print commands
    cout << "Available commands:\n"
         << "  /post <text>::<mediaURL>   - Create post (mediaURL optional)\n"
         << "  /feed                      - View all posts\n"
         << "  /dm <user> <message>       - Direct message (friends only)\n"
         << "  /like <postID>, /dislike <postID>\n"
         << "  /friend request <user>, /friend accept <user>\n"
         << "  /comment <postID> <text>\n"
         << "  /viewpost <postID>\n"
         << "  /editpost <postID> <new text>\n"
         << "  /deletepost <postID>\n"
         << "  /editcomment <commentID> <new text>\n"
         << "  /deletecomment <commentID>\n"
         << "  /poll create <q>::o1,o2..., /poll vote <id> <optIndex>, /poll results <id>\n"
         << "  /quit                      - Exit\n\n";

    // 8) Main loop
    while (true) {
        string userInput;
        getline(cin, userInput);
        if (userInput.empty()) continue;

        send(clientSocket, userInput.c_str(), userInput.size(), 0);

        if (userInput == "/quit") {
            break;
        }
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
