#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <algorithm>
using namespace std;

// ========================
//       USER CLASS
// ========================
enum Status
{
    Online,
    Offline
};
class User
{
private:
    string username;
    string password;
    string phoneNumber;
    Status status;
    string lastSeen;

public:
    User()
    {
        // TODO: Implement default constructor
        username = "";
        password = "";
        phoneNumber = "";
        status = Offline;
        lastSeen = "never";
    }

    User(string uname, string pwd, string phone)
    {
        // TODO: Implement parameterized constructor
        username = uname;
        password = pwd;
        phoneNumber = phone;
        status = Offline;
        lastSeen = "";
    }

    string getUsername() const
    {
        // TODO: Implement getter
        return username;
    }

    string getPhoneNumber() const
    {
        // TODO: Implement getter

        return phoneNumber;
    }

    string getStatus() const
    {
        // TODO: Implement getter
        return (status == Online) ? "Online" : "Offline";
    }

    string getLastSeen() const
    {
        // TODO: Implement getter
        return lastSeen;
    }

    void setUsername(string uname) { username = uname; }

    void setStatus(Status newStatus)
    {
        // TODO: Implement setter
        status = newStatus;
    }

    void setPhoneNumber(string phone)
    {
        // TODO: Implement setter
        phoneNumber = phone;
    }

    void updateLastSeen()
    {
        // TODO: Implement last seen update
        time_t currentTime = time(nullptr); // get the current time
        lastSeen = ctime(&currentTime);
        // cout<<"Last seen" << lastSeen;
    }

    bool checkPassword(string pwd) const
    {
        // TODO: Implement password check
        if (pwd != password)
            return false;
        return true;
    }

    void changePassword(string newPwd)
    {
        // TODO: Implement password change
        password = newPwd;
    }

    void goOnline()
    {
        updateLastSeen();
        status = Online;
    }

    void goOffline()
    {
        updateLastSeen();
        status = Offline;
    }
};
// ========================
//      MESSAGE CLASS
// ========================
class Message
{
private:
    string sender;
    string content;
    string timestamp;
    string status;
    Message *replyTo;

public:
    Message()
    {
        // TODO: Implement default constructor
        sender = "";
        content = "";
        timestamp = "";
        status = "";
        replyTo = nullptr;
    }

    Message(string sndr, string cntnt)
    {
        // TODO: Implement parameterized constructor
        sender = sndr;
        content = cntnt;
        time_t now = time(nullptr);
        char *time_now = ctime(&now);
        timestamp = string(time_now);
        status = "Sent";
        replyTo = nullptr;
    }

    string getContent() const
    {
        // TODO: Implement getter
        return content;
    }

    string getSender() const
    {
        // TODO: Implement getter
        return sender;
    }

    string getTimestamp() const
    {
        // TODO: Implement getter
        return timestamp;
    }

    string getStatus() const
    {
        // TODO: Implement getter
        return status;
    }

    Message *getReplyTo() const
    {
        // TODO: Implement getter
        return replyTo;
    }

    void setStatus(string newStatus)
    {
        // TODO: Implement setter
        status = newStatus;
    }

    void setReplyTo(Message *msg)
    {
        // TODO: Implement setter
        replyTo = msg;
    }

    void updateTimestamp()
    {
        // TODO: Implement timestamp update
        time_t now = time(nullptr);
        timestamp = ctime(&now);
    }

    void display() const
    {
        // TODO: Implement message display
        cout << "Sender: " << getSender() << endl;
        cout << "Content: " << getContent() << endl;
        cout << "Timestamp: " << getTimestamp();
        cout << "Status: " << getStatus() << endl;
        if (getReplyTo())
        {
            Message *s = getReplyTo();
            Message m = *s;
            cout << "Reply To: " << m.getSender() << endl;
        }
        else
            cout << "Reply To: No reply" << endl;
    }

