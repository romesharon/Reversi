
/*aviv shisman 206558157*/
#include "Board.h"
#include "CellManger.h"
#include "ReverseRule.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "GameFlow.h"

/*the main function.
creating the board and setting pieces.*/

int main()
{
    CellManger* c=new CellManger(8);
    c->setWhite(4,4);
    c->setWhite(5,5);
    c->setBlack(4,5);
    c->setBlack(5,4);
    Board* b=new Board(8,c->getArr());
    Rule* r=new ReverseRule();
    Player* p1=new HumanPlayer('x');
    Player* p2=new HumanPlayer('o');
    Player** players=new Player*[2];
    players[0]=p1;
    players[1]=p2;
    GameFlow* g=new GameFlow(b,c,r,players);
    g->play();
    b->show();

    delete c;
    delete b;
    delete r;
    delete p1;
    delete p2;
    delete[] players;
    delete g;


    return 0;
}