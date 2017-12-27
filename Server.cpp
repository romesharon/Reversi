/*aviv shisman 206558157 and rom sharon
 * the server:
 */
#include "Server.h"
#include "CommandManeger.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
using namespace std;

#define MAX_CONNECTED_CLIENTS 6
/*
 * constructor
 */
Server::Server(int port) : port(port), serverSocket(0){
    cout << "Server" << endl;
}
/*
 * initializing the server and start the game
 */
void Server::start(){
    int clientSocket1 = 0;
    vector<pthread_t>* threads = new vector<pthread_t>();
    int counter = 0;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    //local host
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
    int key = 0;

    while (true) {
        cout << "Waiting for client connectios..." << endl;

        // Accept a new client connection
        clientSocket1 = accept(serverSocket, (struct sockaddr *)
                &clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        //if accept had an error
        if (clientSocket1 == -1) {
            throw "Error on accept";
        }
        pthread_t temp;
        threads->push_back(temp);
        pthread_create(&threads->at(counter), NULL,handleClient,(void*)&clientSocket1);
        //the game
        counter++;
    }
    //closing the server with thread!!
}

void* Server::handleClient(void * client) {
    //closing the server and clients sockets
    CommandsManager commandsManager;
    int i = 0;
    vector<char*> *args= new vector<char*>;
    int clientSocket1 = *((int*)client);
    char buffer[100];
    char command[100] = {'\0'};
    int byte = read(clientSocket1, buffer, sizeof(buffer));
    int flag=1;
    int j=0;
    int h = 0;
    char* param;
    while(buffer[i] != '\0') {
        if(flag && buffer[i] != ' ') {
            command[i]=buffer[i];
        }
        if(buffer[i]==' ') {
            if(!flag) {
                args->push_back(param);
            }
            param=new char[100];
            flag=0;
            j=0;
            i++;
            continue;
        }
        else if (!flag){
            param[j] = buffer[i];
        }
        i++;
        j++;
    }
    args->push_back(param);

    commandsManager.executeCommand(command, args, clientSocket1);
    close(clientSocket1);
}

/*the game itself
 * the loop of the game- getting information and passing it to the other client
 */
void Server::handleTowClients(int clientSocket1, int clientSocket2){

    while (true) {
        int x;
        int y;
        // Read new move from 1
        int byte = read(clientSocket1, &x, sizeof(x));
        if (byte == -1) {
            cout << "Error reading player move" << endl;
            return;
        }
        if (byte == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        byte = read(clientSocket1, &y, sizeof(y));
        if (byte == -1) {
            cout << "Error reading player move" << endl;
            return;
        }
        if (byte == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        //means game over
        if(x == -1 && y == -1) {
            return;
        }
        // Send move to player 2
        byte = write(clientSocket2, &x, sizeof(x));
        if (byte == -1) {
            cout << "Error writing to player2" << endl;
            return;
        }
        byte = write(clientSocket2, &y, sizeof(y));
        if (byte == -1) {
            cout << "Error writing to player2" << endl;
            return;
        }
        // Read new move from 2
        byte = read(clientSocket2, &x, sizeof(x));
        if (byte == -1) {
            cout << "Error reading player move" << endl;
            return;
        }
        if (byte == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        byte = read(clientSocket2, &y, sizeof(y));
        if (byte == -1) {
            cout << "Error reading player move" << endl;
            return;
        }
        if (byte == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        //game over
        if(x == -1 && y == -1) {
            return;
        }
        //writing the move to player 2
        byte = write(clientSocket1, &x, sizeof(x));
        if (byte == -1) {
            cout << "Error writing to player2" << endl;
            return;
        }
        byte = write(clientSocket1, &y, sizeof(y));
        if (byte == -1) {
            cout << "Error writing to player2" << endl;
            return;
        }
    }
}