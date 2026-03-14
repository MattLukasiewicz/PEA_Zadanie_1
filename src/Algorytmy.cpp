#include <iostream>
#include <vector>
#include <algorithm> 
#include <climits>   
#include "Algorytmy.h"

using namespace std;

int policzKosztTrasy(const Graf& graf, const vector<int>& trasaMiast) {
    int kosztTrasy = 0;
    int liczbaMiast = graf.rozmiar;

    for (int i = 0; i < liczbaMiast - 1; i++) {
        int start = trasaMiast[i];
        int koniec = trasaMiast[i + 1];
        kosztTrasy += graf.macierz[start][koniec];
    }

    int ostatnieMiasto = trasaMiast[liczbaMiast - 1];
    int pierwszeMiasto = trasaMiast[0];
    kosztTrasy += graf.macierz[ostatnieMiasto][pierwszeMiasto];

    return kosztTrasy;
}

void PrzegladZupelny(const Graf& graf) {
    if (graf.rozmiar <= 0) return;

    int liczbaMiast = graf.rozmiar;
    vector<int> trasaMiast;
    for (int i = 0; i < liczbaMiast; i++) trasaMiast.push_back(i);

    vector<int> najlepsza_trasa;
    int minimalny_koszt = INT_MAX;


    do {
        int aktualny_koszt = policzKosztTrasy(graf, trasaMiast);

        if (aktualny_koszt < minimalny_koszt) {
            minimalny_koszt = aktualny_koszt;
            najlepsza_trasa = trasaMiast;
        }

    } while (next_permutation(trasaMiast.begin() + 1, trasaMiast.end()));
    /*
    cout << "--- WYNIK BRUTE FORCE ---" << endl;
    cout << "Najlepszy koszt: " << minimalny_koszt << endl;
    cout << "Najlepsza trasa: ";
    for (int i = 0; i < liczbaMiast; i++) cout << najlepsza_trasa[i] << " -> ";
    cout << najlepsza_trasa[0] << endl; // Powrot
    cout << "-------------------------" << endl;
    */
   cout << "Minimalny koszt: " << minimalny_koszt << endl;
}