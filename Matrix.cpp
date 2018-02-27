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
#include <fstream>
#include <sstream>
#include <limits>
#include <math.h>

#include "Matrix.h"

Matrix::Matrix(int _zeilen, int _spalten, ifstream& datei) : zeilen(_zeilen), spalten(_spalten) {

    stringstream fehlermeldung;

    for (int i = 0; i < this->zeilen; i++) {
        try {
            Zeile zeile = Zeile();
            zeile.Einlesen(spalten, datei);

            this->matrix.push_back(zeile);
        } catch (int fehlerspalte) {
            fehlermeldung << "Matrix::Matrix --- Fehler beim Einlesen an Stelle" << "(" << i << "," << fehlerspalte << ")";
            throw (fehlermeldung.str());
        }

    }
}

Matrix::~Matrix() {
}

//Methoden

/*
 *  Methode: protokoll_an
 * 
 *  Aktiviert die Ausgabe der Zwischenergebnisse bei der Berechnung
 * 
 */

void Matrix::protokoll_an() {
    Matrix::zeigeZwischenergebnisse = true;
}

/*
 *  Methode: protokoll_an
 * 
 *  Deaktiviert die Ausgabe der Zwischenergebnisse bei der Berechnung
 * 
 */

void Matrix::protokoll_aus() {
    Matrix::zeigeZwischenergebnisse = false;
}

/*
 *  Methode: operator<<
 * 
 *  Ueberladung des << Operators, damit die Matrix einfach
 *  in cout oder in Stroeme generell uebergeben werden kann.
 * 
 */

ostream& operator<<(ostream& strom, Matrix& matrix) {
    for (int j = 0; j < matrix.gib_m(); j++) {
        strom << matrix.matrix[j] << endl;
    }

    return strom;
}

/*
 *  Methode: reduzierteStufenform
 * 
 *  Der eigentliche Gauss-Algorithmus. Zusaetzlich werden
 *  Nullzeilen am Ende entfernt und ggf. Zwischenergebnisse ausgegeben.
 * 
 */

Matrix Matrix::reduzierteStufenform() const {
    double epsilon = numeric_limits<double>::epsilon();
    int zeile = 0;
    int spalte = 0;
    double pivot;
    double c;
    bool einmaligeNachrichtVorbei = false;

    Matrix a(*this);

    for (int j = 0; j < a.gib_n(); j++, spalte++) {
        pivot = a.matrix[zeile][spalte];
        //cout << "-----------------------" << endl << a << endl;
        if (fabs(pivot) <= epsilon) {
            if (unterPivotNullspalte(a, zeile, spalte)) {
                continue;
            } else {
                int zz = findeTauschzeile(a, zeile, spalte);

                a.tauscheZeilen(a, zz, zeile);
                pivot = a.matrix[zeile][spalte];
            }
        }
        if (a.zeigeZwischenergebnisse) {
            if (!einmaligeNachrichtVorbei) {
                cout << "Zwischenergebnisse -- schrittweise" << endl << endl;
                einmaligeNachrichtVorbei = true;
            }
            cout << a << endl;
        }
        for (int i = zeile + 1; i < a.gib_m(); i++) {
            c = -a.matrix[i][spalte] / pivot;
            a.matrix[i] += a.matrix[zeile] * c;
        }

        zeile++;

        if (zeile >= a.gib_m()) {
            break;
        }
    }
    //Nullzeilen loeschen
    int nullzeilen = 0;
    for (int p = 0; p < a.gib_m(); p++) {
        if (a.matrix[p].istNullzeile()) {
            a.matrix.erase(matrix.begin() + p);
            ++nullzeilen;
        }
    }
    a.setze_m(a.gib_m() - nullzeilen);
    return a;
}

/*
 *  Methode: setze_m
 * 
 *  Setzt einen neuen Wert fuer die Anzahl der Zeilen, damit diese
 *  beim Loeschen der Nullzeilen entsprechend angepasst werden kann.
 * 
 */

void Matrix::setze_m(int m) {
    this->zeilen = m;
}

/*
 *  Methode: unterPivotNullspalte
 * 
 *  Prueft, ob unter dem Pivotelement ausschliesslich Nullen vorkommen,
 *  damit diese Spalte im Hauptalgorithmus uebersprungen werden kann.
 * 
 *  return: bool --- "Nullspalte" ja/nein
 * 
 */

bool Matrix::unterPivotNullspalte(Matrix& a, int zeile, int spalte) const {

    double epsilon = numeric_limits<double>::epsilon();
    bool null;
    for (int i = zeile; i < a.gib_m(); i++) {
        if (fabs(a.matrix[i][spalte]) != epsilon) {
            null = false;
        }
        if (fabs(a.matrix[i][spalte]) <= epsilon) {
            null = true;
        }
    }
    return null;
}

/*
 *  Methode: findeTauschzeile
 * 
 *  Findet die naechste Zeile zum Tauschen mit der aktuellen Zeile, falls
 *  das Pivotelement den Wert 0 hat.
 * 
 *  return: int --- Index der Tauschzeile
 * 
 */

int Matrix::findeTauschzeile(Matrix& a, int zeile, int spalte) const {
    double epsilon = numeric_limits<double>::epsilon();

    for (int i = zeile + 1; i < a.gib_m(); i++) {
        if (fabs(a.matrix[i][spalte]) != epsilon) {
            return i;
        }
    }
    return zeile;
}

/*
 *  Methode: tauscheZeilen
 * 
 *  Tauscht zwei beliebige Zeilen miteinander. Die Werte
 *  an Index 1 und Index 2 werden vertauscht.
 * 
 */

void Matrix::tauscheZeilen(Matrix& a, int z1, int z2) {
    Zeile tempZeile = a.matrix[z1];
    a.matrix[z1] = a.matrix[z2];
    a.matrix[z2] = tempZeile;
}