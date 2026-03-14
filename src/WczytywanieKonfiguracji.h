#pragma once

#include <string>

struct Konfiguracja {
    std::string algorytm;
    std::string plik_wejsciowy;
    std::string plik_wyjsciowy;
    int liczba_powtorzen;
    int rozmiar_poczatkowy;
    int rozmiar_koncowy;
    bool pokazuj_pasek_postepu;
    bool tryb_z_pliku;
    bool tryb_symulacji;
};

Konfiguracja wczytajKonfiguracje(std::string nazwa_pliku);