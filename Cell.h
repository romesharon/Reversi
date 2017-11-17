/* aviv shisman 206558157
 * class represent a cell in the board
 */

#ifndef ASS1_CELL_H
#define ASS1_CELL_H


class Cell {
public:
    Cell();

    Cell(char);
    char symbol;
    char opposite();
    int isEmpty();
};


#endif //ASS1_CELL_H
