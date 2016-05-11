#ifndef RATIONALTESTSUITE_H
#define RATIONALTESTSUITE_H

#include <iostream>
#include <sstream>
#include <cmath>

#include "../../lib/inc/cpptest.h"
#include "../../inc/Rational.h"

class RationalTestSuite : public Test::Suite {
public:
    RationalTestSuite() {
        TEST_ADD(RationalTestSuite::constructors)
        TEST_ADD(RationalTestSuite::copyConstructors)
        TEST_ADD(RationalTestSuite::constructorReducesFractions)
        TEST_ADD(RationalTestSuite::constructorHandlesNegativeDenominator)
        TEST_ADD(RationalTestSuite::constructorThrowsOn0Denominator)
        TEST_ADD(RationalTestSuite::stringConstructor)
        TEST_ADD(RationalTestSuite::invalidStringConstructor)
        TEST_ADD(RationalTestSuite::operatorPlusEqual)
        TEST_ADD(RationalTestSuite::operatorPlusEqualSelfAssigment)
        TEST_ADD(RationalTestSuite::operatorMinusEqual)
        TEST_ADD(RationalTestSuite::operatorMinusEqualSelfAssigment)
        TEST_ADD(RationalTestSuite::operatorMultiplyEqual)
        TEST_ADD(RationalTestSuite::operatorMultiplyEqualSelfAssigment)
        TEST_ADD(RationalTestSuite::operatorDivideEqual)
        TEST_ADD(RationalTestSuite::operatorDivideEqualSelfAssigment)
        TEST_ADD(RationalTestSuite::operatorDivideEqualReducesFraction)
        TEST_ADD(RationalTestSuite::operatorDivideEqualThrowsInvalidArgument)
        TEST_ADD(RationalTestSuite::operatorPlus)
        TEST_ADD(RationalTestSuite::operatorMinus)
        TEST_ADD(RationalTestSuite::operatorMultiply)
        TEST_ADD(RationalTestSuite::operatorDivide)
        TEST_ADD(RationalTestSuite::operatorDivideReducesFraction)
        TEST_ADD(RationalTestSuite::operatorDivideThrowsInvalidArgument)
        TEST_ADD(RationalTestSuite::reciprocal)
        TEST_ADD(RationalTestSuite::reciprocalThrowsInvalidArgument)
        TEST_ADD(RationalTestSuite::preIncrement)
        TEST_ADD(RationalTestSuite::postIncrement)
        TEST_ADD(RationalTestSuite::preDecrement)
        TEST_ADD(RationalTestSuite::postDecrement)
        TEST_ADD(RationalTestSuite::castRational)
        TEST_ADD(RationalTestSuite::streamOutput)
        TEST_ADD(RationalTestSuite::operatorUnaryMinus)
        TEST_ADD(RationalTestSuite::relationalOperators)
    }

private:
    void constructors()  {
        Rational r1;
        Rational r2(5);
        Rational r3(5, 3);

        TEST_ASSERT(r1.num() == 0 && r1.denom() == 1);
        TEST_ASSERT(r2.num() == 5 && r2.denom() == 1);
        TEST_ASSERT(r3.num() == 5 && r3.denom() == 3);
    }

    void copyConstructors()  {
        Rational r1(5, 3);
        Rational r2(r1);
        Rational r3;
        r3 = r2;

        TEST_ASSERT(r1.num() == 5 && r1.denom() == 3);
        TEST_ASSERT(r2.num() == 5 && r2.denom() == 3);
        TEST_ASSERT(r3.num() == 5 && r3.denom() == 3);
    }

    void constructorReducesFractions() {
        Rational r4(15, 5);
        Rational r5(3, 15);
        Rational r6(48, 60);

        TEST_ASSERT(r4.num() == 3 && r4.denom() == 1);
        TEST_ASSERT(r5.num() == 1 && r5.denom() == 5);
        TEST_ASSERT(r6.num() == 4 && r6.denom() == 5);
    }

