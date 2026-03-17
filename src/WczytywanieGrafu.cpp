#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "WczytywanieGrafu.h"

using namespace std;

Graf wczytajGraf(string nazwa_pliku, int& optimum) {
    Graf graf;
    graf.rozmiar = 0;
    optimum = 0; 
    ifstream plik(nazwa_pliku);

    if (!plik.is_open()) return graf; // Zabezpieczenie przed brakiem pliku

    plik >> graf.rozmiar; // 1. Pobieramy pierwszą liczbę z pliku (rozmiar N)

    graf.macierz.assign(graf.rozmiar, vector<int>(graf.rozmiar, 0));

    for (int i = 0; i < graf.rozmiar; i++) {
        for (int j = 0; j < graf.rozmiar; j++) {
            
            plik >> graf.macierz[i][j]; // 2. Pobieramy wagę drogi z pliku!

            if (i == j) {
                graf.macierz[i][j] = -1; // Ustawiamy przekątną
            }
        }
    }

    string ignoruj;
    getline(plik, ignoruj, '='); 
    plik >> optimum;             

    plik.close();
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