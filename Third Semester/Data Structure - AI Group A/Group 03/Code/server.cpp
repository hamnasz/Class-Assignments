#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <vector>
#include <set>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

// ---------------------
//  ANSI COLOR HELPER
// ---------------------
string colorText(const string& text, const string& colorCode) {
    return "\033[" + colorCode + "m" + text + "\033[0m";
}

// ---------------------
//  STRUCTS
// ---------------------
struct Post {
    int    id;           // unique post ID
    string username;     // who posted
    string content;      
    string mediaURL;     // optional
    time_t timestamp;    // creation time
};

struct Comment {
    int    commentID;
    int    postID;
    string username;
    string text;
    time_t timestamp;    // for edit/delete time checks
};

struct Poll {
    int    pollID;
    string creator;      // who made the poll
    string question;
    vector<string> options;
    vector<int> votes;   // parallel to 'options', e.g. votes[i] is # of votes for options[i]
    time_t timestamp;    // creation time (for potential future checks)
};

// ---------------------
//  GLOBAL DATA
// ---------------------
map<string, string> userCredentials;  // username -> password
map<string, SOCKET> onlineUsers;      // for DM
map<string, set<string>> friendLists; // friendLists[user] = set of friends
map<string, set<string>> friendRequests; // friendRequests[target] = set of usernames who requested

vector<Post> feedPosts;            // all posts in memory
map<int, set<string>> postLikes;   // postID -> set of users who liked
map<int, set<string>> postDislikes;// postID -> set of users who disliked

// Comments stored in memory only
// commentMap[postID] = vector of comments for that post
// We'll also keep a global commentIDCounter to assign unique IDs.
map<int, vector<Comment>> commentMap;
int  commentIDCounter = 1;

// For message edit/deletion time limit (e.g., 120 sec)
const int EDIT_DELETE_LIMIT_SEC = 120;

// Polls
vector<Poll> polls;
int pollIDCounter = 1;

// ---------------------
//  FILE PATHS
// ---------------------
const string USERS_FILE = "users.txt";
const string POSTS_FILE = "posts.txt";

/*
   We store posts in a text file with lines like:
   postID||username||timestamp||content||mediaURL

   If mediaURL is empty, we store "NONE".
*/

// ---------------------
//  FILE OPERATIONS
// ---------------------
void loadUsersFromFile() {
    ifstream inFile(USERS_FILE);
    if (!inFile.is_open()) {
        cerr << "[INFO] No existing user file. Starting fresh.\n";
        return;
    }
    string line;
    while (getline(inFile, line)) {
        // "username password"
        size_t spacePos = line.find(' ');
        if (spacePos != string::npos) {
            string uname = line.substr(0, spacePos);
            string pass  = line.substr(spacePos + 1);
            userCredentials[uname] = pass;
        }
    }
    inFile.close();
}

void saveUserToFile(const string& username, const string& password) {
    ofstream outFile(USERS_FILE, ios::app);
    if (!outFile.is_open()) {
        cerr << "[ERROR] Could not open users file.\n";
        return;
    }
    outFile << username << " " << password << "\n";
    outFile.close();
}

void loadPostsFromFile() {
    ifstream inFile(POSTS_FILE);
    if (!inFile.is_open()) {
        cerr << "[INFO] No existing posts file. Starting fresh.\n";
        return;
    }
    while (!inFile.eof()) {
        string line;
        if (!getline(inFile, line)) break;
        if (line.empty()) continue;

        vector<string> tokens;
        size_t start = 0;
        while (true) {
            size_t pos = line.find("||", start);
            if (pos == string::npos) {
                tokens.push_back(line.substr(start));
                break;
            }
            tokens.push_back(line.substr(start, pos - start));
            start = pos + 2;
        }
        if (tokens.size() < 5) continue;

        Post p;
        p.id        = stoi(tokens[0]);
        p.username  = tokens[1];
        p.timestamp = stol(tokens[2]);
        p.content   = tokens[3];
        p.mediaURL  = (tokens[4] == "NONE") ? "" : tokens[4];

        feedPosts.push_back(p);

        // Initialize empty like/dislike sets
        postLikes[p.id] = {};
        postDislikes[p.id] = {};
    }
    inFile.close();
}

