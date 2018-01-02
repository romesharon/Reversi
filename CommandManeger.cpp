//
// Created by magshimim on 22/12/17.
//

#include <unistd.h>
#include "CommandManeger.h"
#include "StartGame.h"
#include "JoinGame.h"
#include "ListGames.h"

CommandsManager::CommandsManager() {
commandsMap["start"] = new StartGame();
commandsMap["join"] = new JoinGame();
commandsMap["list_games"] = new ListGames();
gameMap=gameMap->getInstance();
/*
commandsMap["play"] = new Play();
commandsMap["close"] = new Close();
*/

// Add more commands...
}
int CommandsManager::executeCommand(char*
                                 command, vector<char*>* args, int socket) {
    int wrong = 0;
    string str(command);
    Command *commandObj = commandsMap[str];
    if (commandObj == NULL) {
        write(socket, &wrong, sizeof(wrong));
        read(socket, &wrong, sizeof(wrong));
        return 0;
    } else {
        map<string, GameRoom *> *map = gameMap->getGames();
        return commandObj->execute(args, map, socket);
    }
}
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it !=
                                   commandsMap.end(); it++) {
        delete it->second;
    }
}

