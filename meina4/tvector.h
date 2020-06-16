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
#include <iomanip>
#include <iostream>
// forward declaration of class TVector
template <class T>
class TVector;

// forward declaration of template friend functions
template <class T>
TVector<T> operator+(const TVector<T> &, const TVector<T> &);
template <class T>
TVector<T> operator-(const TVector<T> &, const TVector<T> &);
template <class T>
TVector<T> operator-(const TVector<T> &);

template <class T>
T operator*(const TVector<T> &, const TVector<T> &);

template <class T>
TVector<T> operator*(T c, const TVector<T> &);
template <class T>
TVector<T> operator*(const TVector<T> &, T c);
template <class T>
TVector<T> operator/(const TVector<T> &, T c);

template <class T>
bool operator==(const TVector<T> &, const TVector<T> &);
template <class T>
bool operator!=(const TVector<T> &, const TVector<T> &);

template <class T>
std::istream &operator>>(std::istream &, TVector<T> &);
template <class T>
std::ostream &operator<<(std::ostream &, const TVector<T> &);

template <class T>  // T steht hier fuer den Parameter, z.B.
class TVector       // int, float, double
{
   private:
    T *elems;       // Zeiger auf Feld fuer Vektorelemente
    size_t length;  // Vektorlaenge

   public:
    explicit TVector(size_t len = 1);  // Konstruktor mit Laengenangabe
    ~TVector() { delete[] elems; }     // Destruktor
    TVector(const TVector &);          // Kopierkonstruktor

    T &operator()(size_t);       // Vektorelement schreiben
    T operator()(size_t) const;  // Vektorelement lesen

    TVector<T> &operator=(const TVector<T> &);  // Zuweisung
    TVector<T> &operator+=(
        const TVector<T> &);  // Zuweisungen mit arithm. Operation
    TVector<T> &operator-=(const TVector<T> &);
    TVector<T> &operator*=(T c);
    TVector<T> &operator/=(T c);

    TVector<T> &redim(size_t);                   // neue Laenge festlegen
    size_t getLength() const { return length; }  // Laenge
    long double norm2() const;                   // Euklidische Norm des Vektors
    T normMax() const;                           // Maximum-Norm des Vektors

    // Addition, Subtraktion, Aendern des Vorzeichens
    friend TVector<T> operator+<>(const TVector<T> &, const TVector<T> &);
    friend TVector<T> operator-<>(const TVector<T> &, const TVector<T> &);
    friend TVector<T> operator-<>(const TVector<T> &);

    // Skalarprodukt
    friend T operator*<>(const TVector<T> &, const TVector<T> &);

    friend TVector<T> operator*<>(T c,
                                  const TVector<T> &);  // konstante Vielfache
    friend TVector<T> operator*<>(const TVector<T> &, T c);
    friend TVector<T> operator/<>(const TVector<T> &, T c);

    friend bool operator==
        <>(const TVector<T> &, const TVector<T> &);  // Vergleich
    friend bool operator!=<>(const TVector<T> &, const TVector<T> &);

    friend std::istream &operator>><>(std::istream &, TVector<T> &);  // Eingabe
    friend std::ostream &operator<<<>(std::ostream &,
                                      const TVector<T> &);  // Ausgabe

    void vecError(const char str[]) const {
        std::cerr << "\nVektorfehler: " << str << '\n' << std::endl;
        exit(1);
    };  // Fehlermeldung ausgeben
};

// wegen Templates notwendig: Implementierung aller Template-Klassen und
// -Funktionen kommt hierhin!
// ----- Konstruktor -----
template <class T>
TVector<T>::TVector(size_t len) {
#ifndef NDEBUG
    if (len <= 0) {
        vecError("Nur Vektoren mit positiver Laenge!");
    }
#endif

    length = len;

    elems = new (std::nothrow) T[length];
    if (elems == nullptr) {
        vecError("Nicht genuegend Speicher!");
    }

    for (size_t i = 0; i < length; i++) {
        (*this)(i) = T(0);
    }
}

template <class T>
TVector<T>::TVector(const TVector<T> &x) {
    length = x.length;

    elems = new (std::nothrow) T[length];
    if (elems == nullptr) {
        vecError("Nicht genuegend Speicher!");
    }

    for (size_t i = 0; i < length; i++) {
        (*this)(i) = x(i);
    }
}

// ===========================================
//      Vektorelement schreiben und lesen
// ===========================================

// ----- Schreib- und Lesezugriff auf Vektorelemente -----

template <class T>
T &TVector<T>::operator()(size_t i) {
#ifndef NDEBUG
    if (i >= length) vecError("Ungueltiger Index!");
#endif

    return elems[i];
}

// ----- Lesezugriff auf Elemente konstanter Vektoren -----

template <class T>
T TVector<T>::operator()(size_t i) const {
#ifndef NDEBUG
    if (i >= length) vecError("Ungueltiger Index!");
#endif

    return elems[i];
}

template <class T>
TVector<T> &TVector<T>::operator=(const TVector<T> &x) {
#ifndef NDEBUG
    if (length != x.length) {
        vecError("Inkompatible Dimensionen fuer 'Vektor = Vektor'!");
    }
#endif

    for (size_t i = 0; i < length; i++) {
        (*this)(i) = x(i);
    }

    return *this;
}

// ----- Zuweisungsoperator mit Addition "+=" ----

