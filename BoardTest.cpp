//aviv shisman 206558157
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Board.h"
#include "../CellManger.h"

TEST(BoardTest,checkSize){
    CellManger manger(8);
    Board b(8,manger.getArr());
    ASSERT_EQ(8,b.getSize());
}


