#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "WczytywanieKonfiguracji.h"

using namespace std;

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
        if (linia == "" || linia[0] == '#') {
            continue;
        }

        int pozycja_rownasi = linia.find('='); 
        
        if (pozycja_rownasi > 0) { 
            string klucz = linia.substr(0, pozycja_rownasi);
            string wartosc = linia.substr(pozycja_rownasi + 1);

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
        }
    }
    
    plik.close();
    return konfiguracja;
}