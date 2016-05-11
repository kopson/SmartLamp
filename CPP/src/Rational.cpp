#include <vector>

#include "Rational.h"
#include "StringsUtil.h"

const std::string Rational::invalidArgumentMsg = "Invalid denominator value: 0";
const std::string Rational::invalidStringMsg = "Invalid string value";

Rational::Rational() : numerator(0), denominator(1) {

}

Rational::Rational(int n) : numerator(n), denominator(1) {

}

Rational::Rational(int n, int d) throw (std::invalid_argument) : numerator(n), denominator(d) {
    validate();
}

Rational::Rational(std::string s) throw (std::invalid_argument) {
    if (s.size() == 0 || s[s.size() - 1] == '/') {
        throw std::invalid_argument(invalidStringMsg);
    }

    std::vector<std::string> tokens = split(s, '/');
    if (tokens.size() == 0 || tokens.size() > 2) {
        throw std::invalid_argument(invalidStringMsg);
    }

    if (!isNumber(tokens[0])) {
        throw std::invalid_argument(invalidStringMsg);
    }
    numerator = std::stoi(tokens[0]);
    
    if (tokens.size() == 2) {
        if (!isNumber(tokens[1])) {
            throw std::invalid_argument(invalidStringMsg);
        }
        denominator = std::stoi(tokens[1]);
    } else {
        denominator = 1;
    }

    validate();
}

void Rational::validate() {
    if (denominator == 0) {
        throw std::invalid_argument(invalidArgumentMsg);
    }

    reduceFraction<int>(numerator, denominator);

    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

int Rational::num() {
    return numerator;
}

int Rational::denom() {
    return denominator;
}

Rational Rational::reciprocal() const throw (std::invalid_argument) {
    return Rational(denominator, numerator);
}

Rational &Rational::operator+=(const Rational &other) {
    long long tmpNum = numerator * other.denominator + other.numerator * denominator;
    long long tmpDen = denominator * other.denominator;
    reduceFraction<long long>(tmpNum, tmpDen);
    
    numerator = tmpNum;
    denominator = tmpDen;

    return *this;
}

Rational operator+(const Rational &left, const Rational &right) {
    Rational temp(left);
    temp += right;
    return temp;
}

Rational &Rational::operator-=(const Rational &other) {
    *this += -other;
    return *this;
}

Rational operator-(const Rational &left, const Rational &right) {
    Rational temp(left);
    temp -= right;
    return temp;
}

Rational &Rational::operator*=(const Rational &other) {
    long long tmpNum = numerator * other.numerator;
    long long tmpDen = denominator * other.denominator;
    reduceFraction<long long>(tmpNum, tmpDen);
    
    numerator = tmpNum;
    denominator = tmpDen;

    return *this;
}

Rational &Rational::operator/=(const Rational &other) {
    *this *= other.reciprocal();
    return *this;
}

Rational operator*(const Rational &left, const Rational &right) {
    auto temp(left);
    temp *= right;
    return temp;
}

Rational operator/(const Rational &left, const Rational &right) {
    auto temp(left);
    temp /= right;
    return temp;
}

const Rational Rational::operator++(int) {
    auto tmp(*this);
    operator++();
    return tmp;
}

Rational &Rational::operator++() {
    numerator += denominator;
    return *this;
}

const Rational Rational::operator--(int) {
    auto tmp(*this);
    operator--();
    return tmp;
}

Rational &Rational::operator--() {
    numerator -= denominator;
    return *this;
}

Rational Rational::operator-() const {
    return Rational(-numerator, denominator);
}

bool Rational::operator==(const Rational& other) {
    if (denominator == other.denominator) {
        return numerator == other.numerator;
    }

    long long tmpNum = numerator * other.denominator;
    long long tmpOtherNum = denominator * other.numerator;

    return tmpNum == tmpOtherNum;
}

bool Rational::operator!=(const Rational& other) {
    return !(*this == other);
}

bool Rational::operator<(const Rational& other) {
    if (denominator == other.denominator) {
        return numerator < other.numerator;
    }

    long long tmpNum = numerator * other.denominator;
    long long tmpOtherNum = denominator * other.numerator;

    return tmpNum < tmpOtherNum;
}

bool Rational::operator<=(const Rational& other) {
    return *this == other || *this < other;
}

bool Rational::operator>(const Rational& other) {
    return *this == other || !(*this < other);
}

bool Rational::operator>=(const Rational& other) {
    return !(*this < other);
}

Rational::operator double() {
    return static_cast<double>(numerator) / denominator;
}
    
Rational::operator float() {
    return static_cast<float>(numerator) / denominator;
}

std::ostream &operator<<(std::ostream &os, const Rational &r) {
    os << r.numerator;
    if (r.denominator != 1) {
        os << '/' << r.denominator;
    }
    return os;
}