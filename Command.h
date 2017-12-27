//
// Created by magshimim on 22/12/17.
//

#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H

#include <vector>
#include <string>

using namespace std;
class Command {
public:
    virtual void execute(vector<char*>*,map<string,int>*, int) = 0;
    virtual ~Command() {};

};
#endif //SERVER_COMMAND_H
