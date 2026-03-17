#include "Generator.h"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <random>

using namespace std;

Graf przygotujPustyGraf(int rozmiar) {
    Graf graf;

    if (rozmiar <= 0) {
        graf.rozmiar = 0;
        return graf;
    }

    graf.rozmiar = rozmiar;
    graf.macierz.assign(rozmiar, vector<int>(rozmiar, -1));

    return graf;
}



Graf generujGrafSymetryczny(int rozmiar) {
    Graf graf = przygotujPustyGraf(rozmiar);

    if (graf.rozmiar == 0) {
        return graf;
    }

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> losowaWaga(1, 100);

    for (int i = 0; i < rozmiar; i++) {
        graf.macierz[i][i] = -1;
        for (int j = i + 1; j < rozmiar; j++) {
            int waga = losowaWaga(generator);
            graf.macierz[i][j] = waga;
            graf.macierz[j][i] = waga;
        }
    }

    return graf;
}

Graf generujGrafAsymetryczny(int rozmiar) {
    Graf graf = przygotujPustyGraf(rozmiar);

    if (graf.rozmiar == 0) {
        return graf;
    }

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> losowaWaga(1, 100);

    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            if (i == j) {
                graf.macierz[i][j] = -1;
            } else {
                graf.macierz[i][j] = losowaWaga(generator);
            }
        }
    }

    return graf;
}



void zapiszGrafWFormacieMacierzy(const Graf& graf, const string& sciezka) {
    ofstream plik(sciezka);
    if (!plik.is_open()) {
        return;
    }

    plik << graf.rozmiar << "\n";

    for (int i = 0; i < graf.rozmiar; i++) {
        for (int j = 0; j < graf.rozmiar; j++) {
            plik << setw(3) << graf.macierz[i][j];
            if (j + 1 < graf.rozmiar) plik << " ";
        }
        plik << "\n";
    }

    plik << "\n";
}

void wyczyscFolderZPlikow(const string& sciezkaFolderu) {
    if (!std::filesystem::exists(sciezkaFolderu)) {
        return;
    }

    for (const auto& wpis : std::filesystem::directory_iterator(sciezkaFolderu)) {
        if (wpis.is_regular_file()) {
            std::filesystem::remove(wpis.path());
        }
    }
}



void generujBazePlikow(int min_n, int max_n, const string& katalogSym, const string& katalogAsym) {
    if (min_n > max_n || min_n <= 0) {
        return;
    }

    if (katalogSym.empty() || katalogAsym.empty()) {
        return;
    }

    std::filesystem::create_directories(katalogSym);
    std::filesystem::create_directories(katalogAsym);
    wyczyscFolderZPlikow(katalogSym);
    wyczyscFolderZPlikow(katalogAsym);

    for (int n = min_n; n <= max_n; n++) {
        Graf sym = generujGrafSymetryczny(n);
        Graf asym = generujGrafAsymetryczny(n);

        zapiszGrafWFormacieMacierzy(sym, katalogSym + "/sym_" + to_string(n) + ".tsp");
        zapiszGrafWFormacieMacierzy(asym, katalogAsym + "/asym_" + to_string(n) + ".atsp");
    }
}