    void addEmoji(string emojiCode)
    {
        // TODO: Implement emoji support
        string s;
        if (emojiCode == "1")
        {
            s = u8"\U0001F603"; // Smiling face
        }

        else if (emojiCode == "2")
        {
            s = u8"\U0001F609"; // Winking face
        }

        else if (emojiCode == "3")
        {
            s = u8"\U0001F602"; // Laughing with tears
        }

        else if (emojiCode == "4")
        {
            s = u8"\U0001F621"; // Angry face
        }

        else if (emojiCode == "5")
        {
            s = u8"\U0001F622"; // Tearing "sad" face
        }

        else if (emojiCode == "6")
        {
            s = u8"\U0001F62D"; // Crying face
        }

        else if (emojiCode == "7")
        {
            s = u8"\U0001F632"; // Astonished face
        }

        else if (emojiCode == "8")
        {
            s = u8"\U00002764"; // Black Heart
        }

        else if (emojiCode == "9")
        {
            s = u8"\U0001F497"; // Growing Red heart
        }

        else if (emojiCode == "10")
        {
            s = u8"\U0001F494"; // Broken Red Heart
        }

        else if (emojiCode == "11")
        {
            s = u8"\U0001F44D"; // Thumbs up
        }

        else if (emojiCode == "12")
        {
            s = u8"\U0001F44E"; // Thumbs down
        }

        else
            return;

        content += s;
    }
};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat
{
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;

public:
    Chat()
    {
        chatName = "Unnamed Chat";
    }

    Chat(vector<string> users, string name)
    {
        participants = users;
        chatName = name;
    }

    vector<string> getparticipants()
    {
        return participants;
    }
    vector<Message> &getMessages()
    {
        return messages;
    }

    void addMessage(const Message &msg)
    {
        messages.push_back(msg);
    }

    bool deleteMessage(int index, const string &username)
    {
        if (index >= 0 && index < messages.size())
        {
            if (messages[index].getSender() == username)
            {
                messages.erase(messages.begin() + index);
                return true;
            }
        }
        return false;
    }

    virtual void displayChat() const
    {
        cout << "Chat Name: " << chatName << "\nParticipants: ";
        for (const auto &user : participants)
        {
            cout << user << " ";
        }
        cout << "\nMessages:\n";
        for (const auto &msg : messages)
        {
            msg.display();
        }
    }

    vector<Message> searchMessages(string keyword) const
    {
        vector<Message> result;
        for (const auto &msg : messages)
        {
            if (msg.getContent().find(keyword) != string::npos)
            {
                result.push_back(msg);
            }
        }
        return result;
    }

    void exportToFile(const string &filename) const
    {
        ofstream outFile(filename);
        if (!outFile.is_open())
        {
            cout << "Error opening file.\n";
            return;
        }

        outFile << "Chat Type: " << (participants.size() == 2 ? "Private" : "Group") << "\n";
        outFile << "Chat Name: " << chatName << "\n";

        outFile << "Participants: ";
        if (participants.empty())
        {
            outFile << "None";
        }
        else
        {
            for (const auto &user : participants)
            {
                outFile << user << " ";
            }
        }
        outFile << "\n";

        outFile << "Messages:\n";
        if (messages.empty())
        {
            outFile << "No messages yet.\n";
        }
        else
        {
            for (const auto &msg : messages)
            {
                if (msg.getSender().empty() || msg.getContent().empty())
                {
                    outFile << "[Invalid message]\n";
                    continue;
                }
                outFile << "[" << msg.getTimestamp() << "] " << msg.getSender()
                        << ": " << msg.getContent() << " [" << msg.getStatus() << "]\n";
            }
        }

        outFile.close();
        cout << "Chat exported to " << filename << "\n";
    }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat
{
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2)
    {
        // TODO: Implement constructor
        if (u1 == u2)
        {
            cout << "Both participants cannot\nhave the same name." << endl;
            return;
        }

        user1 = u1;
        user2 = u2;
        participants.push_back(user1);
        participants.push_back(user2);
    }

    void displayChat() const override
    {
        // TODO: Implement private chat display
        cout << "Chat History." << endl;
        for (Message msg : messages)
        {
            msg.display();
        }
    }

    void showTypingIndicator(const string &username) const
    {
        // TODO: Implement typing indicator
        cout << username << " Is Typing..." << endl;
    }
};

// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat
{
private:
    vector<string> admins;
    string description;

public:
    GroupChat(vector<string> users, string name, string creator)
    {
        participants = users;
        chatName = name;

        if (!isParticipant(creator))
        {
            participants.push_back(creator);
        }
        admins.push_back(creator);
    }

    void addAdmin(string newAdmin)
    {
        if (isParticipant(newAdmin) && !isAdmin(newAdmin))
        {
            admins.push_back(newAdmin);
            cout << newAdmin << " is now an admin. \n";
        }
        else
        {
            cout << "Cannot add admin. \n";
        }
    }

    bool removeParticipant(const string &admin, const string &userToRemove)
    {
        if (!isAdmin(admin))
        {
            cout << admin << " is not an admin. \n";
            return false;
        }
        for (int i = 0; i < participants.size(); i++)
        {
            if (participants[i] == userToRemove)
            {
                participants.erase(participants.begin() + i);
                for (int j = 0; j < admins.size(); j++)
                {
                    if (admins[j] == userToRemove)
                    {
                        admins.erase(admins.begin() + j);
                        break;
                    }
                }
                cout << userToRemove << " has been removed. \n";
                return true;
            }
        }
        return false;
    }

    bool isAdmin(string username) const
    {
        for (int i = 0; i < admins.size(); i++)
        {
            if (admins[i] == username)
                return true;
        }
        return false;
    }

    bool isParticipant(string username) const
    {
        for (int i = 0; i < participants.size(); i++)
        {
            if (participants[i] == username)
                return true;
        }
        return false;
    }

    void setDescription(string desc)
    {
        description = desc;
    }

    void displayChat() const override
    {
        cout << "=== Group: " << chatName << " ===\n";
        cout << "Description: " << description << "\n";
        cout << "Participants (" << participants.size() << "): ";
        for (int i = 0; i < participants.size(); i++)
        {
            cout << participants[i];
            if (isAdmin(participants[i]))
                cout << " (admin)";
            if (i != participants.size() - 1)
                cout << ", ";
        }
        cout << "\n\nMessages (" << messages.size() << "):\n";
        for (Message msg : messages)
        {
            msg.display();
        }
    }

    void sendJoinRequest(const string &username)
    {
        cout << username << " sent a join request. \n";
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp
{
private:
    vector<User> users;
    vector<Chat *> chats;
    int currentUserIndex;

    int findUserIndex(string username) const
    {
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].getUsername() == username)
                return i;
        }
        return -1;
    }

    bool isLoggedIn() const
    {
        if (currentUserIndex != -1)
            return true;
        else
            return false;
    }

    string getCurrentUsername() const
    {
        if (isLoggedIn())
        {
            return users[currentUserIndex].getUsername();
        }
        return "None";
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    void signUp()
    {
        string username;
        string password;
        string phone;

        cout << "Please enter a username: ";
        cin >> username;
        if (findUserIndex(username) != -1)
        {
            cout << "This username is TAKEN!" << endl;
            return;
        }

        cout << "Please enter password: ";
        cin >> password;
        cout << "Please enter phone number: ";
        cin >> phone;

        users.push_back(User(username, password, phone));
        cout << "You Are Now Registered. Please LogIn Now";
    }

    void login()
    {
        if (isLoggedIn())
        {
            cout << "You are logged in already " << endl;
            return;
        }

        string username;
        string password;

        cout << "Please enter username: ";
        cin >> username;

        if (findUserIndex(username) == -1)
        {
            cout << "Username not found" << endl;
            return;
        }

        cout << "Please enter password: ";
        cin >> password;

        if (!users[findUserIndex(username)].checkPassword(password))
        {
            cout << "Wrong password!" << endl;
            return;
        }

        currentUserIndex = findUserIndex(username);
        users[findUserIndex(username)].goOnline();
        // once the current user be online all the sent messages will be converted to delivered.
        for (Chat *ch : chats)
        {
            for (Message &m : ch->getMessages())
            {
                if (m.getSender() != users[currentUserIndex].getUsername() && m.getStatus() == "sent")
                {
                    m.setStatus("delivered");
                }
            }
        }

        cout << "Welcome back " << username << endl;
    }

    void startPrivateChat()
    {
        // TODO: Implement private chat creation
        do
        {
            int choice;
            cout << "Choose the user you want to chat with: (enter 0  if u want to leave.)" << endl;
            for (int i = 0; i < users.size(); i++)
            {
                cout << i + 1 << " -> " << users[i].getUsername() << endl;
            }

            while (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Please enter a number: ";
            }

            if (choice == 0)
                break;
            choice--; // adjust to 0-based index

            PrivateChat *existingChat;

            bool chatISFound = false;

            for (Chat *i : chats)
            {
                vector<string> partici = i->getparticipants();

                if (partici.size() == 2)
                {
                    if ((partici[0] == users[currentUserIndex].getUsername() && partici[1] == users[choice].getUsername()) || (partici[0] == users[choice].getUsername() && partici[1] == users[currentUserIndex].getUsername()))
                    {
                        existingChat = static_cast<PrivateChat *>(i);
                        chatISFound = true;
                        break;
                    }
                }
            }

            if (!(chatISFound))
            {
                existingChat = new PrivateChat(users[currentUserIndex].getUsername(), users[choice].getUsername());
                chats.push_back(existingChat);
            }

            bool viewed = false;
            while (true)
            {
                cout << "==== Chat Features Menu ====" << endl;
                int chosenFeature;
                cout << 1 << ". View Messages" << endl;
                cout << 2 << ". Send Message" << endl;
                cout << 3 << ". Delete a Message" << endl;
                cout << 4 << ". Search Messages" << endl;
                cout << 5 << ". reply To a Message" << endl;
                cout << 6 << ". Exit Chat" << endl;

                while (!(cin >> chosenFeature))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input! Please enter a number: ";
                }

                if (chosenFeature == 1)
                {
                    // (&m) to modify the message itself not the copy version.
                    for (Message &m : existingChat->getMessages())
                    {
                        if (m.getSender() == users[choice].getUsername())
                        {
                            m.setStatus("read");
                        }
                    }
                    string partnerUsername = users[choice].getUsername();
                    cout << partnerUsername << " is "
                         << users[findUserIndex(partnerUsername)].getStatus() << endl;
                    cout << "Last seen: "
                         << users[findUserIndex(partnerUsername)].getLastSeen() << endl;

                    existingChat->displayChat();
                    viewed = true;
                }

                else if (!(viewed))
                {
                    cout << "Please view chat first before modifying" << endl;
                    continue;
                }

                else if (chosenFeature == 2)
                {

                    cout << "Chatting with " << users[choice].getUsername() << endl;
                    while (true)
                    {
                        int exit;
                        string content;
                        cout << "Enter 0 to leave:";

                        while (!(cin >> exit))
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input! Please enter a number: ";
                        }
                        if (exit == 0)
                            break;
                        cout << "Type message (exit to leave): ";
                        cin.ignore(); //<---
                        getline(cin, content);
                        Message msg(users[currentUserIndex].getUsername(), content);
                        string isAgreed;
                        cout << "Do you want to add emoji." << endl;
                        cin >> isAgreed;

                        while (isAgreed == "y" || isAgreed == "Y")
                        {
                            cout << 1 << " smiling face." << endl;
                            cout << 2 << " winking face." << endl;
                            cout << 3 << " laughing with tears." << endl;
                            cout << 4 << " angry face." << endl;
                            cout << 5 << " sad face." << endl;
                            cout << 6 << " crying face." << endl;
                            cout << 7 << " astonished face." << endl;
                            cout << 8 << " black heart." << endl;
                            cout << 9 << " growing red heart." << endl;
                            cout << 10 << " broken red heart." << endl;
                            cout << 11 << " thumbs up." << endl;
                            cout << 12 << " thumbs down." << endl;
                            cout << "any thing exept these 12 options will not add any thing" << endl;
                            string emjiCode;
                            cout << "you input: " << endl;
                            cin >> emjiCode;
                            msg.addEmoji(emjiCode);

                            cout << "Do you to add more emojs(y/n)." << endl;
                            cin >> isAgreed;
                        }

                        existingChat->addMessage(msg);
                    }
                }

                else if (chosenFeature == 3)
                {
                    int choose;
                    vector<Message> temp = existingChat->getMessages();
                    for (int i = 0; i < temp.size(); i++)
                    {
                        cout << i << " -> ";
                        temp[i].display();
                        cout << endl;
                    }
                    cout << "Choose on the message you want to delete: ";

                    while (!(cin >> choose))
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Please enter a number: ";
                    }

                    if ((!choose > 0) && (!(choose > temp.size())))
                    {
                        existingChat->deleteMessage(choose, temp[choose].getSender());
                        cout << "The Message sent by " << temp[choose].getSender() << "is deleted." << endl;
                        existingChat->displayChat();
                    }
                    else
                    {
                        cout << "out of range" << endl;
                    }
                }

                else if (chosenFeature == 4)
                {
                    string search;
                    cout << "Enter a the keyword to search for a message: " << endl;
                    cin >> search;
                    vector<Message> result = existingChat->searchMessages(search);
                    if (!(result.empty()))
                    {
                        for (Message msg : result)
                        {
                            msg.display();
                        }
                    }
                    else
                    {
                        cout << "No messages found" << endl;
                    }
                }

                else if (chosenFeature == 5)
                {
                    // to work on the original vectors and to avoid coies that can increase the time.
                    vector<Message> &msg = existingChat->getMessages();
                    for (int i = 0; i < msg.size(); i++)
                    {
                        cout << i << " -> ";
                        msg[i].display();
                    }
                    int replyTO;
                    cout << "Choose the message you want to reply to: ";

                    while (!(cin >> replyTO))
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Please enter a number: ";
                    }
                    // for the 0 index
                    Message *found = &msg[replyTO]; // The original message

                    string reply;
                    cout << "The reply content: " << endl;
                    cin.ignore();
                    getline(cin, reply);

                    Message ReplyMsg(users[currentUserIndex].getUsername(), reply);
                    ReplyMsg.setReplyTo(found);

                    existingChat->addMessage(ReplyMsg);
                }
                else
                {
                    break;
                }
            }

        } while (true);
    }

    void createGroup()
    {
        // TODO: Implement group creation
        do
        {
            int option;
            cout << 1 << ". Append on a group chat." << endl;
            cout << 2 << ". Create a new chat.\n"
                 << endl;
            cout << "select an option:";

            while (!(cin >> option))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Please enter a number: ";
            }
            GroupChat *CurrentGroupChat;

            if (option == 1)
            {
                for (int i = 0; i < chats.size(); i++)
                {
                    GroupChat *gp;
                    if (chats[i]->getparticipants().size() > 2)
                    {
                        gp = static_cast<GroupChat *>(chats[i]);

                        auto participant = chats[i]->getparticipants();

                        auto it = find(participant.begin(), participant.end(), users[currentUserIndex].getUsername());
                        if (it != participant.end())
                        {
                            cout << i;
                            gp->displayChat();
                        }
                    }
                }
                int choice;
                cout << "Choose one of the chatting groups your in:";

                while (!(cin >> choice))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input! Please enter a number: ";
                }
                if (!(choice < 0) || !(choice > chats.size()))
                {
                    CurrentGroupChat = static_cast<GroupChat *>(chats[choice]);
                }
                else
                {
                    cout << "out of range." << endl;
                }
            }

            if (option == 2)
            {
                for (int i = 0; i < users.size(); i++)
                {
                    cout << i + 1 << " -> " << users[i].getUsername() << endl;
                }
                vector<string> groupMemebers;
                groupMemebers.push_back(users[currentUserIndex].getUsername());
                while (true)
                {
                    int choose;
                    cout << "choose the users you want them to be the memebers of you group:\n (enter 0 to stop choosing)" << endl;

                    while (!(cin >> choose))
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Please enter a number: ";
                    }

                    if (0 == choose)
                    {
                        if (groupMemebers.size() > 2)
                        {
                            break;
                        }
                        else
                        {
                            cout << "you should have at least 3 numbers." << endl;
                            continue;
                        }
                    }

                    if (choose < 1 || choose > users.size())
                    {
                        cout << "this user doesn't exit." << endl;
                        continue;
                    }

                    choose--;
                    bool userIsFound = false;
                    for (string s : groupMemebers)
                    {
                        if (s == users[choose].getUsername())
                        {
                            cout << "This user is already in the group" << endl;
                            userIsFound = true;
                            break;
                        }
                    }
                    if (!(userIsFound))
                    {
                        groupMemebers.push_back(users[choose].getUsername());
                    }
                }

                string ChatName;
                cout << "Group name: ";
                cin >> ChatName;

                string desc;
                cout << "Enter a description for your group: " << endl;
                cin.ignore();
                getline(cin, desc);

                CurrentGroupChat = new GroupChat(groupMemebers, ChatName, users[currentUserIndex].getUsername());
                CurrentGroupChat->setDescription(desc);
                chats.push_back(CurrentGroupChat);
            }

            bool viewed = false;
            while (true)
            {
                cout << "==== Chat Features Menu ====" << endl;
                int chosenFeature;
                cout << 1 << ". View Messages" << endl;
                cout << 2 << ". Send Message" << endl;
                cout << 3 << ". Delete a Message" << endl;
                cout << 4 << ". Search Messages" << endl;
                cout << 5 << ". replay To a Message" << endl;
                cout << 6 << ". add admin" << endl;
                cout << 7 << ". kick a participant" << endl;
                cout << 8 << ". Exit Chat" << endl;

                while (!(cin >> chosenFeature))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input! Please enter a number: ";
                }

                if (chosenFeature == 1)
                {
                    for (Message &m : CurrentGroupChat->getMessages())
                    {
                        if (m.getSender() != users[currentUserIndex].getUsername())
                        {
                            m.setStatus("read");
                        }
                    }
                    CurrentGroupChat->displayChat();
                    viewed = true;
                }
                else if (!(viewed))
                {
                    cout << "Please view the chat before any modification\n";
                    continue;
                }
                else if (chosenFeature == 2)
                {
                    while (true)
                    {
                        int exit;
                        string content;
                        cout << "Enter 0 to leave: ";

                        while (!(cin >> exit))
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input! Please enter a number: ";
                        }
                        if (exit == 0)
                            break;

                        cout << "write the message you want to send: (Enter exit to leave)" << endl;
                        cin.ignore();
                        getline(cin, content);
                        Message msg(users[currentUserIndex].getUsername(), content);
                        string isAgreed;
                        cout << "Do you want to add emoji(y/n)." << endl;
                        cin >> isAgreed;

                        while (isAgreed == "y" || isAgreed == "Y")
                        {
                            cout << 1 << " smiling face." << endl;
                            cout << 2 << " winking face." << endl;
                            cout << 3 << " laughing with tears." << endl;
                            cout << 4 << " angry face." << endl;
                            cout << 5 << " sad face." << endl;
                            cout << 6 << " crying face." << endl;
                            cout << 7 << " astonished face." << endl;
                            cout << 8 << " black heart." << endl;
                            cout << 9 << " growing red heart." << endl;
                            cout << 10 << " broken red heart." << endl;
                            cout << 11 << " thumbs up." << endl;
                            cout << 12 << " thumbs down." << endl;
                            cout << "any thing exept these 12 options will not add any thing" << endl;
                            string emjiCode;
                            cout << "you input: " << endl;
                            cin >> emjiCode;
                            msg.addEmoji(emjiCode);

                            cout << "Do you to add more emojs(y/n)." << endl;
                            cin >> isAgreed;
                        }

                        CurrentGroupChat->addMessage(msg);
                    }
                }
                else if (chosenFeature == 3)
                {
                    int choose;
                    vector<Message> temp = CurrentGroupChat->getMessages();
                    for (int i = 0; i < temp.size(); i++)
                    {
                        cout << i << " -> ";
                        temp[i].display();
                        cout << endl;
                    }
                    cout << "Choose on the message you want to delete: ";

                    while (!(cin >> choose))
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Please enter a number: ";
                    }
                    if (!(choose < 0) || !(choose > temp.size()))
                    {
                        CurrentGroupChat->deleteMessage(choose, temp[choose].getSender());
                        cout << "The Message sent by " << temp[choose].getSender() << "is deleted." << endl;
                        CurrentGroupChat->displayChat();
                    }
                    else
                    {
                        cout << "Out of range" << endl;
                    }
                }
                else if (chosenFeature == 4)
                {
                    string keyword;
                    cout << "Enter a keyword to search for a messsage: ";
                    cin >> keyword;
                    vector<Message> result = CurrentGroupChat->searchMessages(keyword);

                    if (!(result.empty()))
                    {
                        cout << "Here is the message you searched for." << endl;
                        for (Message m : result)
                        {
                            m.display();
                        }
                    }
                }
                else if (chosenFeature == 5)
                {
                    vector<Message> &messages = CurrentGroupChat->getMessages();
                    for (int i = 0; i < messages.size(); i++)
                    {
                        cout << i + 1 << " ";
                        messages[i].display();
                        cout << endl;
                    }
                    int choose;
                    cout << "choose the message you want to reply to: ";

                    while (!(cin >> choose))
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Please enter a number: ";
                    }

                    string reply;
                    cout << "The reply content: " << endl;

                    cin.ignore();
                    getline(cin, reply);
                    Message ReplyMsg(users[currentUserIndex].getUsername(), reply);

                    ReplyMsg.setReplyTo(&messages[choose]);

                    CurrentGroupChat->addMessage(ReplyMsg);
                }
                else if (chosenFeature == 6)
                {
                    vector<string> allParticipants = CurrentGroupChat->getparticipants();
                    for (int i = 0; i < allParticipants.size(); i++)
                    {
                        cout << i << "->" << allParticipants[i] << endl;
                    }
                    int WhichParticipant;
                    cout << "Which participant do you wnat to promote as an admin: ";

                    while (!(cin >> WhichParticipant))
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Please enter a number: ";
                    }

                    CurrentGroupChat->addAdmin(allParticipants[WhichParticipant]);
                }
                else if (chosenFeature == 7)
                {
                    vector<string> allParticipants = CurrentGroupChat->getparticipants();
                    for (int i = 0; i < allParticipants.size(); i++)
                    {
                        cout << i << "->" << allParticipants[i] << endl;
                    }
                    int remove;
                    cout << "Which participant do you wnat to promote as an admin: ";

                    while (!(cin >> remove))
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Please enter a number: ";
                    }

                    CurrentGroupChat->removeParticipant(users[currentUserIndex].getUsername(), allParticipants[remove]);
                }
                else if (chosenFeature == 8)
                {
                    char YesOrNo;
                    cout << "Do you want to back to options menu: (y/n)";
                    cin >> YesOrNo;
                    if (YesOrNo == 'n' || YesOrNo == 'N')
                    {
                        return;
                    }
                    break;
                }
            }

        } while (true);
    }

    void viewChats() const
    {
        // TODO: Implement chat viewing
        string privateOrGroup;
        cout << "Do you want The priavte chats or the group chats: ";
        cin >> privateOrGroup;
        if (privateOrGroup == "private")
        {
            for (Chat *c : chats)
            {
                if (c->getparticipants().size() == 2)
                {
                    c->displayChat();
                }
            }
        }
        else
        {
            for (Chat *c : chats)
            {
                if (c->getparticipants().size() > 2)
                {
                    c->displayChat();
                }
            }
        }
    }

    void logout()
    {
        // TODO: Implement logout
        if (!(isLoggedIn()))
        {
            cout << "Your not logged in." << endl;
            return;
        }

        users[currentUserIndex].goOffline();
        cout << "Good Bye" << users[currentUserIndex].getUsername() << endl;
        currentUserIndex = -1;
    }

    void run()
    {
        while (true)
        {
            if (!isLoggedIn())
            {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                while (!(cin >> choice))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input! Please enter a number: ";
                }

                if (choice == 1)
                    login();
                else if (choice == 2)
                    signUp();
                else if (choice == 3)
                    break;
            }
            else
            {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                while (!(cin >> choice))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input! Please enter a number: ";
                }

                if (choice == 1)
                    startPrivateChat();
                else if (choice == 2)
                    createGroup();
                else if (choice == 3)
                    viewChats();
                else if (choice == 4)
                    logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
