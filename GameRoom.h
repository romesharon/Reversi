//
// Created by magshimim on 27/12/17.
//

#ifndef SERVER_GAMEROOM_H
#define SERVER_GAMEROOM_H

using namespace std;

class GameRoom {
public:
    GameRoom(int firstPlayer);
    void setSecondPlayer(int secondPlayer);
    void handleTowClients();
    bool fullGame();
    bool gameOver();
private:
    int firstPlayer ;
    int secondPlayer;
    int gameStatus;
};


#endif //SERVER_GAMEROOM_H
