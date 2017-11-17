/*aviv shisman 206558157*/
#include "CellManger.h"
/*
 * the constructor using the size to create the cell array
 */
CellManger::CellManger(int s) {
    size=s;
    arr=new Cell*[size+3];
    for(int i = 0; i < size+3; i++) {
        arr[i] = new Cell[size +3]();
        for(int j=0;j<size+3;j++){
            arr[i][j].symbol='a';
        }
    }
}
/*
 * return the size
 */
int CellManger::getSize() const {
    return size;
}
/*
 * setting black piece
 */
void CellManger::setBlack(int x, int y) {
    arr[x][y].symbol='x';
}
/*
 * setting white piece
 */
void CellManger::setWhite(int x, int y) {
    arr[x][y].symbol='o';
}
/*
 * return the array
 */
Cell **CellManger::getArr() const {
    return arr;
}

/*
 * destructor
 */
CellManger::~CellManger() {

    for(int i = 0; i < size+3; i++) {
        delete[]( arr[i]);

    }
    delete [] arr;

}
