//
// Created by magshimim on 26/12/17.
//


#ifndef SERVER_GAMEMAP_H
#define SERVER_GAMEMAP_H

#include <map>
#include <string>
using namespace std;


class GameMap {
public:
    static GameMap *getInstance();
    map<string,int>* getGames();
private:
    GameMap();
    static GameMap *instance;
    map<string,int>* games;
};


#endif //SERVER_GAMEMAP_H
