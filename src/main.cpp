#include <iostream>
#include <iomanip>
#include "WczytywanieKonfiguracji.h"
#include "WczytywanieGrafu.h"

using namespace std;

int main() {
    Konfiguracja moja_konf = wczytajKonfiguracje("config.ini");

    Graf moj_graf = wczytajGraf(moja_konf.plik_wejsciowy);

    if (moj_graf.rozmiar > 0) {
        cout << "\nMacierz odleglosci z pliku " << moja_konf.plik_wejsciowy << ":\n";
        for (int i = 0; i < moj_graf.rozmiar; i++) {
            for (int j = 0; j < moj_graf.rozmiar; j++) {
                cout << setw(4) << moj_graf.macierz[i][j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}