    void constructorHandlesNegativeDenominator() {
        Rational r7(5, -3);
        Rational r8(-5, -3);
        Rational r9(-5, 3);

        TEST_ASSERT(r7.num() == -5 && r7.denom() == 3);
        TEST_ASSERT(r8.num() == 5 && r8.denom() == 3);
        TEST_ASSERT(r9.num() == -5 && r9.denom() == 3);
    }

    void constructorThrowsOn0Denominator() {
        TEST_THROWS(Rational(5, 0), std::invalid_argument);
    }

    void stringConstructor() {
        Rational r1("1");
        Rational r2("1/4");
        Rational r3("-1/4");
        Rational r4("-1/-4");
        Rational r5("1/-4");

        TEST_THROWS(Rational(""), std::invalid_argument);
        TEST_ASSERT(r1.num() == 1 && r1.denom() == 1);
        TEST_ASSERT(r2.num() == 1 && r2.denom() == 4);
        TEST_ASSERT(r3.num() == -1 && r3.denom() == 4);
        TEST_ASSERT(r4.num() == 1 && r4.denom() == 4);
        TEST_ASSERT(r5.num() == -1 && r5.denom() == 4);
    }

    void invalidStringConstructor() {
        TEST_THROWS(Rational("  1, a"), std::invalid_argument);
        TEST_THROWS(Rational("123abc"), std::invalid_argument);
        TEST_THROWS(Rational("a"), std::invalid_argument);
        TEST_THROWS(Rational("a/b"), std::invalid_argument);
        TEST_THROWS(Rational("1/4/2"), std::invalid_argument);
        TEST_THROWS(Rational("1/"), std::invalid_argument);
        TEST_THROWS(Rational("/1"), std::invalid_argument);
        TEST_THROWS(Rational("/"), std::invalid_argument);
        TEST_THROWS(Rational("1|1"), std::invalid_argument);
        TEST_THROWS(Rational("1.2|1.4"), std::invalid_argument);
    }

    void operatorPlusEqual() {
        // 5 += (-3)
        Rational r(5);
        r += Rational(-3);
        TEST_ASSERT(r.num() == 2 && r.denom() == 1);

        // 2 += (-2)  This should set r1 = 0.
        r += Rational(-2);
        TEST_ASSERT(r.num() == 0 && r.denom() == 1);

        r = Rational(2, 3);
        r += Rational(4, 5);  // 22/15
        TEST_ASSERT(r.num() == 22 && r.denom() == 15);
    }

    void operatorPlusEqualSelfAssigment() {
        Rational r = Rational(4, 5);
        r += r;
        TEST_ASSERT(r.num() == 8 && r.denom() == 5);
    }

    void operatorMinusEqual() {
        Rational r = 5;
        r -= Rational(3);
        TEST_ASSERT(r.num() == 2 && r.denom() == 1);

        r -= Rational(2);
        TEST_ASSERT(r.num() == 0 && r.denom() == 1);

        r = Rational(2, 3);
        r -= Rational(1, 5);  // 7/15
        TEST_ASSERT(r.num() == 7 && r.denom() == 15);
     }

    void operatorMinusEqualSelfAssigment() {
        Rational r = Rational(4, 5);
        r -= r;
        TEST_ASSERT(r.num() == 0 && r.denom() == 1);
    }

    void operatorMultiplyEqual() {
        Rational r = Rational(3, 5);

        r *= Rational(2, 7);  // 6/35
        TEST_ASSERT(r.num() == 6 && r.denom() == 35);

        r = Rational(4);
        r *= Rational(5, 4);
        TEST_ASSERT(r.num() == 5 && r.denom() == 1);
    }

    void operatorMultiplyEqualSelfAssigment() {
        Rational r = Rational(4, 5);
        r *= r;
        TEST_ASSERT(r.num() == 16 && r.denom() == 25);
    }

