//
// Created by magshimim on 27/12/17.
//

#include "ListGames.h"
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

ListGames::ListGames() {}

void ListGames::execute(vector<char *>* args, map<string,GameRoom*>* gameMap,int socket) {
    char buffer[1];
    for(map<string,GameRoom*>::iterator it = gameMap->begin(); it != gameMap->end(); ++it) {
        write(socket, it->first.c_str(), strlen(it->first.c_str())+1);
        read(socket, buffer, sizeof(buffer));

    }
    write(socket, "$", sizeof("$"));
    read(socket, buffer, sizeof(buffer));

}