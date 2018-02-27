/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Zeile.h
 * Author: Thorsten
 *
 * Created on 12. Dezember 2017, 13:32
 */

#ifndef ZEILE_H
#define ZEILE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <iomanip>

using namespace std;

class Zeile {
private:

    vector<double> zahlen;

public:
    Zeile();
    ~Zeile();

    //Methoden

    void Einlesen(int, ifstream&);
    int gibLaenge() const;
    int operator[](int);
    Zeile& operator+=(Zeile);
    Zeile operator*(double) const;
    bool istNullzeile() const;

    friend ostream& operator<<(ostream&, const Zeile&);

};

#endif /* ZEILE_H */

