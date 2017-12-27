/*aviv shisman 206558157 and rom sharon*/

#include "Client.h"
#include <sstream>
#include <cstdio>
#include <string>

using namespace std;

/*client constructor
 * creating the client
 */
Client::Client(const char *sIP, int sPort){
    serverIP = sIP;
    serverPort = sPort;
    clientSocket = 0;
}

void Client::sendMove(int arg1, int arg2){
    // giving the chosen point to the server
    int n = write(clientSocket,&arg1, sizeof(arg1));
    if (n == -1) {
        throw "Error writing arg1 to socket";
    }
    n = write(clientSocket,&arg2, sizeof(arg2));
    if (n == -1) {
        throw "Error writing arg1 to socket";
    }
}
void Client::sentString(const char* str){
    int n = write(clientSocket,str, strlen(str)+1);
    if (n == -1) {
        throw "Error writing arg1 to socket";
    }
}
/*
 * recive which player are you 'x' or 'o'
 */
int Client::recvKey(){
    int key;
    int n = read(clientSocket, &key, sizeof(key));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    return key;
}

Point* Client::readMove(){
    int x, y, end;
    cout << "Waiting for the other player to play..." << endl;
    // Read the new point from the server
    int n = read(clientSocket, &x, sizeof(x));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    n = read(clientSocket, &y, sizeof(y));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    return new Point(x, y);
}

void Client::connectToServer(){
    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }

    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }

    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *) &address, sizeof(address), AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }

    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *) &address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *) &serverAddress.sin_addr.s_addr, (char *) server->h_addr, server->h_length);

    // htons converts values between host and network byt orders
    serverAddress.sin_port = htons(serverPort);

    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
    cout << "Connected to server" << endl;
}

void Client::start() {
    int result = 0;

    printMenu();
    getchar();
    do {
        string option;
        char buffer[100] = {'\0'};
        cout << "Enter you command here: " << endl;
        getline(std::cin, option);
        cout<<strlen(option.c_str())<<endl;
        sentString(option.c_str());
        if (!strcmp("list_games", option.c_str())) {
            result = 1;
            int n = read(clientSocket, buffer, sizeof(buffer));
            write(clientSocket, "y", sizeof("y"));

            while (buffer[0] != '$') {

                cout << buffer << endl;
                int n = read(clientSocket, buffer, sizeof(buffer));
                write(clientSocket, "y", sizeof("y"));

            }
        } else {
            int n = read(clientSocket, &result, sizeof(result));
            cout << "AFTER READ" << endl;
            if(!result) {
                cout << "Error wrong command" << endl;
            }
            write(clientSocket, "y", sizeof("y"));
        }
    }while (result == 0);
}

void Client::printMenu() {
    cout << endl << "Hello player!!!" << endl;
    cout << "Welcome to the online game space" << endl;
    cout << "Here some usefull commands 4 you :)" << endl << endl;
    cout << "start <name> - to start new game called name" << endl;
    cout << "list_games   - get list of the open games you can join" << endl;
    cout << "join <name>  - join a player that currently waiting in the room-> name"<<endl;
    cout << "play <X> <Y> - make a move in the current game" << endl;
    cout << "close <name> - finish the game name" << endl;
}