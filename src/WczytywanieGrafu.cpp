#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "WczytywanieGrafu.h"

using namespace std;

Graf wczytajGraf(string nazwa_pliku) {
    Graf graf;
    ifstream plik(nazwa_pliku);

    if (!plik.is_open()) {
        cout << "BLAD: Nie mozna otworzyc pliku: " << nazwa_pliku << endl;
        graf.rozmiar = 0;
        return graf;
    }

    if (!(plik >> graf.rozmiar)) {
        cout << "BLAD: Plik jest pusty lub uszkodzony!" << endl;
        graf.rozmiar = 0;
        return graf;
    }

    graf.macierz.resize(graf.rozmiar, vector<int>(graf.rozmiar));

    for (int i = 0; i < graf.rozmiar; i++) {
        for (int j = 0; j < graf.rozmiar; j++) {
            if (!(plik >> graf.macierz[i][j])) {
                break;
            }
        }
    }

    plik.close();
    cout << "Wczytano macierz o rozmiarze " << graf.rozmiar << "x" << graf.rozmiar << endl;
    return graf;
}