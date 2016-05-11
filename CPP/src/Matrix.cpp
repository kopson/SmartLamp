#include <iostream>
#include <functional>
#include <numeric>

#include "Matrix.h"

const std::string DimensionError::invalidDimension = "Bad matrix dimension";

DimensionError::DimensionError(int x, int y, int ox, int oy, const std::string &reason) : 
    logic_error(reason), x(x), y(y), otherX(ox), otherY(oy) { 
}

const char *DimensionError::what() const throw() {
    std::ostringstream os;
    os << std::logic_error::what();
    os << ": src=" << x << "x" << y << " dest=" << otherX << otherY;
    return os.str().c_str();
}

DimensionError::~DimensionError() throw () {

}

const std::string IndexError::invalidIndex = "Bad index value";

IndexError::IndexError(int idx, const std::string &reason) : 
    out_of_range(reason), index(idx) { 
}

const char *IndexError::what() const throw() {
    std::ostringstream os;
    os << std::out_of_range::what();
    os << ": " << index;
    return os.str().c_str();
}

IndexError::~IndexError() throw () {

}

RowIndexError::RowIndexError(int i) : IndexError(i, invalidIndex + " for row") {

}

ColIndexError::ColIndexError(int i) : IndexError(i, invalidIndex + " for column") {

}

template <class T>
Matrix<T>::Matrix(int i, int j) : x(i), y(j) {
    v = new T[x * y];
}

template <class T>
Matrix<T>::~Matrix() {
    delete [] v;
}

template <class T>
Matrix<T>::Matrix(const Matrix &other) {
    copy(other);
}

template <class T>
Matrix<T> Matrix<T>::operator=(const Matrix &other) {
    if (this != &other) {
        delete [] v;
        copy(other);
    }
    return *this;
}

template <class T>
void Matrix<T>::copy(const Matrix &other) {
    x = other.x;
    y = other.y;
    v = new T[x * y];
    std::copy(other.v, other.v + x * y, v);
}

template <class T>
void Matrix<T>::check(int i, int j) const throw (IndexError) {
    if (i < 0 || i >= x) {
        throw RowIndexError(i);
    }
    if (j < 0 || j >= y) {
        throw ColIndexError(j);
    }
}

template <class T>
T& Matrix<T>::at(int i, int j) throw(IndexError) {
    check(i, j);
    return operator()(i, j);
}

template <class T>
T Matrix<T>::at(int i, int j) const throw (IndexError) {
    check(i, j);
    return operator()(i, j);
}

template <class T>
T& Matrix<T>::operator()(int i, int j) {
    return v[i * y + j];
}

template <class T>
T Matrix<T>::operator() (int i, int j) const {
    return v[i * y + j];
}

template <class T>
Matrix<T> Matrix<T>::operator+=(const Matrix &other) const throw (DimensionError) {
    if (other.x != x || other.y != y) {
        throw DimensionError(x, y, other.x, other.y);
    }

    for (int i = 0; i < x * y; ++i) {
        v[i] += other.v[i];
    }
    return *this;
}

template <class T>
Matrix<T> operator+(const Matrix<T> &left, const Matrix<T> &right) {
    Matrix<T> temp(left);
    temp += right;
    return temp;
}

template <class T>
const Matrix<T> operator*(const Matrix<T> &v, float s) {
    return Matrix<T>(v) *= s;
}

template <class T>
const Matrix<T> operator*(float s, const Matrix<T> &v) {
    return Matrix<T>(v) *= s;
}

template <class T>
std::string Matrix<T>::print() const {
    std::string matrix;

    matrix = std::accumulate(v, v + x * y, std::string{},
        [](const std::string& s, T i) {
            return s.empty() ? std::to_string(i)
                   : s + ", " + std::to_string(i);
        });
    return std::string("[").append(matrix).append("]");
}

// Explicit template instantiation
template class Matrix<int>;