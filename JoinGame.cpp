//
// Created by magshimim on 27/12/17.
//

#include <unistd.h>
#include "JoinGame.h"

JoinGame::JoinGame() {}

void JoinGame::execute(vector<char *>* args, map<string,GameRoom*>* gameMap,int socket) {
    char buffer[2];
    int ok = 1;
    int wrong = 0;
    string str = getStringFromVector(args);
    //the game is exist
    if (gameMap->find(str) != gameMap->end()) {
        cout << "joining the game: " << str << endl;
        write(socket, &ok ,sizeof(ok));
        read(socket, buffer, sizeof(buffer));
        (*gameMap)[str]->setSecondPlayer(socket);
        (*gameMap)[str]->handleTowClients();
    } else {
        write(socket, &wrong ,sizeof(wrong));
        read(socket, buffer, sizeof(buffer));
    }
}