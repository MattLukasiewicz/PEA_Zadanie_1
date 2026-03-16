#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>
#include "WczytywanieKonfiguracji.h"

using namespace std;

namespace {

string trim(const string& tekst) {
    size_t start = 0;
    while (start < tekst.size() && std::isspace(static_cast<unsigned char>(tekst[start]))) {
        start++;
    }

    size_t koniec = tekst.size();
    while (koniec > start && std::isspace(static_cast<unsigned char>(tekst[koniec - 1]))) {
        koniec--;
    }

    return tekst.substr(start, koniec - start);
}

}

Konfiguracja wczytajKonfiguracje(string nazwa_pliku) {
    Konfiguracja konfiguracja; 
    
    // Otwieramy plik
    ifstream plik(nazwa_pliku);
    
    // Jeśli pliku nie ma, program natychmiast kończy działanie błędem!
    // Dzięki temu mamy pewność, że NIGDY nie użyjemy niczego zaszytego w kodzie.
    if (!plik.is_open()) {
        cout << "BLAD KRYTYCZNY: Nie mozna otworzyc pliku " << nazwa_pliku << "!\n";
        exit(1); 
    }

    string linia;
    while (getline(plik, linia)) {
        linia = trim(linia);
        if (linia.empty() || linia[0] == '#') {
            continue;
        }

        int pozycja_rownasi = linia.find('='); 
        
        if (pozycja_rownasi > 0) { 
            string klucz = trim(linia.substr(0, pozycja_rownasi));
            string wartosc = trim(linia.substr(pozycja_rownasi + 1));

            if (klucz == "algorytm") {
                konfiguracja.algorytm = wartosc;
            }
            else if (klucz == "plik_wejsciowy") {
                konfiguracja.plik_wejsciowy = wartosc;
            }
            else if (klucz == "plik_wyjsciowy") {
                konfiguracja.plik_wyjsciowy = wartosc;
            }
            else if (klucz == "liczba_powtorzen") {
                konfiguracja.liczba_powtorzen = stoi(wartosc); 
            }
            else if (klucz == "rozmiar_poczatkowy") {
                konfiguracja.rozmiar_poczatkowy = stoi(wartosc);
            }
            else if (klucz == "rozmiar_koncowy") {
                konfiguracja.rozmiar_koncowy = stoi(wartosc);
            }
            else if (klucz == "pokazuj_pasek_postepu") {
                if (wartosc == "1") {
                    konfiguracja.pokazuj_pasek_postepu = true;
                } else {
                    konfiguracja.pokazuj_pasek_postepu = false;
                }
            }
            else if (klucz == "tryb_z_pliku") {
                if (wartosc == "1") {
                    konfiguracja.tryb_z_pliku = true;
                } else {
                    konfiguracja.tryb_z_pliku = false;
                }
            }
            else if (klucz == "tryb_symulacji") {
                if (wartosc == "1") {
                    konfiguracja.tryb_symulacji = true;
                } else {
                    konfiguracja.tryb_symulacji = false;
                }
            }
            else if (klucz == "czy_symetryczny") {
                if (wartosc == "1") {
                    konfiguracja.czy_symetryczny = true;
                } else {
                    konfiguracja.czy_symetryczny = false;
                }
            }
            else if (klucz == "generuj_pliki_raz") {
                if (wartosc == "1") {
                    konfiguracja.generuj_pliki_raz = true;
                } else {
                    konfiguracja.generuj_pliki_raz = false;
                }
            }
            else if (klucz == "generuj_min_n") {
                konfiguracja.generuj_min_n = stoi(wartosc);
            }
            else if (klucz == "generuj_max_n") {
                konfiguracja.generuj_max_n = stoi(wartosc);
            }
            else if (klucz == "katalog_sym") {
                konfiguracja.katalog_sym = wartosc;
            }
            else if (klucz == "katalog_asym") {
                konfiguracja.katalog_asym = wartosc;
            }
            else if (klucz == "wyswietl_macierze_symulacji") {
                if (wartosc == "1") {
                    konfiguracja.wyswietl_macierze_symulacji = true;
                } else {
                    konfiguracja.wyswietl_macierze_symulacji = false;
                }
            }
        }
    }
    
    plik.close();
    return konfiguracja;
}