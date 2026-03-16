#include "Generator.h"

#include <filesystem>
#include <fstream>
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



void zapiszGrafDoTsplib(const Graf& graf, const string& nazwa, const string& typ, const string& sciezka) {
    ofstream plik(sciezka);
    if (!plik.is_open()) {
        return;
    }

    plik << "NAME: " << nazwa << "\n";
    plik << "TYPE: " << typ << "\n";
    plik << "DIMENSION: " << graf.rozmiar << "\n";
    plik << "EDGE_WEIGHT_TYPE: EXPLICIT\n";
    plik << "EDGE_WEIGHT_FORMAT: FULL_MATRIX\n";
    plik << "EDGE_WEIGHT_SECTION\n";

    for (int i = 0; i < graf.rozmiar; i++) {
        for (int j = 0; j < graf.rozmiar; j++) {
            plik << graf.macierz[i][j];
            if (j + 1 < graf.rozmiar) {
                plik << " ";
            }
        }
        plik << "\n";
    }

    plik << "EOF\n";
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

    for (int n = min_n; n <= max_n; n++) {
        Graf sym = generujGrafSymetryczny(n);
        Graf asym = generujGrafAsymetryczny(n);

        zapiszGrafDoTsplib(sym, "sym_" + to_string(n), "TSP", katalogSym + "/sym_" + to_string(n) + ".tsp");
        zapiszGrafDoTsplib(asym, "asym_" + to_string(n), "ATSP", katalogAsym + "/asym_" + to_string(n) + ".atsp");
    }
}
