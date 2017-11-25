/*aviv shisman 206558157
 *
 */

#include "AIPlayer.h"
AIPlayer::AIPlayer(char s, CellManger* cells){
    this->symbol = s;
    this->c = cells;
    //free rule
    this->rule = new ReverseRule();
}

char AIPlayer::getSymbol() const {
    return this->symbol;
}

Point* AIPlayer::oneMove(Point ** points, int a) const {
    map<Point*, int> moves;
    Point* p;
    int row, col, counter = 0, min = c->getSize() * c->getSize();
    int rowSecond, colSecond, max = -c->getSize() * c->getSize();
    char opposite;
    Point** oppositeMoves = new Point*[c->getSize() * c->getSize()];
    for(int i = 0; i < a; i++) {
        //copy the board.
        CellManger copyCell(c->getSize());
        row = points[i]->getX();
        col = points[i]->getY();
        copyCell.setArr(c->getArr());
        //applying the move
        copyCell.setCell(row, col, symbol);
        opposite = copyCell.getArr()[row][col].opposite();
        rule->apply(copyCell.getArr(), row, col, symbol);
        //get opposite player moves
        for (int k = 1; k <= copyCell.getSize(); k++) {
            for (int l = 1; l <= copyCell.getSize(); l++) {
                if (rule->check(copyCell.getArr(), k, l, opposite) ) {
                    oppositeMoves[counter] = new Point(k, l);
                    counter++;
                }
            }
        }
        //checking the "max" move for opposite player
        for(int j = 0; j < counter; j++) {
            CellManger copyCellSecond(copyCell.getSize());
            copyCellSecond.setArr(copyCell.getArr());
            rowSecond = oppositeMoves[j]->getX();
            colSecond = oppositeMoves[j]->getY();
            copyCellSecond.setCell(rowSecond, colSecond, opposite);
            rule->apply(copyCellSecond.getArr(), rowSecond, colSecond, opposite);
            int sub = copyCell.getCount(opposite) - copyCellSecond.getCount(symbol);
            if(max < sub) {
                max = sub;
            }
        }

        //adding the move we did and the max of the opposite player to map
        moves[points[i]] = max;
    }
    //iterating over the moves and chosing the move that will bring the opposite player the lowest max
    for (map<Point*, int>::iterator it=moves.begin(); it!=moves.end(); it++) {
        if(it->second < min) {
            min = it->second;
            p = new Point(*it->first);
        }
    }

    for (int k = 1; k <counter; k++) {
        delete oppositeMoves[k];
    }
    delete [] oppositeMoves;

    return p;
}