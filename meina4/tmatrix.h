/**************************************************
 *  Name       : tvektor.h                        *
 *  Verwendung : Template Vektorklasse (Header)   *
 *  Autoren    : V. Reichelt, T. Barsch, K. Urban *
 *               IGPM RWTH Aachen                 *
 *  Datum      : Nov '96, Okt '97                 *
 *  Sprache    : C++                              *
 **************************************************/

#ifndef _TMATRIX_H  // tmatrix.h nicht doppelt benutzen
#define _TMATRIX_H

#include <iostream>

#include "tvector.h"

template <class T>
class TMatrix;

template <class T>
TMatrix<T> operator+(const TMatrix<T> &, const TMatrix<T> &);
template <class T>
TMatrix<T> operator-(const TMatrix<T> &, const TMatrix<T> &);
template <class T>
TMatrix<T> operator-(const TMatrix<T> &);

template <class T>
TMatrix<T> operator*(const TMatrix<T> &, const TMatrix<T> &);
template <class T>
TMatrix<T> operator*(const T c, const TMatrix<T> &);
template <class T>
TMatrix<T> operator*(const TMatrix<T> &, const T c);
template <class T>
TMatrix<T> operator/(const TMatrix<T> &, const T c);

template <class T>
bool operator==(const TMatrix<T> &, const TMatrix<T> &);
template <class T>
bool operator!=(const TMatrix<T> &, const TMatrix<T> &);

template <class T>
std::istream &operator>>(std::istream &, TMatrix<T> &);
template <class T>
std::ostream &operator<<(std::ostream &, const TMatrix<T> &);

template <class T>
TVector<T> operator*(const TMatrix<T> &, const TVector<T> &);
template <class T>
TVector<T> operator*(const TVector<T> &, const TMatrix<T> &);

template <class T>
class TMatrix {
   private:
    T *elems;           // Zeiger auf Feld fuer Matrixelemente
    size_t rows, cols;  // Matrixdimension

