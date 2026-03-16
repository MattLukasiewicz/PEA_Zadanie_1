#pragma once

#include <string>

struct Konfiguracja {
    std::string algorytm = "NN";
    std::string plik_wejsciowy = "dane/matrix_11x11.atsp";
    std::string plik_wyjsciowy = "wyniki/wyniki.csv";
    int liczba_powtorzen = 1;
    int rozmiar_poczatkowy = 6;
    int rozmiar_koncowy = 15;
    bool pokazuj_pasek_postepu = false;
    bool tryb_z_pliku = false;
    bool tryb_symulacji = false;
    bool czy_symetryczny = false;
    bool generuj_pliki_raz = false;
    int generuj_min_n = 6;
    int generuj_max_n = 15;
    std::string katalog_sym = "sym";
    std::string katalog_asym = "asym";
    bool wyswietl_macierze_symulacji = false;
};

Konfiguracja wczytajKonfiguracje(std::string nazwa_pliku);