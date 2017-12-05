/*aviv shisman 206558157 01
rome sharon 209296235 01*/
#include "Board.h"
#include "CellManger.h"
#include "ReverseRule.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "GameFlow.h"
#include "AIPlayer.h"
#include "Client.h"
#include "ClientPlayer.h"
#include <iostream>
/*the main function.
creating the board and setting pieces.*/

using namespace std;

int main(){
    int choice;
    GameFlow *g;
    Player *p1 = NULL;
    Player **players =new Player *[2];
    CellManger *c = new CellManger(8);
    c->setWhite(4, 4);
    c->setWhite(5, 5);
    c->setBlack(4, 5);
    c->setBlack(5, 4);
    Board *b = new Board(8, c->getArr());
    Rule *r = new ReverseRule();
    cout << "Welcome to Reversi!!!!" << endl << "1. 1 vs 1" << endl << "2. 1 vs Computer" << endl
         << "3. play Online" << endl;
    do {
        cout << "Enter your choice here" << endl;
        cin >> choice;
    } while (choice != 1 && choice != 2 && choice != 3);
    Player *p2;
    if (choice == 1) {
        p2 = new HumanPlayer('o');
    } else if (choice == 2) {
        p2 = new AIPlayer('o', c);

    } else if (choice == 3) {
        char symbol;
        Client *client = new Client("127.0.0.1", 8000);
        try {
            client->connectToServer();
            if (client->recvKey() == 0) {
                symbol = 'x';
            } else {
                symbol = 'o';
            }
        } catch (const char *msg) {
            cout << "Faild:" << msg << endl;
        }

        ClientPlayer *cp = new ClientPlayer(client, symbol);
        players[0] = cp;
        players[1] = NULL;
        g = new GameFlow(b, c, r, players, client);
        if(symbol == 'x') {
            cout << "Waiting for the other player to connect..." << endl;
            client->recvKey();
        }
    }

    if (choice != 3) {
        p1 = new HumanPlayer('x');
        players[0] = p1;
        players[1] = p2;
        g = new GameFlow(b, c, r, players);
    }

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

