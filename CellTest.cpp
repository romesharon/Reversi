//
// Created by magshimim on 28/11/17.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Cell.h"

TEST(CellTest, emptyCell) {
        Cell cell('x');
        Cell empty;
        EXPECT_EQ(0, cell.isEmpty());
        EXPECT_EQ(1, empty.isEmpty());
}

TEST(CelTest, oppositeX) {
        Cell cell('x');
        char c = cell.opposite();
        EXPECT_EQ('o', c);
}

TEST(CelTest, oppositeO) {
        Cell cellO('o');
        char c = cellO.opposite();
        EXPECT_EQ('x', c);
}