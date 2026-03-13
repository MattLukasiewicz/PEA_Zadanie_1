#include <iostream>
#include "WczytywanieKonfiguracji.h"
#include "WczytywanieGrafu.h"
#include "Algorytmy.h"

using namespace std;

int main() {

    Konfiguracja konf = wczytajKonfiguracje("config.ini");

    cout << "Zaladowano konfiguracje." << endl;
    cout << "Plik wejsciowy: " << konf.plik_wejsciowy << endl;
    cout << "Algorytm: " << konf.algorytm << endl;
    cout << "----------------------------------------------" << endl;

    Graf mojGraf = wczytajGraf(konf.plik_wejsciowy);

    if (mojGraf.rozmiar > 0) {
        PrzegladZupelny(mojGraf);
    } else {
        cout << "BŁĄD: Nie udalo sie wczytac grafu. Sprawdz sciezke w config.ini!" << endl;
    }

    return 0;
}