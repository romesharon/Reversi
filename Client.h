//
// Created by magshimim on 01/12/17.
//

#ifndef ASS1_CLIENT_H
#define ASS1_CLIENT_H


#include "Point.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

class Client {
public:
    Client(const char *serverIP, int serverPort);
    void connectToServer();
    Point sendMove(int arg1, int arg2);
private:
    const char *serverIP;
    int serverPort;
    int clientSocket;
};


#endif //ASS1_CLIENT_H
