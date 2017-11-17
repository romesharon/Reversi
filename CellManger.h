/* aviv shisman 206558157
 * class we use to represent the board different cells and manage them
 * explanation on the methods in the cpp file
 */

#ifndef ASS1_CELLMANGER_H
#define ASS1_CELLMANGER_H


#include "Cell.h"

class CellManger {
public:
    CellManger(int);
    ~CellManger();
    int getSize() const;
    Cell **getArr() const;
    void setBlack(int,int);
    void setWhite(int,int);
private:
    int size;
    Cell** arr;

};


#endif //ASS1_CELLMANGER_H
