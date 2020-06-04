/**************************************************
 *  Name       : tvector.h                        *
 *  Verwendung : Template Vektorklasse (Header)   *
 *  Autoren    : V. Reichelt, T. Barsch, K. Urban *
 *               IGPM RWTH Aachen                 *
 *  Datum      : Nov '96, Okt '97                 *
 *  Sprache    : C++                              *
 **************************************************/

#ifndef _TVECTOR_H  // damit der Header nicht mehrfach eingelesem wird
#define _TVECTOR_H

#include <cmath>
#include <iostream>

// forward declaration of class TVector
template<class T>
class TVector;

// forward declaration of template friend functions
template<class T>
TVector<T> operator+(const TVector<T> &, const TVector<T> &);
template<class T>
TVector<T> operator-(const TVector<T> &, const TVector<T> &);
template<class T>
TVector<T> operator-(const TVector<T> &);

template<class T>
T operator*(const TVector<T> &, const TVector<T> &);

template<class T>
TVector<T> operator*(T c, const TVector<T> &);
template<class T>
TVector<T> operator*(const TVector<T> &, T c);
template<class T>
TVector<T> operator/(const TVector<T> &, T c);

template<class T>
bool operator==(const TVector<T> &, const TVector<T> &);
template<class T>
bool operator!=(const TVector<T> &, const TVector<T> &);

template<class T>
std::istream &operator>>(std::istream &, TVector<T> &);
template<class T>
std::ostream &operator<<(std::ostream &, const TVector<T> &);

template<class T>  // T steht hier fuer den Parameter, z.B.
class TVector      // int, float, double
{
   private:
    T *elems;       // Zeiger auf Feld fuer Vektorelemente
    size_t length;  // Vektorlaenge

   public:
    explicit TVector(size_t len = 1);  // Konstruktor mit Laengenangabe
    ~TVector() {
        delete[] elems;
    }                          // Destruktor
    TVector(const TVector &);  // Kopierkonstruktor

    T &operator()(size_t);       // Vektorelement schreiben
    T operator()(size_t) const;  // Vektorelement lesen

    TVector<T> &operator=(const TVector<T> &);   // Zuweisung
    TVector<T> &operator+=(const TVector<T> &);  // Zuweisungen mit arithm. Operation
    TVector<T> &operator-=(const TVector<T> &);
    TVector<T> &operator*=(T c);
    TVector<T> &operator/=(T c);

    TVector<T> &redim(size_t);  // neue Laenge festlegen
    size_t getLength() const {
        return length;
    }                           // Laenge
    long double norm2() const;  // Euklidische Norm des Vektors
    T normMax() const;          // Maximum-Norm des Vektors

    // Addition, Subtraktion, Aendern des Vorzeichens
    friend TVector<T> operator+<>(const TVector<T> &, const TVector<T> &);
    friend TVector<T> operator-<>(const TVector<T> &, const TVector<T> &);
    friend TVector<T> operator-<>(const TVector<T> &);

    // Skalarprodukt
    friend T operator*<>(const TVector<T> &, const TVector<T> &);

    friend TVector<T> operator*<>(T c, const TVector<T> &);  // konstante Vielfache
    friend TVector<T> operator*<>(const TVector<T> &, T c);
    friend TVector<T> operator/<>(const TVector<T> &, T c);

    friend bool operator==<>(const TVector<T> &, const TVector<T> &);  // Vergleich
    friend bool operator!=<>(const TVector<T> &, const TVector<T> &);

    friend std::istream &operator>><>(std::istream &, TVector<T> &);        // Eingabe
    friend std::ostream &operator<<<>(std::ostream &, const TVector<T> &);  // Ausgabe

    void vecError(const char str[]) const;  // Fehlermeldung ausgeben
};

// wegen Templates notwendig: Implementierung aller Template-Klassen und -Funktionen kommt hierhin!

#endif
