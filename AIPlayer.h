//
// Created by magshimim on 20/11/17.
//

#ifndef ASS1_AIPLAYER_H
#define ASS1_AIPLAYER_H

#include "Player.h"
#include "CellManger.h"
#include "Rule.h"
#include "ReverseRule.h"
#include <map>

using namespace std;

class AIPlayer: public Player {
public:
    Point* oneMove(Point**,int) const;
    char getSymbol() const;
    CellManger *getC() const;
    AIPlayer(char, CellManger* c);
private:
    char symbol;
    CellManger* c;
};


#endif //ASS1_AIPLAYER_H