    void operatorDivideEqual() {
        Rational r = Rational(3, 5);
        r /= Rational(2);
        TEST_ASSERT(r.num() == 3 && r.denom() == 10);
    }

    void operatorDivideEqualSelfAssigment() {
        Rational r = Rational(4, 5);
        r /= r;
        TEST_ASSERT(r.num() == 1 && r.denom() == 1);
    }
        
    void operatorDivideEqualReducesFraction() { 
        Rational r = Rational(4, 5);
        r /= Rational(2, 5);
        TEST_ASSERT(r.num() == 2 && r.denom() == 1);
    }
    
    void operatorDivideEqualThrowsInvalidArgument() { 
        Rational r = Rational(4, 5);
        TEST_THROWS(r /= Rational(), std::invalid_argument);
    }

    void operatorPlus() {
        Rational r;

        // 5 + (-3)
        r = 5;
        r = r + Rational(-3);
        TEST_ASSERT(r.num() == 2 && r.denom() == 1);

        // 2 + (-2)  This should set r1 = 0.
        r = r + Rational(-2);
        TEST_ASSERT(r.num() == 0 && r.denom() == 1);

        r = Rational(2, 3);
        r = r + Rational(4, 5);  // 22/15
        TEST_ASSERT(r.num() == 22 && r.denom() == 15);
    }

    void operatorMinus() {
        Rational r = 5;
        r = r - Rational(3);
        TEST_ASSERT(r.num() == 2 && r.denom() == 1);

        r = r - Rational(2);
        TEST_ASSERT(r.num() == 0 && r.denom() == 1);

        r = Rational(2, 3);
        r = r - Rational(1, 5);  // 7/15
        TEST_ASSERT(r.num() == 7 && r.denom() == 15);
    }

    void operatorMultiply() {
        Rational r = Rational(3, 5);

        r = r * Rational(2, 7);  // 6/35
        TEST_ASSERT(r.num() == 6 && r.denom() == 35);

        r = Rational(4);
        r = r * Rational(5, 4);
        TEST_ASSERT(r.num() == 5 && r.denom() == 1);
    }

    void operatorDivide() {
        Rational r = Rational(3, 5);
        r = r / Rational(2);
        TEST_ASSERT(r.num() == 3 && r.denom() == 10);
    }

    void operatorDivideReducesFraction() {
        Rational r = Rational(4, 5);
        r = r / Rational(2, 5);
        TEST_ASSERT(r.num() == 2 && r.denom() == 1);
    }

    void operatorDivideThrowsInvalidArgument() {
        Rational r = Rational(4, 5);
        TEST_THROWS(r = r / Rational(), std::invalid_argument);
    }

    void reciprocal() {
        Rational r = Rational(2, 5);
        TEST_ASSERT(r.num() == 2 && r.denom() == 5);

        Rational r2 = r.reciprocal();
        TEST_ASSERT(r.num() == 2 && r.denom() == 5);
        TEST_ASSERT(r2.num() == 5 && r2.denom() == 2);
        
        r = Rational(5);
        TEST_ASSERT(r.num() == 5 && r.denom() == 1);
        r = r.reciprocal();
        TEST_ASSERT(r.num() == 1 && r.denom() == 5);
    }
    
    void reciprocalThrowsInvalidArgument() {
        Rational r = Rational(0);
        TEST_THROWS(r.reciprocal(), std::invalid_argument);
    }

    void preIncrement() {
        Rational r = Rational(3);
        Rational r2 = ++r;
        TEST_ASSERT(r.num() == 4 && r.denom() == 1);
        TEST_ASSERT(r2.num() == 4 && r2.denom() == 1);
    
        r = Rational(4, 9);
        r2 = ++r;
        TEST_ASSERT(r.num() == 13 && r.denom() == 9);
        TEST_ASSERT(r2.num() == 13 && r2.denom() == 9);
    }
    
