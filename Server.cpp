//
// Created by rom on 02/12/17.
//

#include"Server.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

using namespace std;

#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port) : port(port), serverSocket(0){
    cout << "Server" << endl;
}

void Server::start(){
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);

    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;

    while (true) {
        cout << "Waiting for client connectios..." << endl;
        // Accept a new client connection
        int clientSocket1 = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (clientSocket1 == -1) {
            throw "Error on accept";
        }
        int clientSocket2 = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (clientSocket2 == -1) {
            throw "Error on accept";
        }
        handleTowClients(clientSocket1, clientSocket2);
        close(clientSocket1);
        close(clientSocket2);
    }
    close(serverSocket);
}


bool readFromSocket(int clientSocket, string* data, int size) {
    int byte = read(clientSocket, data, sizeof(data));
    if (byte == -1) {
        cout << "Error reading player move" << endl;
        return false;
    }
    if (byte == 0) {
        cout <<"Client disconnected" << endl;
        return false;
    }
    return true;
}


void Server::handleTowClients(int clientSocket1, int clientSocket2){
    string data;
    while(true) {
        // Read new move from 1
        if(readFromSocket(clientSocket1, &data, sizeof(data))) {
            return;
        }
        if (!data.compare("End")) {
            return;
        }
        // Send move to player 2
        int byte = write(clientSocket2, &data, sizeof(data));
        if(byte == -1) {
            cout << "Error writing to player2" << endl;
            return;
        }
        // Read new move from 2
        if(readFromSocket(clientSocket2, &data, sizeof(data))) {
            return;
        }
        if (!data.compare("End")) {
            return;
        }
        // Send move to player 1
        byte = write(clientSocket1, &data, sizeof(data));
        if(byte == -1) {
            cout << "Error writing to player1" << endl;
            return;
        }
    }
}
