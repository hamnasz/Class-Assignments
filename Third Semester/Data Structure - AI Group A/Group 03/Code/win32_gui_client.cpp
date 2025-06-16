#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>  // Include winsock2 FIRST
#include <windows.h>   // Then windows.h
#include <string>
#include <thread>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

// ----------------------------------------------------
// Forward declarations
// ----------------------------------------------------
LRESULT CALLBACK WndProcA(HWND, UINT, WPARAM, LPARAM);
void AppendToFeed(const std::string& text);
void SendToServer(const std::string& text);
void ConnectToServer();
void StartReceiverThread();
void ReceiverThreadFunc();
std::string RemoveANSICodes(const std::string& input);

// ----------------------------------------------------
// Global Win32 UI handles
// ----------------------------------------------------
static HWND g_hWndMain       = nullptr;
static HWND g_hEditUsername  = nullptr;
static HWND g_hEditPassword  = nullptr;
static HWND g_hRadioRegister = nullptr;
static HWND g_hRadioLogin    = nullptr;
static HWND g_hButtonConnect = nullptr;
static HWND g_hFeedOutput    = nullptr;
static HWND g_hCommandInput  = nullptr;
static HWND g_hButtonSend    = nullptr;

// ----------------------------------------------------
// Networking / State
// ----------------------------------------------------
static SOCKET      g_clientSocket = INVALID_SOCKET;
static bool        g_connected    = false;
static std::thread g_recvThread;

// ----------------------------------------------------
// Remove ANSI color codes by skipping from ESC up to 'm'
// ----------------------------------------------------
std::string RemoveANSICodes(const std::string& input)
{
    std::string output;
    output.reserve(input.size());

    for (size_t i = 0; i < input.size(); i++)
    {
        // ASCII 27 (0x1B) is ESC
        if (static_cast<unsigned char>(input[i]) == 0x1B)
        {
            // Skip until we find 'm' or reach end
            while (i < input.size() && input[i] != 'm')
            {
                i++;
            }
            // Then the for-loop will do i++ again
        }
        else
        {
            output.push_back(input[i]);
        }
    }

    return output;
}

// ----------------------------------------------------
// Append text to feed (stripping ANSI codes, ensuring newline)
// ----------------------------------------------------
void AppendToFeed(const std::string& rawText)
{
    if (!g_hFeedOutput) return;

    // 1) Remove ANSI color codes
    std::string cleaned = RemoveANSICodes(rawText);

    // 2) Add a newline if not present
    if (!cleaned.empty() && cleaned.back() != '\n') {
        cleaned.push_back('\n');
    }

    // 3) Get current length
    int length = GetWindowTextLengthA(g_hFeedOutput);

    // 4) Move caret to end, append cleaned text
    SendMessageA(g_hFeedOutput, EM_SETSEL, (WPARAM)length, (LPARAM)length);
    SendMessageA(g_hFeedOutput, EM_REPLACESEL, FALSE, (LPARAM)cleaned.c_str());
}

// ----------------------------------------------------
// Send text to the server (ensuring newline)
// ----------------------------------------------------
void SendToServer(const std::string& text)
{
    if (!g_connected || g_clientSocket == INVALID_SOCKET) {
        AppendToFeed("[ERROR] Not connected to server.");
        return;
    }

    // Many servers parse commands line-by-line. So we ensure a newline.
    std::string toSend = text;
    if (!toSend.empty() && toSend.back() != '\n') {
        toSend.push_back('\n');
    }

    int result = send(g_clientSocket, toSend.c_str(), (int)toSend.size(), 0);
    if (result == SOCKET_ERROR) {
        AppendToFeed("[ERROR] send() failed.");
        return;
    }

    // Show the command in feed for debug
    AppendToFeed("[DEBUG] Sent command: " + text);
}

