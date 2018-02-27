/* 
 * Gauss-Algorithmus und Matrizen
 * O. Henkel
 *
 * Test der Klasse Zeile und Matrix
 *
 * Nov./Dez. 2011
 * Sep 2012: angepasst fuer Praktikum
 */

#include "Zeile.h"                             // Matrixzeilen
#include "Matrix.h"                            // Matrizen
bool Matrix::zeigeZwischenergebnisse=true;     // Protokoll an
#include<iostream>
#include<fstream>

using namespace std;

int main() {
  ifstream f_in;
  f_in.open("Matrixdaten");

  cout << "Zeilentest" << endl;
  cout << "----------" << endl;
  Zeile z1,z2;
  try {
    z1.Einlesen(3,f_in);
    z2.Einlesen(4,f_in);
    cout << z1[3] << endl;                      // unzulaessiger Indexwert
  }
  catch (string& fehlertext) {
    cout << "!!! " << fehlertext << endl;
  }
  try {
    z1+=z2;                                     // Dimensionen passen nicht
  }
  catch (string& fehlertext) {
    cout << "!!! " << fehlertext << endl;
  }
  cout << endl << endl;

  cout << "Matrixtest" << endl;
  cout << "----------" << endl; 
  try {
    Matrix A(4,5,f_in);
    cout << "A: " << A.gib_m() << "x" << A.gib_n() << endl;
    cout << A << endl;
    Matrix StufeA(A.reduzierteStufenform());
    cout << "Stufenform: " << endl;
    cout << StufeA << endl;
    cout << endl<< "---------------------" << endl << endl;
    getchar();
    

    Matrix::protokoll_aus();                   // Ab jetzt Protokoll aus
    Matrix B(3,2,f_in);
    cout << "B: " << B.gib_m() << "x" << B.gib_n() << endl;
    cout << B << endl;
    Matrix StufeB(B.reduzierteStufenform());
    cout << "Stufenform: " << endl;
    cout << StufeB << endl;
    cout << endl<< "---------------------" << endl << endl;
    getchar();

    Matrix C(2,3,f_in);
    cout << "C: " << C.gib_m() << "x" << C.gib_n() << endl;
    cout << C << endl;
    Matrix StufeC(C.reduzierteStufenform());
    cout << "Stufenform: " << endl;
    cout << StufeC << endl;
 
}
  catch (string& fehlermeldung) { cout << "!!!  " << fehlermeldung << endl; }

  f_in.close(); 
return 0;
}

