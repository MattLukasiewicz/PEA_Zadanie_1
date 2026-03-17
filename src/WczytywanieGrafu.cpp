#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "WczytywanieGrafu.h"

using namespace std;

Graf wczytajGraf(string nazwa_pliku, bool pokazKomunikaty) {
    Graf graf;
    graf.rozmiar = 0;
    ifstream plik(nazwa_pliku);

    if (!plik.is_open()) {
        if (pokazKomunikaty) {
            cout << "BLAD: Nie mozna otworzyc pliku: " << nazwa_pliku << endl;
        }
        return graf;
    }

    if (!(plik >> graf.rozmiar)) {
        if (pokazKomunikaty) {
            cout << "BLAD: Nie udalo sie odczytac rozmiaru grafu!" << endl;
        }
        return graf;
    }

    

    graf.macierz.assign(graf.rozmiar, vector<int>(graf.rozmiar, 0));

    for (int i = 0; i < graf.rozmiar; i++) {
        for (int j = 0; j < graf.rozmiar; j++) {
            if (!(plik >> graf.macierz[i][j])) {
                if (pokazKomunikaty) {
                    cout << "BLAD: Niepelna macierz w pliku: " << nazwa_pliku << endl;
                }
                graf.rozmiar = 0;
                graf.macierz.clear();
                return graf;
            }

            if (i == j) {
                graf.macierz[i][j] = -1;
            }
        }
    }

    plik.close();
    if (pokazKomunikaty) {
        cout << "Wczytano macierz o rozmiarze " << graf.rozmiar << "x" << graf.rozmiar << endl;
    }
    return graf;
}

void wyswietlGraf(const Graf& graf) {
    if (graf.rozmiar <= 0) {
        cout << "Graf jest pusty." << endl;
        return;
    }

    cout << "\n--- MACIERZ " << graf.rozmiar << "x" << graf.rozmiar << " ---" << endl;
    for (int i = 0; i < graf.rozmiar; i++) {
        for (int j = 0; j < graf.rozmiar; j++) {
            cout << setw(4) << graf.macierz[i][j] << " ";
        }
        cout << endl;
    }
}