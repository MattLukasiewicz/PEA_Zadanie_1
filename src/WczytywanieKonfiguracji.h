#pragma once

#include <string>

struct Konfiguracja {
    std::string algorytm;
    std::string plik_wejsciowy;
    std::string plik_wyjsciowy;
    int liczba_powtorzen;
    int rozmiar_poczatek;
    int rozmiar_koniec;
    bool pokazuj_pasek_postepu;
};

Konfiguracja wczytajKonfiguracje(std::string nazwa_pliku);