//
// Created by magshimim on 22/12/17.
//

#ifndef SERVER_STARTGAME_H
#define SERVER_STARTGAME_H

#include "Command.h"

class StartGame: public Command {
public:
    StartGame();
    void execute(vector<char *>* args,map<string,GameRoom*>*, int);
};

#endif //SERVER_STARTGAME_H

