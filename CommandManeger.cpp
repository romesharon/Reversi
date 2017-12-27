//
// Created by magshimim on 22/12/17.
//

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
void CommandsManager::executeCommand(char*
                                     command, vector<char*>* args, int socket) {
    string str(command);
    Command *commandObj = commandsMap[str];
    map<string,GameRoom*>* map = gameMap->getGames();
    commandObj->execute(args,map, socket);

}
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it !=
                                   commandsMap.end(); it++) {
        delete it->second;
    }
}