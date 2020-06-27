/*****************************************************************
 *  Name       : unit.h                                           *
 *  Verwendung : Schnittstelle zu Praktikumsumgebung (MAPRA),     *
 *               Vier-Gewinnt mit Minimax-Algorithmus             *
 *  Autor      : Juergen Bey, V.R., A.V. IGPM RWTH Aachen         *
 *  Datum      : Nov '98, Jan '00                                 *
 *  Sprache    : C++                                              *
 *****************************************************************/

#ifndef _UNIT_H
#define _UNIT_H

extern const unsigned int numRows;
extern const unsigned int numCols;
extern const unsigned int numGames;

static const int GAME_END = -1;

// difficulty 0 = Eingabe ueber die Tatstatur
void startGame(unsigned int difficulty);

// Mit nextTurn uebergeben Sie die Nummer der Spalte (0...numCols-1),
// die Ihr Programm fuer den naechsten Spielstein ausgewaehlt hat.
// Zurueckgegeben wird Ihnen dann der naechste Zug der Praktikumsumgebung
// bzw. von der Tastatur.
int nextTurn(int column);

#endif