    void postIncrement() {
        Rational r = Rational(3);
        Rational r2 = r++;
        TEST_ASSERT(r.num() == 4 && r.denom() == 1);
        TEST_ASSERT(r2.num() == 3 && r2.denom() == 1);
        
        r = Rational(4, 9);
        r2 = r++;
        TEST_ASSERT(r.num() == 13 && r.denom() == 9);
        TEST_ASSERT(r2.num() == 4 && r2.denom() == 9);
    }
    
    void preDecrement() {
        Rational r = Rational(3);
        Rational r2 = --r;
        TEST_ASSERT(r.num() == 2 && r.denom() == 1);
        TEST_ASSERT(r2.num() == 2 && r2.denom() == 1);
        
        r = Rational(4, 9);
        r2 = --r;
        TEST_ASSERT(r.num() == -5 && r.denom() == 9);
        TEST_ASSERT(r2.num() == -5 && r2.denom() == 9);
    }    

    void postDecrement() {
        Rational r = Rational(3);
        Rational r2 = r--;
        TEST_ASSERT(r.num() == 2 && r.denom() == 1);
        TEST_ASSERT(r2.num() == 3 && r2.denom() == 1);
        
        r = Rational(4, 9);
        r2 = r--;
        TEST_ASSERT(r.num() == -5 && r.denom() == 9);
        TEST_ASSERT(r2.num() == 4 && r2.denom() == 9);
    }

    void castRational() {
        Rational r = 62;
        TEST_ASSERT(r.num() == 62 && r.denom() == 1);
        
        r = Rational(3);
        TEST_ASSERT((float) r == 3.0f);
        TEST_ASSERT((double) r == 3.0);

        // 2.5 can be represented precisely in floating-point, so
        // no epsilon_equals() is needed
        r = Rational(5, 2);
        TEST_ASSERT((float) r == 2.5f);
        TEST_ASSERT((double) r == 2.5);
        
        // 2/3 cannot be represented precisely in floating-point, so
        // epsilon_equals() is needed
        r = Rational(2, 3);
        TEST_ASSERT(epsilon_equals((float) r, 0.666667f));
        TEST_ASSERT(epsilon_equals((double) r, 0.666667));
    }

    void operatorUnaryMinus() {
        Rational r(-5);
        Rational r2 = -r;

        TEST_ASSERT(r.num() == -5 && r.denom() == 1);
        TEST_ASSERT(r2.num() == 5 && r2.denom() == 1);
    }

    void relationalOperators() {
        Rational r1(1, 4);
        Rational r2(3, 4);
        Rational r3(3, 4);

        TEST_ASSERT(r1 != r2);
        TEST_ASSERT(r2 == r3);
        TEST_ASSERT(r1 < r2);
        TEST_ASSERT(r1 <= r2);
        TEST_ASSERT(r2 > r1);
        TEST_ASSERT(r2 >= r1);
        TEST_ASSERT(r2 >= r3);
        TEST_ASSERT(r2 <= r3);
    }

    void streamOutput() {
        Rational r;
        std::stringstream sstream;
        
        r = Rational(31);
        sstream.str("");
        sstream << r;
        TEST_ASSERT(sstream.str() == "31");
        
        r = Rational();
        sstream.str("");
        sstream << r;
        TEST_ASSERT(sstream.str() == "0");

        r = Rational(22, 7);
        sstream.str("");
        sstream << r;
        TEST_ASSERT(sstream.str() == "22/7");

        r = Rational(-22, 7);
        sstream.str("");
        sstream << r;
        TEST_ASSERT(sstream.str() == "-22/7");
    }

    inline bool epsilon_equals(float a, float b, float epsilon = 0.00001) {
        return (fabsf(a - b) <= epsilon);
    }

    inline bool epsilon_equals(double a, double b, double epsilon = 0.00001) {
        return (fabs(a - b) <= epsilon);
    }
};

#endif /* RATIONALTESTSUITE_H */