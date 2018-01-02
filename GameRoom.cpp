//
// Created by magshimim on 27/12/17.
//

#include <unistd.h>
#include <iostream>
#include "GameRoom.h"

GameRoom::GameRoom(int firstPlayer) : firstPlayer(firstPlayer){
    int x=0;
    int n = write(firstPlayer, &x, sizeof(x));
    if (n == -1) {
        cout << "Error writing to player2" << endl;
        return;
    }
    secondPlayer=0;
    gameStatus=0;
}

void GameRoom::setSecondPlayer(int secondPlayer) {
    this->secondPlayer = secondPlayer;
}

bool GameRoom::fullGame() {
    return secondPlayer && firstPlayer;
}

bool GameRoom::gameOver() {
    return gameStatus;
}
void GameRoom::handleTowClients(){
    int o=1;
    int start=2;

    int n = write(secondPlayer, &o, sizeof(o));
    if (n == -1) {
        cout << "Error writing to player2" << endl;
        return;
    }
    n = write(firstPlayer, &start, sizeof(start));
    if (n == -1) {
        cout << "Error writing to player1" << endl;
        return;
    }
    while (true) {
        int x;
        int y;
        // Read new move from 1 problem!!11111
        int byte = read(firstPlayer, &x, sizeof(x));
        if (byte == -1) {
            cout << "Error reading player move" << endl;
            return;
        }
        if (byte == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        byte = read(firstPlayer, &y, sizeof(y));
        if (byte == -1) {
            cout << "Error reading player move" << endl;
            return;
        }
        if (byte == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        // Send move to player 2
        byte = write(secondPlayer, &x, sizeof(x));
        if (byte == -1) {
            cout << "Error writing to player2" << endl;
            return;
        }
        byte = write(secondPlayer, &y, sizeof(y));
        if (byte == -1) {
            cout << "Error writing to player2" << endl;
            return;
        }
        //means game over
        if(x == -1 && y == -1) {
            gameStatus=1;
            return;
        }
        // Read new move from 2
        byte = read(secondPlayer, &x, sizeof(x));
        if (byte == -1) {
            cout << "Error reading player move" << endl;
            return;
        }
        if (byte == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        byte = read(secondPlayer, &y, sizeof(y));
        if (byte == -1) {
            cout << "Error reading player move" << endl;
            return;
        }
        if (byte == 0) {
            cout << "Client disconnected" << endl;
            return;
        }

        //writing the move to player 2
        byte = write(firstPlayer, &x, sizeof(x));
        if (byte == -1) {
            cout << "Error writing to player2" << endl;
            return;
        }
        byte = write(firstPlayer, &y, sizeof(y));
        if (byte == -1) {
            cout << "Error writing to player2" << endl;
            return;
        }
        //game over
        if(x == -1 && y == -1) {
            gameStatus=1;
            return;
        }
    }
}