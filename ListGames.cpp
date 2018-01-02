//
// Created by magshimim on 27/12/17.
//

#include "ListGames.h"
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

ListGames::ListGames() {}

int ListGames::execute(vector<char *>* args, map<string,GameRoom*>* gameMap,int socket) {
    char buffer[2];
    string full = "(full)";
    string open = "(1 waiting for you)";
    for(map<string,GameRoom*>::iterator it = gameMap->begin(); it != gameMap->end(); ++it) {
        if(it->second->fullGame()) {
            write(socket, (it->first+full).c_str() , strlen((it->first+full).c_str()) + 1);
        } else {
            write(socket, (it->first+open).c_str() , strlen((it->first+open).c_str()) + 1);
        }
        read(socket, buffer, sizeof(buffer));

    }
    write(socket, "$", sizeof("$"));
    read(socket, buffer, sizeof(buffer));
    return 0;
}