//
// Created by rom on 02/12/17.
//

#ifndef ASS1_SERVER_H
#define ASS1_SERVER_H


class Server {
public:
    Server(int port);
    void start();
    void stop();

private:
    int port;
    int serverSocket;

    void handleTowClients(int clientSocket1, int clientSocket2);
};


#endif //ASS1_SERVER_H
