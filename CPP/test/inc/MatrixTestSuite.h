#ifndef MATRIXTESTSUITE_H
#define MATRIXTESTSUITE_H

#include <iostream>
#include <sstream>
#include <cmath>

#include "../../lib/inc/cpptest.h"
#include "../../inc/Matrix.h"

class MatrixTestSuite : public Test::Suite {
public:
    MatrixTestSuite() {
        TEST_ADD(MatrixTestSuite::constructors)
        TEST_ADD(MatrixTestSuite::copyConstructors)
        TEST_ADD(MatrixTestSuite::copyConstructorsIdentiation)
        TEST_ADD(MatrixTestSuite::parenthesisOperator)
        TEST_ADD(MatrixTestSuite::atOperator)
        TEST_ADD(MatrixTestSuite::atOperatorThrowsRowException)
        TEST_ADD(MatrixTestSuite::atOperatorThrowsColException)
        TEST_ADD(MatrixTestSuite::plusEqualOperator)
        TEST_ADD(MatrixTestSuite::plusEqualOperatorThrowsError)
    }

private:
    void constructors() {
        Matrix<int> m1(0, 0);
        Matrix<int> m2(2, 4);

        TEST_ASSERT(m1.rows() == 0 && m1.cols() == 0);
        TEST_ASSERT(m2.rows() == 2 && m2.cols() == 4);
    }

    void copyConstructors() {
        Matrix<int> m1(5, 3);
        Matrix<int> m2(m1);
        Matrix<int> m3(1, 1);
        m3 = m2;

        TEST_ASSERT(m1.rows() == 5 && m1.cols() == 3);
        TEST_ASSERT(m2.rows() == 5 && m2.cols() == 3);
        TEST_ASSERT(m3.rows() == 5 && m3.cols() == 3);
    }

    void copyConstructorsIdentiation() {
        Matrix<int> m1(5, 3);
        m1 = m1;

        TEST_ASSERT(m1.rows() == 5 && m1.cols() == 3);
    }

    void parenthesisOperator() {
        Matrix<int> m1(2, 2);
        m1(0, 0) = 0;
        m1(0, 1) = 1;
        m1(1, 0) = 2;
        m1(1, 1) = 3;

        TEST_ASSERT(m1.print() == "[0, 1, 2, 3]");
    }

    void atOperator() {
        Matrix<int> m1(2, 2);
        m1(0, 0) = 0;
        m1(0, 1) = 1;
        m1(1, 0) = 2;
        m1(1, 1) = 3;

        TEST_ASSERT(m1.at(0, 0) == 0);
        TEST_ASSERT(m1.at(0, 1) == 1);
        TEST_ASSERT(m1.at(1, 0) == 2);
        TEST_ASSERT(m1.at(1, 1) == 3);
    }

    void atOperatorThrowsRowException() {
        Matrix<int> m1(2, 2);

        TEST_THROWS(m1.at(2, 2), RowIndexError);
        TEST_THROWS(m1.at(2, 1), RowIndexError);
    }

    void atOperatorThrowsColException() {
        Matrix<int> m1(2, 2);

        TEST_THROWS(m1.at(1, 2), ColIndexError);
    }

    void plusEqualOperator() {
        Matrix<int> m1(2, 2);
        m1(0, 0) = 0;
        m1(0, 1) = 0;
        m1(1, 0) = 0;
        m1(1, 1) = 0;

        Matrix<int> m2(2, 2);
        m2(0, 0) = 0;
        m2(0, 1) = 1;
        m2(1, 0) = 2;
        m2(1, 1) = 3;

        m1 += m2;

        TEST_ASSERT(m1.print() == "[0, 1, 2, 3]");
    }

    void plusEqualOperatorThrowsError() {
        Matrix<int> m1(2, 2);
        Matrix<int> m2(3, 4);

        TEST_THROWS(m1 += m2, DimensionError);
    }
};

#endif /* MATRIXTESTSUITE_H */