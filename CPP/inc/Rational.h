#ifndef RATIONAL_H
#define RATIONAL_H

#include <stdexcept>
#include <iostream>
#include <string>

/*
 * Represent positive and negative rational numbers as two whole numbers, numerator and denominator. 
 * The denominator should never be negative or zero; the numerator may be any whole number.
 */
class Rational {
public:
    Rational();
    Rational(int n);
    Rational(int n, int d) throw (std::invalid_argument);
    explicit Rational(std::string s) throw (std::invalid_argument);

    int num();
    int denom();
    Rational reciprocal() const throw (std::invalid_argument);

    Rational &operator+=(const Rational &other);
    Rational &operator-=(const Rational &other);
    Rational &operator*=(const Rational &other);
    Rational &operator/=(const Rational &other);
    const Rational operator++(int);
    Rational &operator++();
    const Rational operator--(int);
    Rational &operator--();
    Rational operator-() const;
    bool operator==(const Rational& other);
    bool operator!=(const Rational& other);
    bool operator<(const Rational& other);
    bool operator<=(const Rational& other);
    bool operator>(const Rational& other);
    bool operator>=(const Rational& other);

    friend Rational operator+(const Rational &left, const Rational &right);
    friend Rational operator-(const Rational &left, const Rational &right);
    friend Rational operator*(const Rational &left, const Rational &right);
    friend Rational operator/(const Rational &left, const Rational &right);

    operator double();
    operator float();

    friend std::ostream &operator<<(std::ostream &stream, const Rational &r);

private:
    static const std::string invalidArgumentMsg;
    static const std::string invalidStringMsg;
    int numerator;
    int denominator;

    template<typename T>
    static void reduceFraction(T &n, T &d) {
        for (int i = 2; i <= d;) {
            if (n % i == 0 && d % i == 0) {
                n = n / i;
                d = d / i;
            } else {
                i++;
            }
        }
    }

    void validate();
};

#endif /* RATIONAL_H */