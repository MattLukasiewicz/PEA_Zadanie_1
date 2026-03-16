#include "Generator.h"

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
