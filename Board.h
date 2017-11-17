    //

/*aviv shisman 206558157
the Board class.*/
#pragma once
    #ifndef BOARD_H_
#define BOARD_H_
#include <string>
#include "GameShower.h"
#include "Cell.h"

    using namespace std;

    class Board:public GameShower {
    public:
        Board(int,Cell**);
        int getSize() const;
        void show() const;


    private:
        int size;
        Cell** arr;
    };
#endif//Board_h
