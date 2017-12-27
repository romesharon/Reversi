// aviv shisman and rom sharon .
#include <map>
#include "StartGame.h"
StartGame::StartGame(){

}

void StartGame::execute(vector<char *>* args, map<string,int>* moti,int socket) {
    string str = "";
    for (int i = 0; i < args->size(); i++) {
        str += args->at(i);
        if (i + 1 == args->size()) {
            continue;
        }
        str += " ";
    }

    (*moti)[str] = socket;
    cout << (*moti).size() << endl;
}