void savePostToFile(const Post& p) {
    ofstream outFile(POSTS_FILE, ios::app);
    if (!outFile.is_open()) {
        cerr << "[ERROR] Could not open posts file.\n";
        return;
    }
    string media = p.mediaURL.empty() ? "NONE" : p.mediaURL;
    outFile << p.id << "||"
            << p.username << "||"
            << p.timestamp << "||"
            << p.content << "||"
            << media
            << "\n";
    outFile.close();
}

// ---------------------
//  ID GENERATORS
// ---------------------
int generatePostID() {
    int maxID = 0;
    for (auto &p : feedPosts) {
        if (p.id > maxID) maxID = p.id;
    }
    return maxID + 1;
}

// ---------------------
//  SORT HELPERS
// ---------------------
bool sortByTimestampDesc(const Post &a, const Post &b) {
    return a.timestamp > b.timestamp;
}
bool sortPollByTimestampDesc(const Poll &a, const Poll &b) {
    return a.timestamp > b.timestamp;
}

// ---------------------
//  TIME CHECKS
// ---------------------
bool canEditOrDelete(time_t creationTime) {
    time_t now = time(nullptr);
    double diff = difftime(now, creationTime);
    return (diff <= EDIT_DELETE_LIMIT_SEC);
}

// ---------------------
//  COMMAND HANDLERS
// ---------------------
void handleFriendCommand(const string& cmdBody, const string& username, SOCKET clientSock) {
    // /friend request <targetUser>
    // /friend accept <targetUser>
    // We store in friendRequests[targetUser] the set of usernames who requested.
    // When accepted, we remove from friendRequests[targetUser] and add each other in friendLists.
    if (cmdBody.rfind("request ", 0) == 0) {
        // request <targetUser>
        string targetUser = cmdBody.substr(8);
        if (targetUser.empty()) {
            string msg = "Usage: /friend request <username>\n";
            send(clientSock, msg.c_str(), msg.size(), 0);
            return;
        }
        // Check if user exists
        if (userCredentials.find(targetUser) == userCredentials.end()) {
            string msg = "User '" + targetUser + "' does not exist.\n";
            send(clientSock, msg.c_str(), msg.size(), 0);
            return;
        }
        // Add to friendRequests
        friendRequests[targetUser].insert(username);
        string msg = "Friend request sent to " + targetUser + "\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
    }
    else if (cmdBody.rfind("accept ", 0) == 0) {
        // accept <targetUser>
        string requester = cmdBody.substr(7);
        if (requester.empty()) {
            string msg = "Usage: /friend accept <username>\n";
            send(clientSock, msg.c_str(), msg.size(), 0);
            return;
        }
        // check if 'requester' is in friendRequests[username]
        auto it = friendRequests.find(username);
        if (it == friendRequests.end() || it->second.find(requester) == it->second.end()) {
            string msg = "No friend request from '" + requester + "' found.\n";
            send(clientSock, msg.c_str(), msg.size(), 0);
            return;
        }
        // Accept
        friendLists[username].insert(requester);
        friendLists[requester].insert(username);
        // remove from friendRequests
        friendRequests[username].erase(requester);
        string msg = "You are now friends with " + requester + "\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
    }
    else {
        string msg = "Usage:\n"
                     "  /friend request <user>\n"
                     "  /friend accept <user>\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
    }
}