   public:
    explicit TMatrix(size_t r = 1, size_t c = 1) {
        size_t len = r * c;
        rows = r;
        cols = c;
#ifndef NDEBUG
        if (len <= 0) {
            matError("Nur Matrix mit positiver Laenge!");
        }
#endif
        elems = new (std::nothrow) T[len];
        if (elems == nullptr) {
            matError("Nicht genuegend Speicher!");
        }

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                (*this)(i, j) = 0;
            }
        }
    }                               // Konstruktor mit Laengenangabe
    ~TMatrix() { delete[] elems; }  // Destruktor
    TMatrix(const TMatrix<T> &mat) {
        rows = mat.rows;
        cols = mat.cols;
        elems = new (std::nothrow) T[rows * cols];
        if (elems == nullptr) {
            matError("Nicht genuegend Speicher!");
        }
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                (*this)(i, j) = mat(i, j);
            }
        }
    }  // Kopierkonstruktor

    T &operator()(size_t i, size_t j) {
#ifndef NDEBUG
        if (i >= rows || j >= cols) matError("Ungueltiger Index!");
#endif
        return elems[i * cols + j];

    }  // Matrixelement schreiben
    T operator()(size_t i, size_t j) const {
#ifndef NDEBUG
        if (i >= rows || j >= cols) matError("Ungueltiger Index!");
#endif
        return elems[i * cols + j];
    }  // Matrixelement lesen

    TMatrix<T> &operator=(const TMatrix<T> &mat) {
#ifndef NDEBUG
        if ((rows != mat.rows) || (cols != mat.cols)) {
            matError("Inkompatible Dimensionen fuer 'Matrix = Matrix'!");
        }
#endif
        for (size_t i = 0; i < mat.rows; i++) {
            for (size_t j = 0; j < mat.cols; j++) {
                (*this)(i, j) = mat(i, j);
            }
        }

        return *this;
    }  // Zuweisung
    TMatrix<T> &operator+=(const TMatrix<T> &mat) {
#ifndef NDEBUG
        if ((rows != mat.rows) || (cols != mat.cols)) {
            matError("Inkompatible Dimensionen fuer 'Matrix = Matrix'!");
        }
#endif
        for (size_t i = 0; i < mat.rows; i++) {
            for (size_t j = 0; j < mat.cols; j++) {
                (*this)(i, j) = (*this)(i, j) + mat(i, j);
            }
        }
        return *this;
    }  // Zuweisungen mit arithm. Operation
    TMatrix<T> &operator-=(const TMatrix<T> &mat) {
#ifndef NDEBUG
        if ((rows != mat.rows) || (cols != mat.cols)) {
            matError("Inkompatible Dimensionen fuer 'Matrix = Matrix'!");
        }
#endif
        for (size_t i = 0; i < mat.rows; i++) {
            for (size_t j = 0; j < mat.cols; j++) {
                (*this)(i, j) = (*this)(i, j) - mat(i, j);
            }
        }
        return *this;
    }
    TMatrix<T> &operator*=(const TMatrix<T> &mat) {
#ifndef NDEBUG
        if ((cols != mat.rows)) {
            matError("Inkompatible Dimensionen fuer 'Matrix = Matrix'!");
        }
#endif
        TMatrix<T> z(rows, mat.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < mat.cols; j++) {
                T sum = 0;
                for (size_t k = 0; k < cols; k++) {
                    sum += (*this)(i, k) * mat(k, j);
                }
                z(i, j) = sum;
            }
        }
        delete[] elems;
        elems = new (std::nothrow) T[rows * mat.cols];
        cols = mat.cols;
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                (*this)(i, j) = z(i, j);
            }
        }

        return *this;
    }
    TMatrix<T> &operator*=(const T c) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                (*this)(i, j) = (*this)(i, j) * c;
            }
        }
        return *this;
    }
    TMatrix<T> &operator/=(const T c) {
#ifndef NDEBUG
        if (c == 0) {
            matError("divider should not be zero");
        }
#endif
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                (*this)(i, j) = (*this)(i, j) / c;
            }
        }
        return *this;
    }

    TMatrix<T> &redim(size_t r, size_t c) {
        delete[] elems;
        rows = r;
        cols = c;
        elems = new (std::nothrow) T[r * c];
        for (size_t i = 0; i < r; i++) {
            for (size_t j = 0; j < c; j++) {
                (*this)(i, j) = 0;
            }
        }
        return *this;
    }                                        // neue Dimensionen festlegen
    size_t getRows() const { return rows; }  // Zeilen
    size_t getCols() const { return cols; }  // Spalten

    friend TMatrix<T> operator+
        <>(const TMatrix<T> &mat1, const TMatrix<T> &mat2);  // Addition
    friend TMatrix<T> operator-
        <>(const TMatrix<T> &, const TMatrix<T> &);     // Subtraktion
    friend TMatrix<T> operator-<>(const TMatrix<T> &);  // Vorzeichen

    friend TMatrix<T> operator*<>(const TMatrix<T> &,
                                  const TMatrix<T> &);  // Matrix mult.
    friend TMatrix<T> operator*<>(const T c, const TMatrix<T> &);  // Vielfache
    friend TMatrix<T> operator*<>(const TMatrix<T> &, const T c);
    friend TMatrix<T> operator/<>(const TMatrix<T> &, const T c);

    friend bool operator==
        <>(const TMatrix<T> &, const TMatrix<T> &);  // Vergleich
    friend bool operator!=<>(const TMatrix<T> &, const TMatrix<T> &);

    friend std::istream &operator>><>(std::istream &, TMatrix<T> &);  // Eingabe
    friend std::ostream &operator<<<>(std::ostream &,
                                      const TMatrix<T> &);  // Ausgabe

    friend TVector<T> operator*<>(const TMatrix<T> &,
                                  const TVector<T> &);  // Matrix-Vektor-
    friend TVector<T> operator*<>(const TVector<T> &,
                                  const TMatrix<T> &);  // Multiplikation

    void matError(const char str[]) const {
        std::cerr << "\nMatrixfehler: " << str << '\n' << std::endl;
        exit(1);
    }  // Fehlermeldung ausgeben
};

// wegen Templates notwendig: Implementierung aller Template-Klassen und
// -Funktionen kommt hierhin!
template <class T>
TMatrix<T> operator+(const TMatrix<T> &mat1, const TMatrix<T> &mat2) {
#ifndef NDEBUG
    if ((mat1.rows != mat2.rows) || (mat1.cols != mat2.cols)) {
        mat2.matError("Inkompatible Dimensionen fuer 'Matrix + Matrix'!");
    }
#endif
    TMatrix<T> matR = mat1;
    matR += mat2;
    return matR;
}
template <class T>
TMatrix<T> operator-(const TMatrix<T> &mat1, const TMatrix<T> &mat2) {
#ifndef NDEBUG
    if ((mat1.rows != mat2.rows) || (mat1.cols != mat2.cols)) {
        mat2.matError("Inkompatible Dimensionen fuer 'Matrix - Matrix'!");
    }
#endif
    TMatrix<T> matR = mat1;
    matR -= mat2;
    return matR;
}  // Subtraktion

