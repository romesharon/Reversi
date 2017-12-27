//
// Created by magshimim on 22/12/17.
//

#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H

#include <vector>
#include <string>
#include "GameRoom.h"
#include <iostream>
#include <map>

using namespace std;
class Command {
public:
    virtual void execute(vector<char*>* , map<string,GameRoom*>* , int) = 0;
    virtual ~Command() {};
    string getStringFromVector(vector<char *>* args) {
        string str = "";
        for (int i = 0; i < args->size(); i++) {
            str += args->at(i);
            if (i + 1 == args->size()) {
                continue;
            }
            str += " ";
        }
        return  str;
    }

};
#endif //SERVER_COMMAND_H
