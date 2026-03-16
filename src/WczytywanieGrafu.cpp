#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
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

    string slowo;
    if (!(plik >> slowo)) {
        if (pokazKomunikaty) {
            cout << "BLAD: Plik jest pusty!" << endl;
        }
        return graf;
    }

    if (isdigit(static_cast<unsigned char>(slowo[0]))) {
        graf.rozmiar = stoi(slowo);
        graf.macierz.assign(graf.rozmiar, vector<int>(graf.rozmiar, 0));
    } else {
        do {
            if (slowo == "DIMENSION:" || slowo == "DIMENSION") {
                string wartosc;
                plik >> wartosc;
                if (wartosc == ":") {
                    plik >> wartosc;
                }
                graf.rozmiar = stoi(wartosc);
                graf.macierz.assign(graf.rozmiar, vector<int>(graf.rozmiar, 0));
            } else if (slowo == "EDGE_WEIGHT_SECTION") {
                break;
            }
        } while (plik >> slowo);
    }

    if (graf.rozmiar <= 0) {
        if (pokazKomunikaty) {
            cout << "BLAD: Nie udalo sie odczytac rozmiaru grafu!" << endl;
        }
        return graf;
    }

    if (graf.macierz.empty()) {
        graf.macierz.assign(graf.rozmiar, vector<int>(graf.rozmiar, 0));
    }

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