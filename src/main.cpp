#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "WczytywanieKonfiguracji.h"
#include "WczytywanieGrafu.h"
#include "Algorytmy.h"
#include "Stoper.h"
#include "Generator.h"

using namespace std;

// 1. Obliczanie teoretycznej zajetosci pamieci przez algorytm i graf
long long obliczZajetaPamiec(int n) {
    long long pamiecMacierzy = n * n * sizeof(int); 
    long long narzutWektorow = n * sizeof(std::vector<int>) + sizeof(std::vector<std::vector<int>>);
    long long pamiecTrasy = n * sizeof(int) + sizeof(std::vector<int>);
    return pamiecMacierzy + narzutWektorow + pamiecTrasy;
}

// 2. Wskaznik postepu
void rysujPasekPostepu(int aktualny, int wszystkich, bool czyPokazywac) {
    if (!czyPokazywac || wszystkich == 0) return;

    int procent = (aktualny * 100) / wszystkich;
    cout << "\rPostep: " << aktualny << "/" << wszystkich << " (" << procent << "%)" << flush;
}

void uruchomTestPoprawnosciZPliku(const Konfiguracja& konf) {
    cout << "\n>>> TEST POPRAWNOSCI (DANE Z PLIKU) <<<" << endl;

    Graf grafZPliku = wczytajGraf(konf.plik_wejsciowy);
    if (grafZPliku.rozmiar <= 0) {
        cout << "Nie udalo sie wczytac grafu testowego z pliku: " << konf.plik_wejsciowy << endl;
        return;
    }

    Stoper stoper;
    stoper.startStopera();
    PrzegladZupelny(grafZPliku);
    stoper.stopStopera();

    cout << "Czas testu [ms]: " << stoper.pobierzCzasMs() << endl;
}

// 3. Glowna funkcja symulacji
void uruchomSymulacje(bool czySymetryczny, const Konfiguracja& konf) {
    Stoper stoper;
    string typProblemu = czySymetryczny ? "Symetryczny" : "Asymetryczny";
    ofstream plik(konf.plik_wyjsciowy, ios::app); // Dopisywanie do CSV

    cout << "\n>>> SYMULACJA: " << typProblemu << " <<<" << endl;
    cout << "N\tSredni Czas [ms]\tPamiec [B]" << endl;

    // Pobieramy parametry z pliku konfiguracyjnego
    for (int n = konf.rozmiar_poczatkowy; n <= konf.rozmiar_koncowy; n++) {
        
        double sumaCzasowMs = 0.0;

        // Pętla badająca X losowych instancji dla danego rozmiaru N
        for (int i = 1; i <= konf.liczba_powtorzen; i++) {
            
            // Wskaznik postepu na ekranie
            rysujPasekPostepu(i, konf.liczba_powtorzen, konf.pokazuj_pasek_postepu);

            Graf g = generujGraf(n, czySymetryczny);
            
            stoper.startStopera();
            PrzegladZupelny(g); // Zakładamy, że ta funkcja zwraca wynik bez niepotrzebnych coutów
            stoper.stopStopera();

            sumaCzasowMs += stoper.pobierzCzasMs(); // Czas w milisekundach
        }
        
        // Czyszczenie linii z postepem (wersja kompatybilna z Windows terminal)
        if (konf.pokazuj_pasek_postepu) {
            cout << "\r                                        \r";
        }

        // Wyliczenie sredniej
        double sredniCzas = sumaCzasowMs / konf.liczba_powtorzen;
        long long pamiecBajty = obliczZajetaPamiec(n);

        // Ekran (zgodnie z wytycznymi: Rozmiar, Srednia, Pamiec, Jednostki)
        cout << n << "\t" << sredniCzas << " ms\t\t" << pamiecBajty << " B" << endl;

        // Plik CSV (Średniki używane do podziału kolumn w Excelu)
        if (plik.is_open()) {
            plik << typProblemu << ";" << n << ";" << sredniCzas << ";" << pamiecBajty << "\n";
            plik.flush();
        }

        // Warunek awaryjny - "rozsądny czas" 30 min (1 800 000 ms)
        if (sredniCzas > 1800000.0) { 
            cout << "Przekroczono limit 30 min dla rozmiaru " << n << ". Przerywam badanie tej grupy." << endl;
            break;
        }
    }
    plik.close();
}

int main() {
    // 1. Wczytujemy plik
    Konfiguracja konf = wczytajKonfiguracje("config.ini");

    cout << "Zaladowano konfiguracje. Liczba powtorzen: " << konf.liczba_powtorzen << endl;

    if (!konf.tryb_z_pliku && !konf.tryb_symulacji) {
        cout << "BLAD: Oba tryby sa wylaczone. Ustaw tryb_z_pliku=1 lub tryb_symulacji=1 w config.ini" << endl;
        return 1;
    }

    if (konf.tryb_z_pliku) {
        uruchomTestPoprawnosciZPliku(konf);
    }

    if (konf.tryb_symulacji) {
        ofstream czysc(konf.plik_wyjsciowy);
        czysc << "Typ;Rozmiar_N;Sredni_Czas_ms;Zajeta_Pamiec_B\n";
        czysc.close();

        uruchomSymulacje(false, konf);
        uruchomSymulacje(true, konf);
    }

    cout << "\nBadania zakonczone. Wyniki w pliku: " << konf.plik_wyjsciowy << endl;
    
    return 0;
}