template <class T>
TMatrix<T> operator-(const TMatrix<T> &mat) {
    TMatrix<T> matR = mat;
    matR -= mat;
    return matR -= mat;
}  // Vorzeichen

template <class T>
TMatrix<T> operator*(const TMatrix<T> &mat1, const TMatrix<T> &mat2) {
#ifndef NDEBUG
    if ((mat1.cols != mat2.row)) {
        mat2.matError("Inkompatible Dimensionen fuer 'Matrix - Matrix'!");
    }
#endif
    TMatrix<T> matR = mat1;
    matR *= mat2;
    return matR;
}  // Matrix mult.

template <class T>
TMatrix<T> operator*(const T c, const TMatrix<T> &mat) {
    TMatrix<T> matR = mat;
    matR *= c;
    return matR;
}

template <class T>
TMatrix<T> operator*(const TMatrix<T> &mat, const T c) {
    TMatrix<T> matR = mat;
    matR *= c;
    return matR;
}

template <class T>
TMatrix<T> operator/(const TMatrix<T> &mat, const T c) {
    TMatrix<T> matR = mat;
    matR /= c;
    return matR;
}

template <class T>
bool operator==(const TMatrix<T> &mat1, const TMatrix<T> &mat2) {
    if ((mat1.row != mat2.row) || (mat1.col != mat2.col)) {
        return false;
    }

    for (size_t i = 0; i < mat1.rows; i++) {
        for (size_t j = 0; j < mat1.cols; j++) {
            if (mat1(i, j) != mat2(i, j)) {
                return false;
            }
        }
    }

    return true;
}
// Vergleich

template <class T>
bool operator!=(const TMatrix<T> &mat1, const TMatrix<T> &mat2) {
    if ((mat1.row != mat2.row) || (mat1.col != mat2.col)) {
        return true;
    }

    for (size_t i = 0; i < mat1.rows; i++) {
        for (size_t j = 0; j < mat1.cols; j++) {
            if (mat1(i, j) != mat2(i, j)) {
                return true;
            }
        }
    }

    return false;
}
template <class T>
std::istream &operator>>(std::istream &s, TMatrix<T> &mat) {
    std::cout << std::setiosflags(std::ios::right);
    for (size_t i = 0; i < mat.rows; i++) {
        for (size_t j = 0; j < mat.cols; j++) {
            s >> mat(i, j);
        }
    }
    return s;
}  // Eingabe

template <class T>
std::ostream &operator<<(std::ostream &s, const TMatrix<T> &mat) {
    s << std::setiosflags(std::ios::right);
    for (size_t i = 0; i < mat.rows; i++) {
        s << std::endl;
        for (size_t j = 0; j < mat.cols; j++) {
            s << std::setw(4) << mat(i, j) << " ";
        }
    }

    return s << std::endl;
}  // Ausgabe
template <class T>
TVector<T> operator*(const TMatrix<T> &mat, const TVector<T> &vec) {
#ifndef NDEBUG

    if ((mat.cols != vec.getLength())) {
        mat.matError("Inkompatible Dimensionen fuer 'mat * vec'!");
    }
#endif
    TVector<T> vecR(mat.rows);
    for (size_t i = 0; i < mat.rows; i++) {
        T sum = 0;
        for (size_t j = 0; j < mat.cols; j++) {
            sum += mat(i, j) * vec(j);
        }
        vecR(i) = sum;
    }
    return vecR;
}  // Matrix-Vektor-

template <class T>
TVector<T> operator*(const TVector<T> &vec, const TMatrix<T> &mat) {
#ifndef NDEBUG

    if ((mat.rows != vec.getLength())) {
        mat.matError("Inkompatible Dimensionen fuer 'vec * mat'!");
    }
#endif
    TVector<T> vecR(mat.cols);
    for (size_t i = 0; i < mat.cols; i++) {
        T sum = 0;
        for (size_t j = 0; j < mat.rows; j++) {
            sum += mat(j, i) * vec(j);
        }
        vecR(i) = sum;
    }
    return vecR;
}  // Multiplikation

#endif