template <class T>
TVector<T> &TVector<T>::operator+=(const TVector<T> &x) {
    // ***** Hier fehlt was *****
#ifndef NDEBUG
    if (length != x.length) {
        vecError("Inkompatible Dimensionen fuer 'Vektor = Vektor'!");
    }
#endif
    for (size_t i = 0; i < length; i++) {
        (*this)(i) = (*this)(i) + x(i);
    }
    return *this;
}

// ----- Zuweisungsoperator mit Subtraktion "-=" ----
template <class T>
TVector<T> &TVector<T>::operator-=(const TVector<T> &x) {
    // ***** Hier fehlt was *****
#ifndef NDEBUG
    if (length != x.length) {
        vecError("Inkompatible Dimensionen fuer 'Vektor = Vektor'!");
    }
#endif
    for (size_t i = 0; i < length; i++) {
        (*this)(i) = (*this)(i)-x(i);
    }
    return *this;
}

// ----- Zuweisungsoperator mit Multiplikation "*=" ----
template <class T>
TVector<T> &TVector<T>::operator*=(T c) {
    // ***** Hier fehlt was *****
    for (size_t i = 0; i < length; i++) {
        (*this)(i) = (*this)(i)*c;
    }
    return *this;
}

// ----- Zuweisungsoperator mit Divsion "/=" ----
template <class T>
TVector<T> &TVector<T>::operator/=(T c) {
    // ***** Hier fehlt was *****
#ifndef NDEBUG
    if (c == 0) {
        vecError("division by 0");
    }
#endif
    for (size_t i = 0; i < length; i++) {
        (*this)(i) = (*this)(i) / c;
    }
    return *this;
}

template <class T>
TVector<T> &TVector<T>::redim(size_t l) {
    // ***** Hier fehlt was *****

    T *elemsNeu = new (std::nothrow) T[l];
#ifndef NDEBUG
    if (elemsNeu == nullptr) {
        vecError("Nicht genuegend Speicher!");
    }
#endif
    for (size_t i = 0; i < l; i++) {
        if (i < length) {
            elemsNeu[i] = 0;
        } else {
            elemsNeu[i] = 0;
        }
    }

    length = l;
    delete[] elems;
    elems = elemsNeu;
    return *this;
}

// ======================
//      Vektornormen
// ======================

// ----- Euklidische Norm -----
template <class T>
long double TVector<T>::norm2() const {
    // ***** Hier fehlt was *****
    T sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += (*this)(i) * (*this)(i);
    }
    sum = sqrt(sum);
    return sum;
}

// ----- Maximum-Norm -----
template <class T>
T TVector<T>::normMax() const {
    // ***** Hier fehlt was *****
    T maxAbs = 0;
    for (size_t i = 0; i < length; i++) {
        if (fabs((*this)(i)) > maxAbs) {
            maxAbs = fabs((*this)(i));
        }
    }
    return maxAbs;
}
template <class T>
TVector<T> operator+(const TVector<T> &x, const TVector<T> &y) {
#ifndef NDEBUG
    if (x.length != y.length) {
        x.vecError("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
    }
#endif

    TVector<T> z = x;
    return z += y;
}
template <class T>
TVector<T> operator-(const TVector<T> &x, const TVector<T> &y) {
#ifndef NDEBUG
    if (x.length != y.length) {
        x.vecError("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
    }
#endif

    TVector<T> z = x;
    return z -= y;
}
template <class T>
TVector<T> operator-(const TVector<T> &x) {
    TVector<T> z = x;
    z -= x;
    return z -= x;
}

// Skalarprodukt
template <class T>
T operator*(const TVector<T> &x, const TVector<T> &y) {
#ifndef NDEBUG
    if (x.length != y.length) {
        x.vecError("Inkompatible Dimensionen fuer 'Vektor * Vektor'!");
    }
#endif
    T sum = 0;
    for (size_t i = 0; i < x.length; i++) {
        sum += x(i) * y(i);
    }
    return sum;
}

template <class T>
TVector<T> operator*(T c, const TVector<T> &x) {
    TVector<T> z = x;
    return z *= c;
}  // konstante Vielfache

template <class T>
TVector<T> operator*(const TVector<T> &x, T c) {
    TVector<T> z = x;
    return z *= c;
}

template <class T>
TVector<T> operator/(const TVector<T> &x, T c) {
    TVector<T> z = x;
    return z /= c;
}

template <class T>
bool operator==(const TVector<T> &x, const TVector<T> &y) {
    if (x.length != y.length) {
        return false;
    }

    for (size_t i = 0; i < x.length; i++) {
        if (x(i) != y(i)) {
            return false;
        }
    }

    return true;
}  // Vergleich

template <class T>
bool operator!=(const TVector<T> &x, const TVector<T> &y) {
    if (x.length != y.length) {
        return true;
    }
    for (size_t i = 0; i < x.length; i++) {
        if (x(i) != y(i)) {
            return true;
        }
    }
}
template <class T>
std::ostream &operator<<(std::ostream &s, const TVector<T> &x) {
    s << std::setiosflags(std::ios::right);
    for (size_t i = 0; i < x.length; i++) {
        // s << "\n(" << std::setw(4) << i << ") " << x(i);
        s << std::endl << x(i);
    }

    return s << std::endl;
}

template <class T>
std::istream &operator>>(std::istream &s, TVector<T> &x) {
    std::cout << std::setiosflags(std::ios::right);
    for (size_t i = 0; i < x.length; i++) {
        std::cout << "\n(" << std::setw(4) << i << ") ";
        s >> x(i);
    }
    return s;
}  // Eingabe

#endif
