/*aviv shisman and rom sharon
 * Player of online play
 */

#include "ClientPlayer.h"
#include "HumanPlayer.h"
#include <iostream>
using namespace std;
/*
 * constructor
 */
ClientPlayer::ClientPlayer(Client *c, char s){
    symbol = s;
    client = c;
}
/*the one move function the same as human player
 * with the exception of sending the move to the client
 */
Point* ClientPlayer::oneMove(Point** pointsArr,int a) const  {
    cout<<symbol<<":"<<"its your Move!\n";
    cout<<"your possible moves are: ";
    for(int i=0;i<a;i++){
        cout<<"("<<pointsArr[i]->getX()<<","<<pointsArr[i]->getY()<<")"<<" ";
    }

    cout<<endl;
    cout<<"choose a move by pressing a number a space and than the other number"<<endl;

    cout<<endl;
    cout<<endl;
    int flag=1;
    int x, y;
    //loops until the user chooses valid option
    do {
        cin >> x >> y;
        for(int i=0;i<a;i++){
            if(x==pointsArr[i]->getX() && y==pointsArr[i]->getY())
                flag=0;
        }
        if(flag==1){
            cout<<"not an option try again"<<endl;
        }
    }while(flag);
    cout<<"you chose "<<x<<","<<y<<endl;

    Point* p=new Point(x,y);
    client->sendMove(x, y);
    return p;
}
/*
 * return symbol of player
 */
char ClientPlayer::getSymbol() const {
    return symbol;
};