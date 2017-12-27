//
// Created by magshimim on 26/12/17.
//

#include "GameMap.h"

GameMap* GameMap::instance = 0;
GameMap* GameMap::getInstance() {
    if(!instance) {
        instance = new GameMap();
        return  instance;
    }
    else {
        return  instance;
    }
}

map<string,int>* GameMap::getGames() {
    return games;
}
GameMap::GameMap() {
    games = new map<string,int >();
}