void handleComment(const string& cmdBody, const string& username, SOCKET clientSock) {
    // /comment <postID> <text>
    // parse out postID
    size_t spacePos = cmdBody.find(' ');
    if (spacePos == string::npos) {
        string msg = "Usage: /comment <postID> <comment text>\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
        return;
    }
    string idStr = cmdBody.substr(0, spacePos);
    string commentText = cmdBody.substr(spacePos + 1);
    if (commentText.empty()) {
        string msg = "Cannot post empty comment.\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
        return;
    }
    int postID = stoi(idStr);

    // verify post exists
    auto found = find_if(feedPosts.begin(), feedPosts.end(), [postID](const Post& p){
        return p.id == postID;
    });
    if (found == feedPosts.end()) {
        string msg = "Post ID " + to_string(postID) + " not found.\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
        return;
    }

    // create comment
    Comment c;
    c.commentID = commentIDCounter++;
    c.postID = postID;
    c.username = username;
    c.text = commentText;
    c.timestamp = time(nullptr);

    commentMap[postID].push_back(c);

    string msg = "Comment posted successfully! (CommentID: " + to_string(c.commentID) + ")\n";
    send(clientSock, msg.c_str(), msg.size(), 0);
}

void handleViewPost(const string& cmdBody, SOCKET clientSock) {
    // /viewpost <postID>
    int postID = stoi(cmdBody);
    // find post
    auto it = find_if(feedPosts.begin(), feedPosts.end(), [postID](const Post &p){
        return p.id == postID;
    });
    if (it == feedPosts.end()) {
        string msg = "Post ID " + to_string(postID) + " not found.\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
        return;
    }
    // build output
    Post &p = *it;
    char timeBuf[26];
    ctime_s(timeBuf, sizeof(timeBuf), &p.timestamp);
    string timeString(timeBuf);
    if (!timeString.empty() && timeString.back() == '\n') {
        timeString.pop_back();
    }

    int likeCount    = (int)postLikes[p.id].size();
    int dislikeCount = (int)postDislikes[p.id].size();

    // Post info
    string postLine = colorText("[PostID=" + to_string(p.id) + "] ", "35") +
                      colorText("[" + timeString + "] ", "33") +
                      colorText(p.username, "36") + "\n" +
                      "  " + colorText("Content: ", "32") + p.content + "\n";
    if (!p.mediaURL.empty()) {
        postLine += "  " + colorText("Media: ", "34") + p.mediaURL + "\n";
    }
    postLine += "  " + colorText("Likes: ", "31") + to_string(likeCount) +
                ", " + colorText("Dislikes: ", "31") + to_string(dislikeCount) + "\n\n";

    // Comments
    auto &comVec = commentMap[p.id];
    if (comVec.empty()) {
        postLine += colorText("No comments.\n", "33");
    } else {
        postLine += colorText("Comments:\n", "33");
        for (auto &c : comVec) {
            char cTimeBuf[26];
            ctime_s(cTimeBuf, sizeof(cTimeBuf), &c.timestamp);
            string cTimeString(cTimeBuf);
            if (!cTimeString.empty() && cTimeString.back() == '\n') {
                cTimeString.pop_back();
            }
            postLine += "  [CmtID=" + to_string(c.commentID) + "] " +
                        colorText("(" + cTimeString + ") ", "33") +
                        colorText(c.username, "36") + ": " + c.text + "\n";
        }
    }
    postLine += "\n";

    send(clientSock, postLine.c_str(), postLine.size(), 0);
}

void handleEditPost(const string& cmdBody, const string& username, SOCKET clientSock) {
    // /editpost <postID> <newContent>
    // can only edit if user is the creator, within time limit
    size_t spacePos = cmdBody.find(' ');
    if (spacePos == string::npos) {
        string msg = "Usage: /editpost <postID> <new content>\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
        return;
    }
    int postID = stoi(cmdBody.substr(0, spacePos));
    string newContent = cmdBody.substr(spacePos + 1);

    auto it = find_if(feedPosts.begin(), feedPosts.end(), [postID](const Post& p){
        return p.id == postID;
    });
    if (it == feedPosts.end()) {
        string msg = "Post ID " + to_string(postID) + " not found.\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
        return;
    }
    // check ownership
    if (it->username != username) {
        string msg = "You do not own this post.\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
        return;
    }
    // check time limit
    if (!canEditOrDelete(it->timestamp)) {
        string msg = "Edit window has expired.\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
        return;
    }
    // do edit
    it->content = newContent;
    string msg = "Post edited successfully.\n";
    send(clientSock, msg.c_str(), msg.size(), 0);
}

