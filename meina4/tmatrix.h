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

template<class T>
class TMatrix;

template<class T>
TMatrix<T> operator+(const TMatrix<T> &, const TMatrix<T> &);
template<class T>
TMatrix<T> operator-(const TMatrix<T> &, const TMatrix<T> &);
template<class T>
TMatrix<T> operator-(const TMatrix<T> &);

template<class T>
TMatrix<T> operator*(const TMatrix<T> &, const TMatrix<T> &);
template<class T>
TMatrix<T> operator*(const T c, const TMatrix<T> &);
template<class T>
TMatrix<T> operator*(const TMatrix<T> &, const T c);
template<class T>
TMatrix<T> operator/(const TMatrix<T> &, const T c);

template<class T>
bool operator==(const TMatrix<T> &, const TMatrix<T> &);
template<class T>
bool operator!=(const TMatrix<T> &, const TMatrix<T> &);

template<class T>
std::istream &operator>>(std::istream &, TMatrix<T> &);
template<class T>
std::ostream &operator<<(std::ostream &, const TMatrix<T> &);

template<class T>
TVector<T> operator*(const TMatrix<T> &, const TVector<T> &);
template<class T>
TVector<T> operator*(const TVector<T> &, const TMatrix<T> &);

template<class T>
class TMatrix {
   private:
    T *elems;           // Zeiger auf Feld fuer Matrixelemente
    size_t rows, cols;  // Matrixdimension

   public:
    explicit TMatrix(size_t r = 1, size_t c = 1);  // Konstruktor mit Laengenangabe
    ~TMatrix() {
        delete[] elems;
    }                             // Destruktor
    TMatrix(const TMatrix<T> &);  // Kopierkonstruktor

    T &operator()(size_t, size_t);       // Matrixelement schreiben
    T operator()(size_t, size_t) const;  // Matrixelement lesen

    TMatrix<T> &operator=(const TMatrix<T> &);   // Zuweisung
    TMatrix<T> &operator+=(const TMatrix<T> &);  // Zuweisungen mit arithm. Operation
    TMatrix<T> &operator-=(const TMatrix<T> &);
    TMatrix<T> &operator*=(const TMatrix<T> &);
    TMatrix<T> &operator*=(const T);
    TMatrix<T> &operator/=(const T);

    TMatrix<T> &redim(size_t, size_t);  // neue Dimensionen festlegen
    size_t getRows() const {
        return rows;
    }  // Zeilen
    size_t getCols() const {
        return cols;
    }  // Spalten

    friend TMatrix<T> operator+<>(const TMatrix<T> &, const TMatrix<T> &);  // Addition
    friend TMatrix<T> operator-<>(const TMatrix<T> &, const TMatrix<T> &);  // Subtraktion
    friend TMatrix<T> operator-<>(const TMatrix<T> &);                      // Vorzeichen

    friend TMatrix<T> operator*<>(const TMatrix<T> &, const TMatrix<T> &);  // Matrix mult.
    friend TMatrix<T> operator*<>(const T c, const TMatrix<T> &);           // Vielfache
    friend TMatrix<T> operator*<>(const TMatrix<T> &, const T c);
    friend TMatrix<T> operator/<>(const TMatrix<T> &, const T c);

    friend bool operator==<>(const TMatrix<T> &, const TMatrix<T> &);  // Vergleich
    friend bool operator!=<>(const TMatrix<T> &, const TMatrix<T> &);

    friend std::istream &operator>><>(std::istream &, TMatrix<T> &);        // Eingabe
    friend std::ostream &operator<<<>(std::ostream &, const TMatrix<T> &);  // Ausgabe

    friend TVector<T> operator*<>(const TMatrix<T> &, const TVector<T> &);  // Matrix-Vektor-
    friend TVector<T> operator*<>(const TVector<T> &, const TMatrix<T> &);  // Multiplikation

    void matError(const char str[]) const;  // Fehlermeldung ausgeben
};

// wegen Templates notwendig: Implementierung aller Template-Klassen und -Funktionen kommt hierhin!

#endif
