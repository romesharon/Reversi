/*aviv shisman 206558157 01
rome sharon 209296235 01*/

#include <iostream>
#include "GameFlow.h"
/*
 * the constructor
 * screen - we will use the methods show and size
 * manger- will be used to get the arr of cells and set new value for cells
 * players - a pointer arr to the players
 * current signifies who is the current player
 * numOf pieces looks for the ending of the game
 */
GameFlow::GameFlow(GameShower* s, CellManger* c, Rule *r, Player**p) {
    screen=s;
    manger=c;
    rule=r;
    players=p;
    current=0;
    numOfPieces=4;
}

GameFlow::GameFlow(GameShower *s, CellManger *c, Rule *r, Player** p, Client* cl){
    screen=s;
    manger=c;
    rule=r;
    players = p;
    current=0;
    numOfPieces=4;
    client = cl;
}

/*
 * play method uses to start the game
 */
void GameFlow::play() {
    bool isOnline = false;
    bool myTurn=false;
    if(players[1] == NULL) {
        isOnline = true;
        if(players[0]->getSymbol()=='x'){
            myTurn=true;
        }
    }
    do {
        if (isOnline) {
            current = 0;
        }
        screen->show();
        if (isOnline && !myTurn) {
            char symbol;
            Point* p = client->readMove();
            cout << "The other player move: " << p->getX() << ","<< p->getY() << endl;
            if (players[0]->getSymbol() == 'x') {
                manger->setWhite(p->getX(), p->getY());
                symbol = 'o';
            } else {
                manger->setBlack(p->getX(), p->getY());
                symbol = 'x';
            }
            rule->apply(manger->getArr(), p->getX(), p->getY(), symbol);
            numOfPieces++;
            myTurn = !myTurn;
            //delete p
            delete p;
            continue;
        }
        Point **points = new Point *[screen->getSize() * screen->getSize()];

        //going trough all the cells in the array and checking who is valid place to set piece
        int i = 0, j = 0, k = 0;
        for (i = 1; i <= screen->getSize(); i++) {
            for (j = 1; j <= screen->getSize(); j++) {
                if (rule->check(manger->getArr(), i, j, players[current]->getSymbol())) {
                    points[k] = new Point(i, j);
                    k++;
                }
            }
        }
        if (k == 0) {
            cout << "No possible move for:" << players[current]->getSymbol() << endl;
            current++;
            if (current == 2) { current = 0; }
            for (int i = 0; i < k; i++) {
                delete (points[i]);
            }
            delete (points);
            continue;
        }
        Point *a = players[current]->oneMove(points, k);
        if (players[current]->getSymbol() == 'x') {
            manger->setBlack(a->getX(), a->getY());
        } else {
            manger->setWhite(a->getX(), a->getY());
        }
        numOfPieces++;
        if (isOnline) {
            current = 0;
        }
        //applying the rule: flipping the appropriate pieces
        rule->apply(manger->getArr(), a->getX(), a->getY(), players[current]->getSymbol());
        current++;

        if (current == 2) {
            current = 0;
        }

        myTurn = !myTurn;

        delete (a);
        for (int i = 0; i < k; i++) {
            delete (points[i]);
        }
        delete (points);
    //}while(numOfPieces<8); //for debug we will use this somethimes...
    }while(numOfPieces<screen->getSize()*screen->getSize());
    cout<<"game over"<<endl;

    if(this->manger->getCount('x')>this->manger->getCount('o')){
        cout<<"player black-x has won"<<endl;
    }
    else{
        cout<<"player white-o has won"<<endl;
    }

    //end message to the server.
    if (myTurn) {
        this->client->sendMove(-1,-1);
    }
}
