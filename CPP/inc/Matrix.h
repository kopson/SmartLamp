#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <sstream>
#include <stdexcept>

template <class T> class Matrix;

/**
 * Base matrix operations
 */

class DimensionError : public std::logic_error {
public:
    DimensionError(int x, int y, int ox, int oy, const std::string &reason = invalidDimension);
    virtual const char *what() const throw();
    virtual ~DimensionError() throw ();

protected:
    static const std::string invalidDimension;

private:
    int x, y, otherX, otherY;
};

class IndexError : public std::out_of_range {
public:
    IndexError(int idx, const std::string &reason = invalidIndex);
    virtual const char *what() const throw();
    virtual ~IndexError() throw ();

protected:
    static const std::string invalidIndex;

private:
    int index;
};

class RowIndexError : public IndexError {
public:
    RowIndexError(int i);
};

class ColIndexError : public IndexError {
public:
    ColIndexError(int i);
};

template <class T>
class Matrix {
public:
    Matrix(int i, int j);
    Matrix(const Matrix &other);
    ~Matrix();

    Matrix operator=(const Matrix &other);

    int rows() const { return x; }
    int cols() const { return y; }

    T& at(int i, int j) throw (IndexError);
    T  at(int i, int j) const throw (IndexError);
    T& operator()(int i, int j);
    T  operator()(int i, int j) const;

    Matrix operator+=(const Matrix &other) const throw (DimensionError);
    std::string print() const;

private:
    int  x;
    int  y;
    T   *v;

    void copy(const Matrix &other);
    void check(int i, int j) const throw (IndexError);
};
       
template <class T>
Matrix<T> operator+(const Matrix<T> &x, const Matrix<T> &y);
template <class T>
const Matrix<T> operator*(const Matrix<T> &v, float s);
template <class T>
const Matrix<T> operator*(float s, const Matrix<T> &v);

#endif /* MATRIX_H */