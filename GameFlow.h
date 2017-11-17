/* aviv shisman 206558157
 * this class defines the flow of the game
 * the play method uses all the classes to create a full functioning game.
 * explanation on the methods in the cpp file
 */

#ifndef ASS1_GAMEFLOW_H
#define ASS1_GAMEFLOW_H


#include "GameShower.h"
#include "CellManger.h"
#include "Rule.h"
#include "Board.h"
#include "Player.h"

class GameFlow {
public:
    void play();
    GameFlow(GameShower*,CellManger*,Rule*,Player**);
private:
    GameShower* screen;
    CellManger* manger;
    Rule* rule;
    Player** players;
    int current;
    int numOfPieces;
};


#endif //ASS1_GAMEFLOW_H
