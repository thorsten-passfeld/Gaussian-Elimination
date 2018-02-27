/*
 * --------------------------------------------------------
 * 
 * Aufgabe: Gauss-Algorithmus
 * Autor: Thorsten Paßfeld
 * 
 * Ein Programm, welches Zeilen einer Matrix aus einer Datei
 * einliest und auf sie den Gauss-Algorithmus anwendet.
 * 
 * Praktikum Grundlagen Programmierung, HS Osnabrueck
 * --------------------------------------------------------
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

#include "Zeile.h"

using namespace std;

class Matrix {
private:

    int zeilen, spalten;
    vector<Zeile> matrix;
    static bool zeigeZwischenergebnisse;

public:
    Matrix(int, int, ifstream&);
    static void protokoll_aus();
    static void protokoll_an();
    ~Matrix();

    //Methoden
    bool unterPivotNullspalte(Matrix&, int, int) const;
    int findeTauschzeile(Matrix&, int zeile, int spalte) const;

    int gib_m() const {
        return this->zeilen;
    }
    void setze_m(int);

    int gib_n() const {
        return this->spalten;
    }
    friend ostream& operator<<(ostream&, Matrix&);
    void tauscheZeilen(Matrix&, int, int);
    Matrix reduzierteStufenform() const;

};

#endif /* MATRIX_H */