void handleDeletePost(const string& cmdBody, const string& username, SOCKET clientSock) {
    // /deletepost <postID>
    int postID = stoi(cmdBody);
    auto it = find_if(feedPosts.begin(), feedPosts.end(), [postID](const Post& p){
        return p.id == postID;
    });
    if (it == feedPosts.end()) {
        string msg = "Post ID " + to_string(postID) + " not found.\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
        return;
    }
    // check ownership
    if (it->username != username) {
        string msg = "You do not own this post.\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
        return;
    }
    // check time limit
    if (!canEditOrDelete(it->timestamp)) {
        string msg = "Delete window has expired.\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
        return;
    }
    // remove from feedPosts
    feedPosts.erase(it);
    // remove from postLikes, postDislikes, commentMap if present
    postLikes.erase(postID);
    postDislikes.erase(postID);
    commentMap.erase(postID);

    string msg = "Post deleted successfully.\n";
    send(clientSock, msg.c_str(), msg.size(), 0);
}

void handleEditComment(const string& cmdBody, const string& username, SOCKET clientSock) {
    // /editcomment <commentID> <new text>
    size_t spacePos = cmdBody.find(' ');
    if (spacePos == string::npos) {
        string msg = "Usage: /editcomment <commentID> <new text>\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
        return;
    }
    int cmtID = stoi(cmdBody.substr(0, spacePos));
    string newText = cmdBody.substr(spacePos + 1);

    // find comment
    bool foundCmt = false;
    for (auto &kv : commentMap) {
        for (auto &c : kv.second) {
            if (c.commentID == cmtID) {
                if (c.username != username) {
                    string msg = "You do not own this comment.\n";
                    send(clientSock, msg.c_str(), msg.size(), 0);
                    return;
                }
                if (!canEditOrDelete(c.timestamp)) {
                    string msg = "Edit window expired.\n";
                    send(clientSock, msg.c_str(), msg.size(), 0);
                    return;
                }
                c.text = newText;
                string msg2 = "Comment edited successfully.\n";
                send(clientSock, msg2.c_str(), msg2.size(), 0);
                return;
            }
        }
    }
    if (!foundCmt) {
        string msg = "Comment ID not found.\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
    }
}

void handleDeleteComment(const string& cmdBody, const string& username, SOCKET clientSock) {
    // /deletecomment <commentID>
    int cmtID = stoi(cmdBody);
    for (auto &kv : commentMap) {
        auto &vec = kv.second;
        for (size_t i = 0; i < vec.size(); i++) {
            if (vec[i].commentID == cmtID) {
                if (vec[i].username != username) {
                    string msg = "You do not own this comment.\n";
                    send(clientSock, msg.c_str(), msg.size(), 0);
                    return;
                }
                if (!canEditOrDelete(vec[i].timestamp)) {
                    string msg = "Delete window expired.\n";
                    send(clientSock, msg.c_str(), msg.size(), 0);
                    return;
                }
                vec.erase(vec.begin() + i);
                string msg2 = "Comment deleted successfully.\n";
                send(clientSock, msg2.c_str(), msg2.size(), 0);
                return;
            }
        }
    }
    string msg = "Comment ID not found.\n";
    send(clientSock, msg.c_str(), msg.size(), 0);
}

