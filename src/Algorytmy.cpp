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

int NajblizszySasiad(const Graf& graf) {
    int liczbaMiast = graf.rozmiar;
    if (liczbaMiast <= 0) return -1;

    vector<bool> odwiedzone(liczbaMiast, false);
    int aktualneMiasto = 0;
    int calkowityKoszt = 0;
    odwiedzone[0] = true;

    for (int krok = 1; krok < liczbaMiast; krok++) {
        int najlepszyKoszt = INT_MAX;
        int najlepszeMiasto = -1;

        for (int miasto = 0; miasto < liczbaMiast; miasto++) {
            int kosztPrzejscia = graf.macierz[aktualneMiasto][miasto];

            if (!odwiedzone[miasto] && kosztPrzejscia > 0) {
                if (kosztPrzejscia < najlepszyKoszt) {
                    najlepszyKoszt = kosztPrzejscia;
                    najlepszeMiasto = miasto;
                }
                // OBSLUGA REMISU
                else if (kosztPrzejscia == najlepszyKoszt && (najlepszeMiasto == -1 || miasto < najlepszeMiasto)) {
                    najlepszeMiasto = miasto;
                }
            }
        }

        if (najlepszeMiasto == -1) {
            return -1;
        }

        odwiedzone[najlepszeMiasto] = true;
        calkowityKoszt += najlepszyKoszt;
        aktualneMiasto = najlepszeMiasto;
    }

    int kosztPowrotu = graf.macierz[aktualneMiasto][0];
    if (kosztPowrotu <= 0) {
        return -1;
    }

    calkowityKoszt += kosztPowrotu;
    return calkowityKoszt;
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
    cout << "Przeglad zupelny" << endl;
    cout << "Najlepszy koszt: " << minimalny_koszt << endl;
    cout << "Najlepsza trasa: ";
    for (int i = 0; i < liczbaMiast; i++) cout << najlepsza_trasa[i] << " -> ";
    cout << najlepsza_trasa[0] << endl; // Powrot
    */
}