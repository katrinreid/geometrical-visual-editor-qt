#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "matrixs/matrixs.hpp"
#include "doctest/doctest.h"

TEST(MatrixSTest, DefaultConstructor
) {
MatrixS m1;
ASSERT_EQ(m1
.

ssize(), std::make_tuple(0, 0)

);
}

TEST(MatrixSTest, ConstructorWithSizeParameter
) {
MatrixS m2(3, 2);
ASSERT_EQ(m2
.

ssize(), std::make_tuple(3, 2)

);
}

TEST(MatrixSTest, CopyConstructor
) {
MatrixS m2(3, 2);
m2.at(1, 1) = 5;
MatrixS m3(m2);
ASSERT_EQ(m3
.at(1, 1), 5);
}

TEST(MatrixSTest, AssignmentOperator
) {
MatrixS m2(3, 2);
m2.at(1, 1) = 5;
MatrixS m4;
m4 = m2;
ASSERT_EQ(m4
.at(1, 1), 5);
}

TEST(MatrixSTest, ResizeMatrix
) {
MatrixS m2(3, 2);
m2.resize(2, 4);
ASSERT_EQ(m2
.

ssize(), std::make_tuple(2, 4)

);
}

TEST(MatrixSTest, AccessElementsWithAtFunction
) {
MatrixS m2(2, 2);
m2.at(0, 0) = 1;
m2.at(0, 1) = 2;
m2.at(1, 0) = 3;
m2.at(1, 1) = 4;
ASSERT_EQ(m2
.at(0, 0), 1);
ASSERT_EQ(m2
.at(0, 1), 2);
ASSERT_EQ(m2
.at(1, 0), 3);
ASSERT_EQ(m2
.at(1, 1), 4);
}

TEST(MatrixSTest, AccessElementsWithInvalidIndices
) {
MatrixS m2(2, 2);
bool exception_caught = false;
try {
m2.at(2, 0);
}
catch (
const std::out_of_range& e
) {
exception_caught = true;
}
ASSERT_TRUE(exception_caught);
}

TEST(MatrixSTest, AccessElementsWithConstObject
) {
const MatrixS m5(2, 2);
ASSERT_EQ(m5
.at(1, 1), 0);
}

TEST(MatrixSTest, ResizeMatrixWithNegativeSize
) {
MatrixS m2(2, 2);
bool exception_caught = false;
try {
m2.resize(-1, 2);
}
catch (
const std::invalid_argument& e
) {
exception_caught = true;
}
ASSERT_TRUE(exception_caught);
}

TEST(MatrixSTest, AccessElementsWithInvalidIndicesAfterResizing
) {
MatrixS m2(2, 2);
m2.resize(2, 4);
bool exception_caught = false;
try {
m2.at(2, 0);
}
catch (
const std::out_of_range& e
) {
exception_caught = true;
}
ASSERT_TRUE(exception_caught);
}