// ---------------------
//  POLLS
// ---------------------
void handlePollCommand(const string& cmdBody, const string& username, SOCKET clientSock) {
    // /poll create <question>::<opt1>,<opt2>,...
    // /poll vote <pollID> <optionIndex>
    // /poll results <pollID>
    // We'll parse subcommand
    size_t spacePos = cmdBody.find(' ');
    if (spacePos == string::npos) {
        string helpMsg = "Usage:\n"
                         "  /poll create <question>::opt1,opt2,...\n"
                         "  /poll vote <pollID> <optionIndex>\n"
                         "  /poll results <pollID>\n";
        send(clientSock, helpMsg.c_str(), helpMsg.size(), 0);
        return;
    }
    string subCmd = cmdBody.substr(0, spacePos);
    string remainder = cmdBody.substr(spacePos + 1);

    if (subCmd == "create") {
        // remainder = <question>::<opt1,opt2,...>
        size_t delimPos = remainder.find("::");
        if (delimPos == string::npos) {
            string msg = "Usage: /poll create <question>::opt1,opt2,...\n";
            send(clientSock, msg.c_str(), msg.size(), 0);
            return;
        }
        string question = remainder.substr(0, delimPos);
        string optionsPart = remainder.substr(delimPos + 2);
        if (question.empty() || optionsPart.empty()) {
            string msg = "Invalid poll creation.\n";
            send(clientSock, msg.c_str(), msg.size(), 0);
            return;
        }
        // split options by comma
        vector<string> opts;
        size_t start = 0;
        while (true) {
            size_t pos = optionsPart.find(',', start);
            if (pos == string::npos) {
                opts.push_back(optionsPart.substr(start));
                break;
            }
            opts.push_back(optionsPart.substr(start, pos - start));
            start = pos + 1;
        }
        if (opts.size() < 2) {
            string msg = "Need at least 2 options.\n";
            send(clientSock, msg.c_str(), msg.size(), 0);
            return;
        }
        Poll pl;
        pl.pollID = pollIDCounter++;
        pl.creator = username;
        pl.question = question;
        pl.options = opts;
        pl.votes.resize(opts.size(), 0);
        pl.timestamp = time(nullptr);

        polls.push_back(pl);

        string msg = "Poll created successfully! (Poll ID: " + to_string(pl.pollID) + ")\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
    }
    else if (subCmd == "vote") {
        // remainder = <pollID> <optionIndex>
        size_t spacePos2 = remainder.find(' ');
        if (spacePos2 == string::npos) {
            string msg = "Usage: /poll vote <pollID> <optionIndex>\n";
            send(clientSock, msg.c_str(), msg.size(), 0);
            return;
        }
        int pID = stoi(remainder.substr(0, spacePos2));
        int optIndex = stoi(remainder.substr(spacePos2 + 1));

        // find poll
        auto it = find_if(polls.begin(), polls.end(), [pID](const Poll& p){
            return p.pollID == pID;
        });
        if (it == polls.end()) {
            string msg = "Poll ID not found.\n";
            send(clientSock, msg.c_str(), msg.size(), 0);
            return;
        }
        if (optIndex < 0 || optIndex >= (int)it->options.size()) {
            string msg = "Invalid option index.\n";
            send(clientSock, msg.c_str(), msg.size(), 0);
            return;
        }
        it->votes[optIndex]++;
        string msg = "Voted successfully on poll #" + to_string(pID) + "\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
    }
    else if (subCmd == "results") {
        // remainder = <pollID>
        int pID = stoi(remainder);
        auto it = find_if(polls.begin(), polls.end(), [pID](const Poll& p){
            return p.pollID == pID;
        });
        if (it == polls.end()) {
            string msg = "Poll ID not found.\n";
            send(clientSock, msg.c_str(), msg.size(), 0);
            return;
        }
        // build results
        Poll &pl = *it;
        string out = colorText("Poll #" + to_string(pl.pollID) + ": ", "35") +
                     colorText(pl.question, "36") + "\n";
        for (size_t i = 0; i < pl.options.size(); i++) {
            out += "  [" + to_string(i) + "] " + pl.options[i] + " => votes: " + to_string(pl.votes[i]) + "\n";
        }
        out += "\n";
        send(clientSock, out.c_str(), out.size(), 0);
    }
    else {
        string msg = "Unknown /poll subcommand.\n";
        send(clientSock, msg.c_str(), msg.size(), 0);
    }
}

