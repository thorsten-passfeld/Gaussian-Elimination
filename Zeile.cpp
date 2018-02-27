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

#include "Zeile.h"

Zeile::Zeile() {


}

Zeile::~Zeile() {
}

/*
 *  Methode: gibLaenge
 * 
 *  Gibt die Laenge der aktuellen Zeile an den Aufrufer zurueck.
 * 
 *  return: int --- Die Laenge des Zahlenvektors
 * 
 */

int Zeile::gibLaenge() const{
    return this->zahlen.size();
}

/*
 *  Methode: istNullzeile
 * 
 *  Ermittelt, ob die Zeile ausschliesslich aus Nullen besteht.
 * 
 *  return: bool --- "Nullzeile" ja/nein
 * 
 */

bool Zeile::istNullzeile() const{
    double epsilon = numeric_limits<double>::epsilon();
    bool istNull;

    for (int i = 0; i < this->zahlen.size(); i++) {
        if (fabs(this->zahlen[i]) != epsilon) {
            istNull = false;
            //return false;
        }
        if (fabs(this->zahlen[i]) <= epsilon) {
            istNull = true;
        }
    }
    return istNull;
}

/*
 *  Methode: Einlesen
 * 
 *  Liest eine Zeile aus einer Datei ein. Es werden nur so viele
 *  Werte eingelesen, wie spezifiziert.
 * 
 */

void Zeile::Einlesen(int anzahlZahlen, ifstream& datei) {
    double zahl = 0;

    for (int i = 0; i < anzahlZahlen; i++) {

        if (!datei.eof()) {
            datei >> zahl;
            if (datei.fail()) {
                throw (i);
            }
            this->zahlen.push_back(zahl);
        } else cout << "Ende der Datei erreicht." << endl;

    }
}

/*
 *  Methode: operator<<
 * 
 *  Ueberladung des << Operators, damit die Zeile einfach
 *  in cout oder in Stroeme generell uebergeben werden kann.
 * 
 */

ostream& operator<<(ostream& strom, const Zeile& zeile) {
    for (int i = 0; i < zeile.gibLaenge(); i++) {
        strom << right << setw(10) << zeile.zahlen[i];
    }
    return strom;
}

/*
 *  Methode: operator[]
 * 
 *  Ueberladung des [] Operators, damit ein Index der Zeile einfach
 *  eingegeben werden kann.
 * 
 *  return int --- Wert der Zeile im Index
 * 
 */

int Zeile::operator[](int index) {
    string fehlertext = "Zeilen::operator[] -- falscher Zeilenindex";
    if (index < 0 || index >= this->zahlen.size()) {
        throw (fehlertext);
    } else {
        return this->zahlen[index];
    }
}

/*
 *  Methode: operator+=
 * 
 *  Ueberladung des += Operators, damit Zeilenobjekte addiert werden koennen.
 * 
 */

Zeile& Zeile::operator+=(Zeile z2) {
    string fehlertext = "Zeile::operator+= --- Dimensionen stimmen nicht";

    if (this->zahlen.size() != z2.zahlen.size()) {
        throw (fehlertext);
    }

    for (int i = 0; i < this->zahlen.size(); i++) {
        this->zahlen[i] += z2.zahlen[i];
    }
    return *this;
}

Zeile Zeile::operator*(double faktor) const {
    Zeile z = *this;
    for (int i = 0; i < z.zahlen.size(); i++) {
        z.zahlen[i] *= faktor;
    }
    return z;
}