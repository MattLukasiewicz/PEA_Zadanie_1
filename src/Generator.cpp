#include "Generator.h"

#include <random>

Graf generujGraf(int rozmiar, bool czySymetryczny) {
    Graf graf;

    if (rozmiar <= 0) {
        graf.rozmiar = 0;
        return graf;
    }

    graf.rozmiar = rozmiar;
    graf.macierz.assign(rozmiar, std::vector<int>(rozmiar, -1));

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> losowaWaga(1, 100);

    if (czySymetryczny) {
        for (int i = 0; i < rozmiar; i++) {
            graf.macierz[i][i] = -1;
            for (int j = i + 1; j < rozmiar; j++) {
                int waga = losowaWaga(generator);
                graf.macierz[i][j] = waga;
                graf.macierz[j][i] = waga;
            }
        }
    } else {
        for (int i = 0; i < rozmiar; i++) {
            for (int j = 0; j < rozmiar; j++) {
                if (i == j) {
                    graf.macierz[i][j] = -1;
                } else {
                    graf.macierz[i][j] = losowaWaga(generator);
                }
            }
        }
    }

    return graf;
}
