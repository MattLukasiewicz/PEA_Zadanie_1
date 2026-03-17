#pragma once

#include <vector>
#include <string>

struct Graf {
    int rozmiar;
    std::vector<std::vector<int>> macierz;
};

Graf wczytajGraf(std::string nazwa_pliku, int& optimum);
void wyswietlGraf(const Graf& graf);