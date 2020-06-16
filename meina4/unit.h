/*******************************************************************
 *  Name       : unit.h                                            *
 *  Verwendung : Schnittstelle zu Praktikumsumgebung (MAPRA),      *
 *               Numerische Loesung von gewoehnlichen AWPs durch   *
 *               Runge-Kutta-Verfahren mit Schrittweitensteuerung  *
 *  Autor      : V. Reichelt, IGPM RWTH Aachen                     *
 *  Datum      : Jan 1997                                          *
 *  Aenderung  : Jun 1997                                          *
 *  Ueberarb.  : Mai 1998, Karsten Urban                           *
 *               Jun 1999, Titus Barsch                            *
 *                         Korrekturen zur richtigen Verwendung    *
 *                         des Typs long double (fabsl,...)        *
 *               Jan 2007, Kolja Brix                              *
 *               Mai 2016, Felix Gruber                            *
 *                         C-Funktionen fabsl und sqrtl durch      *
 *                         C++-Äquivalente fabs und sqrt ersetzt.  *
 *                         Benutze bool statt int.                 *
 *  Sprache    : C++                                               *
 *  Bemerkung  : Fuer g++                                          *
 ******************************************************************/

#include <functional>

#include "tmatrix.h"
#include "tvector.h"

using real = long double;
using Vector = TVector<real>;
using Matrix = TMatrix<real>;

// Anzahl der Beispielfunktionen
extern const int num_examples;

// Gravitationskonstante
const real kGrav = 6.67e-11;

// Koeffizienten fuer das Runge-Kutta-Verfahren
extern Vector rk_alpha, rk_gamma, rk_delta;
extern Matrix rk_beta;
extern unsigned int rk_p;  // Ordnung
extern real eps;

// Funktionstyp zum Uebergeben der rechten Seite der DGL
using VFFunction = std::function<Vector(real, const Vector&)>;

// siehe Uebungsblatt

void getExample(int ex_id, Vector& mass, VFFunction& f, Vector& y0, real& tBeg,
                real& tEnd, real& h0, bool doDraw, bool doOutput = true);

void checkStep(real t, const Vector& y, bool doDraw, bool doOutput = true);

void checkSolution(real t, const Vector& y);