// ---------------------
//  MAIN CLIENT HANDLER
// ---------------------
void handleClient(SOCKET clientSocket) {
    char buffer[1024];

    // 1) Credentials
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived <= 0) {
        closesocket(clientSocket);
        return;
    }
    buffer[bytesReceived] = '\0';
    string credentials(buffer);

    size_t space1 = credentials.find(' ');
    if (space1 == string::npos) {
        closesocket(clientSocket);
        return;
    }
    string action = credentials.substr(0, space1);
    size_t space2 = credentials.find(' ', space1 + 1);
    if (space2 == string::npos) {
        closesocket(clientSocket);
        return;
    }
    string username = credentials.substr(space1 + 1, space2 - space1 - 1);
    string password = credentials.substr(space2 + 1);

    // 2) Register or Login
    if (action == "R") {
        if (userCredentials.find(username) != userCredentials.end()) {
            string msg = "Username already exists";
            send(clientSocket, msg.c_str(), msg.size(), 0);
            closesocket(clientSocket);
            return;
        }
        userCredentials[username] = password;
        saveUserToFile(username, password);
        string msg = "Success";
        send(clientSocket, msg.c_str(), msg.size(), 0);
    }
    else if (action == "L") {
        auto it = userCredentials.find(username);
        if (it == userCredentials.end() || it->second != password) {
            string msg = "Invalid username or password";
            send(clientSocket, msg.c_str(), msg.size(), 0);
            closesocket(clientSocket);
            return;
        }
        string msg = "Success";
        send(clientSocket, msg.c_str(), msg.size(), 0);
    }
    else {
        string msg = "Unknown command";
        send(clientSocket, msg.c_str(), msg.size(), 0);
        closesocket(clientSocket);
        return;
    }

    onlineUsers[username] = clientSocket;

    // 3) Commands
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            cerr << "[INFO] " << username << " disconnected.\n";
            onlineUsers.erase(username);
            closesocket(clientSocket);
            return;
        }
        buffer[bytesReceived] = '\0';
        string clientMsg(buffer);

        // /post ...
        if (clientMsg.rfind("/post ", 0) == 0) {
            // /post <content>::<mediaURL?>
            string remainder = clientMsg.substr(6);
            size_t delimPos  = remainder.find("::");
            string content, media;
            if (delimPos != string::npos) {
                content = remainder.substr(0, delimPos);
                media   = remainder.substr(delimPos + 2);
            } else {
                content = remainder;
            }
            if (content.empty()) {
                string msg = "Cannot create empty post.\n";
                send(clientSocket, msg.c_str(), msg.size(), 0);
                continue;
            }

            Post newPost;
            newPost.id        = generatePostID();
            newPost.username  = username;
            newPost.content   = content;
            newPost.mediaURL  = media;
            newPost.timestamp = time(nullptr);

            feedPosts.push_back(newPost);
            savePostToFile(newPost);

            postLikes[newPost.id] = {};
            postDislikes[newPost.id] = {};

            string msg = "Post created successfully! (ID: " + to_string(newPost.id) + ")\n";
            send(clientSocket, msg.c_str(), msg.size(), 0);
        }
        // /feed
        else if (clientMsg == "/feed") {
            sort(feedPosts.begin(), feedPosts.end(), sortByTimestampDesc);
            for (auto &p : feedPosts) {
                char timeBuf[26];
                ctime_s(timeBuf, sizeof(timeBuf), &p.timestamp);
                string timeString(timeBuf);
                if (!timeString.empty() && timeString.back() == '\n') {
                    timeString.pop_back();
                }

                int likeCount    = (int)postLikes[p.id].size();
                int dislikeCount = (int)postDislikes[p.id].size();

                string feedLine = colorText("[ID=" + to_string(p.id) + "] ", "35") +
                                  colorText("[" + timeString + "] ", "33") +
                                  colorText(p.username, "36") + "\n" +
                                  "  " + colorText("Content: ", "32") + p.content + "\n";
                if (!p.mediaURL.empty()) {
                    feedLine += "  " + colorText("Media: ", "34") + p.mediaURL + "\n";
                }
                feedLine += "  " + colorText("Likes: ", "31") + to_string(likeCount) +
                            ", " + colorText("Dislikes: ", "31") + to_string(dislikeCount) + "\n\n";

                send(clientSocket, feedLine.c_str(), feedLine.size(), 0);
            }
            string endMsg = colorText("--- End of feed ---\n", "33");
            send(clientSocket, endMsg.c_str(), endMsg.size(), 0);
        }
        // /dm <target> <message>
        else if (clientMsg.rfind("/dm ", 0) == 0) {
            // must be friends
            string dmBody = clientMsg.substr(4);
            size_t spacePos = dmBody.find(' ');
            if (spacePos == string::npos) {
                string msg = "Usage: /dm <username> <message>\n";
                send(clientSocket, msg.c_str(), msg.size(), 0);
                continue;
            }
            string targetUser = dmBody.substr(0, spacePos);
            string dmMessage  = dmBody.substr(spacePos + 1);
            if (dmMessage.empty()) {
                string msg = "Cannot send empty DM.\n";
                send(clientSocket, msg.c_str(), msg.size(), 0);
                continue;
            }
            // check friend
            if (friendLists[username].find(targetUser) == friendLists[username].end()) {
                string msg = "You are not friends with " + targetUser + "\n";
                send(clientSocket, msg.c_str(), msg.size(), 0);
                continue;
            }
            auto it = onlineUsers.find(targetUser);
            if (it == onlineUsers.end()) {
                string msg = "User '" + targetUser + "' is not online.\n";
                send(clientSocket, msg.c_str(), msg.size(), 0);
            } else {
                string finalDM = colorText("[DM] from ", "35") +
                                 colorText(username, "36") + ": " +
                                 colorText(dmMessage, "32") + "\n";
                send(it->second, finalDM.c_str(), finalDM.size(), 0);

                string ack = "DM sent to " + targetUser + "\n";
                send(clientSocket, ack.c_str(), ack.size(), 0);
            }
        }
        // /like <postID>
        else if (clientMsg.rfind("/like ", 0) == 0) {
            int postID = stoi(clientMsg.substr(6));
            auto found = find_if(feedPosts.begin(), feedPosts.end(), [postID](const Post& p){
                return p.id == postID;
            });
            if (found == feedPosts.end()) {
                string msg = "Post ID not found.\n";
                send(clientSocket, msg.c_str(), msg.size(), 0);
                continue;
            }
            postDislikes[postID].erase(username);
            postLikes[postID].insert(username);

            string msg = "You liked post #" + to_string(postID) + "\n";
            send(clientSocket, msg.c_str(), msg.size(), 0);
        }
        // /dislike <postID>
        else if (clientMsg.rfind("/dislike ", 0) == 0) {
            int postID = stoi(clientMsg.substr(9));
            auto found = find_if(feedPosts.begin(), feedPosts.end(), [postID](const Post& p){
                return p.id == postID;
            });
            if (found == feedPosts.end()) {
                string msg = "Post ID not found.\n";
                send(clientSocket, msg.c_str(), msg.size(), 0);
                continue;
            }
            postLikes[postID].erase(username);
            postDislikes[postID].insert(username);

            string msg = "You disliked post #" + to_string(postID) + "\n";
            send(clientSocket, msg.c_str(), msg.size(), 0);
        }
        // /friend ...
        else if (clientMsg.rfind("/friend ", 0) == 0) {
            string subCmd = clientMsg.substr(8);
            handleFriendCommand(subCmd, username, clientSocket);
        }
        // /comment <postID> <text>
        else if (clientMsg.rfind("/comment ", 0) == 0) {
            string subCmd = clientMsg.substr(9);
            handleComment(subCmd, username, clientSocket);
        }
        // /viewpost <postID>
        else if (clientMsg.rfind("/viewpost ", 0) == 0) {
            string subCmd = clientMsg.substr(10);
            handleViewPost(subCmd, clientSocket);
        }
        // /editpost <postID> <newContent>
        else if (clientMsg.rfind("/editpost ", 0) == 0) {
            string subCmd = clientMsg.substr(10);
            handleEditPost(subCmd, username, clientSocket);
        }
        // /deletepost <postID>
        else if (clientMsg.rfind("/deletepost ", 0) == 0) {
            string subCmd = clientMsg.substr(12);
            handleDeletePost(subCmd, username, clientSocket);
        }
        // /editcomment <commentID> <newText>
        else if (clientMsg.rfind("/editcomment ", 0) == 0) {
            string subCmd = clientMsg.substr(13);
            handleEditComment(subCmd, username, clientSocket);
        }
        // /deletecomment <commentID>
        else if (clientMsg.rfind("/deletecomment ", 0) == 0) {
            string subCmd = clientMsg.substr(15);
            handleDeleteComment(subCmd, username, clientSocket);
        }
        // /poll ...
        else if (clientMsg.rfind("/poll ", 0) == 0) {
            string subCmd = clientMsg.substr(6);
            handlePollCommand(subCmd, username, clientSocket);
        }
        // /quit
        else if (clientMsg == "/quit") {
            string msg = "Goodbye!\n";
            send(clientSocket, msg.c_str(), msg.size(), 0);
            cerr << "[INFO] " << username << " disconnected via /quit.\n";
            onlineUsers.erase(username);
            closesocket(clientSocket);
            return;
        }
        // Unknown
        else {
            string msg = colorText("Unknown command.\n", "31") +
            "Available commands:\n"
            "  /post <text>::<mediaURL>    (create post)\n"
            "  /feed                       (view feed)\n"
            "  /dm <user> <message>        (direct message if friends)\n"
            "  /like <postID>, /dislike <postID>\n"
            "  /friend request <user>, /friend accept <user>\n"
            "  /comment <postID> <text>, /viewpost <postID>\n"
            "  /editpost <postID> <text>, /deletepost <postID>\n"
            "  /editcomment <cmtID> <text>, /deletecomment <cmtID>\n"
            "  /poll create..., /poll vote..., /poll results...\n"
            "  /quit\n";
            send(clientSocket, msg.c_str(), msg.size(), 0);
        }
    }
}

// ---------------------
//  MAIN
// ---------------------
int main() {
    // 1) Load existing data
    loadUsersFromFile();
    loadPostsFromFile();

    // 2) Init WinSock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "[ERROR] WSAStartup failed.\n";
        return 1;
    }

    // 3) Create server socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        cerr << "[ERROR] Socket creation failed.\n";
        WSACleanup();
        return 1;
    }

    // 4) Bind
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port   = htons(54000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "[ERROR] Bind failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // 5) Listen
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cerr << "[ERROR] Listen failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server is running on port 54000\n";

    // 6) Accept loop
    while (true) {
        sockaddr_in clientAddr;
        int clientSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
        if (clientSocket == INVALID_SOCKET) {
            cerr << "[ERROR] accept() failed.\n";
            continue;
        }
        // spawn thread
        thread t(handleClient, clientSocket);
        t.detach();
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
