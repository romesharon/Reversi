//
// Created by magshimim on 22/12/17.
//

#include "CommandManeger.h"
#include "StartGame.h"

CommandsManager::CommandsManager() {
    commandsMap["start"] = new StartGame();
    gameMap=gameMap->getInstance();
/*
    commandsMap["list_games"] = new ListGames();
    commandsMap["join"] = new Join();
    commandsMap["play"] = new Play();
    commandsMap["close"] = new Close();
*/

    // Add more commands...
}
void CommandsManager::executeCommand(char*
                                     command, vector<char*>* args, int socket) {
    string str(command);
    Command *commandObj = commandsMap[str];
    map<string,int>* map = gameMap->getGames();
    commandObj->execute(args,map, socket);

}
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it !=
                                   commandsMap.end(); it++) {
        delete it->second;
    }
}