// ----------------------------------------------------
// Connect to server, gather user credentials
// ----------------------------------------------------
void ConnectToServer()
{
    if (g_connected) {
        AppendToFeed("[INFO] Already connected.");
        return;
    }

    // 1) Init WinSock
    WSADATA wsaData;
    int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaResult != 0) {
        AppendToFeed("[ERROR] WSAStartup failed.");
        return;
    }

    // 2) Create socket
    g_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (g_clientSocket == INVALID_SOCKET) {
        AppendToFeed("[ERROR] Socket creation failed.");
        WSACleanup();
        return;
    }

    // 3) Connect => 127.0.0.1:54000
    sockaddr_in serverAddr;
    serverAddr.sin_family      = AF_INET;
    serverAddr.sin_port        = htons(54000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change if server is on another IP

    int connResult = connect(g_clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (connResult == SOCKET_ERROR) {
        AppendToFeed("[ERROR] Connection failed. Is the server running?");
        closesocket(g_clientSocket);
        g_clientSocket = INVALID_SOCKET;
        WSACleanup();
        return;
    }

    AppendToFeed("[INFO] Connected to server.");
    g_connected = true;

    // 4) Gather user/pass from UI
    char unameBuf[128] = {0};
    char passBuf[128]  = {0};

    GetWindowTextA(g_hEditUsername, unameBuf, 128);
    GetWindowTextA(g_hEditPassword, passBuf, 128);

    bool isRegister = (SendMessageA(g_hRadioRegister, BM_GETCHECK, 0, 0) == BST_CHECKED);

    std::string username(unameBuf);
    std::string password(passBuf);

    if (username.empty() || password.empty()) {
        AppendToFeed("[ERROR] Username or password is empty.");
        return;
    }

    // "R user pass" => Register, or "L user pass" => Login
    std::string option = (isRegister ? "R" : "L");
    std::string credentials = option + " " + username + " " + password;
    SendToServer(credentials);

    // 5) Start background receiving thread
    StartReceiverThread();
}

// ----------------------------------------------------
// Launch the receiver thread
// ----------------------------------------------------
void StartReceiverThread()
{
    if (g_recvThread.joinable()) {
        // Already started
        return;
    }
    g_recvThread = std::thread(ReceiverThreadFunc);
}

// ----------------------------------------------------
// Continuously read from server in a separate thread
// ----------------------------------------------------
void ReceiverThreadFunc()
{
    char buf[1024];
    while (true) {
        int bytesRecv = recv(g_clientSocket, buf, sizeof(buf) - 1, 0);
        if (bytesRecv <= 0) {
            AppendToFeed("[INFO] Disconnected from server (recv error).");
            closesocket(g_clientSocket);
            g_clientSocket = INVALID_SOCKET;
            g_connected = false;
            return;
        }
        buf[bytesRecv] = '\0';

        // Show server response in feed (strip ANSI codes)
        AppendToFeed(buf);
    }
}

// ----------------------------------------------------
// The Window Procedure (ASCII version)
// ----------------------------------------------------
LRESULT CALLBACK WndProcA(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        // Username label
        CreateWindowA("STATIC", "Username:",
            WS_VISIBLE | WS_CHILD,
            10, 10, 60, 20,
            hWnd, nullptr, nullptr, nullptr);

        // Username edit
        g_hEditUsername = CreateWindowA("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            80, 10, 120, 20,
            hWnd, nullptr, nullptr, nullptr);

        // Password label
        CreateWindowA("STATIC", "Password:",
            WS_VISIBLE | WS_CHILD,
            210, 10, 60, 20,
            hWnd, nullptr, nullptr, nullptr);

        // Password edit
        g_hEditPassword = CreateWindowA("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD | ES_AUTOHSCROLL,
            280, 10, 120, 20,
            hWnd, nullptr, nullptr, nullptr);

        // Register radio
        g_hRadioRegister = CreateWindowA("BUTTON", "Register",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
            410, 10, 70, 20,
            hWnd, (HMENU)101, nullptr, nullptr);

        // Login radio
        g_hRadioLogin = CreateWindowA("BUTTON", "Login",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
            480, 10, 60, 20,
            hWnd, (HMENU)102, nullptr, nullptr);

        // Default => "Login" checked
        SendMessageA(g_hRadioLogin, BM_SETCHECK, BST_CHECKED, 0);

        // Connect button
        g_hButtonConnect = CreateWindowA("BUTTON", "Connect",
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            550, 10, 70, 20,
            hWnd, (HMENU)103, nullptr, nullptr);

        // Feed (read-only)
        g_hFeedOutput = CreateWindowA("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            10, 40, 610, 300,
            hWnd, nullptr, nullptr, nullptr);

        // Command label
        CreateWindowA("STATIC", "Command:",
            WS_VISIBLE | WS_CHILD,
            10, 350, 60, 20,
            hWnd, nullptr, nullptr, nullptr);

        // Command edit
        g_hCommandInput = CreateWindowA("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            80, 350, 450, 20,
            hWnd, nullptr, nullptr, nullptr);

        // Send button
        g_hButtonSend = CreateWindowA("BUTTON", "Send",
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            540, 350, 80, 20,
            hWnd, (HMENU)104, nullptr, nullptr);

        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 103:
            // Connect
            ConnectToServer();
            break;
        case 104:
            // Send
            {
                char cmdBuf[512] = {0};
                GetWindowTextA(g_hCommandInput, cmdBuf, 512);
                std::string cmd(cmdBuf);
                if (!cmd.empty()) {
                    SendToServer(cmd);
                    // Clear the command input
                    SetWindowTextA(g_hCommandInput, "");
                }
            }
            break;
        }
        break;

    case WM_DESTROY:
        // Cleanup
        if (g_clientSocket != INVALID_SOCKET) {
            closesocket(g_clientSocket);
            g_clientSocket = INVALID_SOCKET;
        }
        WSACleanup();
        PostQuitMessage(0);
        break;
    }

    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

// ----------------------------------------------------
// WinMain entry point (ASCII)
// ----------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    // 1) Register Window Class (ASCII)
    WNDCLASSA wc = {0};
    wc.lpfnWndProc   = WndProcA;
    wc.hInstance     = hInstance;
    wc.lpszClassName = "Win32ClientClass";
    wc.hCursor       = LoadCursorA(nullptr, IDC_ARROW);

    if (!RegisterClassA(&wc)) {
        MessageBoxA(nullptr, "RegisterClassA failed!", "Error", MB_ICONERROR);
        return 1;
    }

    // 2) Create main window
    g_hWndMain = CreateWindowA(
        "Win32ClientClass",
        "Simple Win32 SocialFeed Client - Stripping ANSI",
        WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION,
        CW_USEDEFAULT, CW_USEDEFAULT,
        650, 420,  // width, height
        nullptr, nullptr, hInstance, nullptr
    );
    if (!g_hWndMain) {
        MessageBoxA(nullptr, "CreateWindowA failed!", "Error", MB_ICONERROR);
        return 1;
    }

    ShowWindow(g_hWndMain, nCmdShow);
    UpdateWindow(g_hWndMain);

    // 3) Message loop
    MSG msg;
    while (GetMessageA(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    // If the receiver thread is still running, detach it
    if (g_recvThread.joinable()) {
        g_recvThread.detach();
    }

    return (int)msg.wParam;
}
