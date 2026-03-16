#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "WczytywanieKonfiguracji.h"
#include "WczytywanieGrafu.h"
#include "Algorytmy.h"
#include "Stoper.h"
#include "Generator.h"

using namespace std;

void rysujPasekPostepu(int aktualny, int wszystkich, bool czyPokazywac) {
    if (!czyPokazywac || wszystkich == 0) return;

    constexpr int szerokoscPaska = 30;
    if (aktualny > wszystkich) {
        aktualny = wszystkich;
    }

    int procent = (aktualny * 100) / wszystkich;
    int zapelnienie = (aktualny * szerokoscPaska) / wszystkich;

    cout << "\rPostep: [";
    for (int i = 0; i < szerokoscPaska; i++) {
        cout << (i < zapelnienie ? '#' : '-');
    }
    cout << "] " << setw(3) << procent << "%" << flush;
}

void uruchomTestPoprawnosciZPliku(const Konfiguracja& konf) {
    cout << "\n>Sprawdzanie poprawności algorytmow" << endl;

    Graf grafZPliku = wczytajGraf(konf.plik_wejsciowy);
    if (grafZPliku.rozmiar <= 0) {
        cout << "Nie udalo sie wczytac grafu testowego z pliku: " << konf.plik_wejsciowy << endl;
        return;
    }

    Stoper stoper;
    stoper.startStopera();
    int kosztTrasy = -1;

    if (konf.algorytm == "NN") {
        kosztTrasy = NajblizszySasiad(grafZPliku);
    } else {
        PrzegladZupelny(grafZPliku);
    }
    stoper.stopStopera();

    cout << "Koszt trasy: " << kosztTrasy << endl;
    cout << "Czas testu [ms]: " << stoper.pobierzCzasMs() << endl;
}

void uruchomSymulacjePrzegladu(const Konfiguracja& konf) {
    Stoper stoper;
    bool czySymetryczny = konf.czy_symetryczny;
    string typProblemu = czySymetryczny ? "Symetryczny" : "Asymetryczny";
    ofstream plik(konf.plik_wyjsciowy, ios::app);

    if (konf.liczba_powtorzen <= 0 || konf.rozmiar_koncowy < konf.rozmiar_poczatkowy) {
        cout << "BLAD: Niepoprawne parametry symulacji w config.ini" << endl;
        return;
    }

    int wszystkieKroki = (konf.rozmiar_koncowy - konf.rozmiar_poczatkowy + 1) * konf.liczba_powtorzen;
    int aktualnyKrok = 0;

    cout << "\nSymulacja algorytmu przegladu zupelnego " << typProblemu << " <<<" << endl;
    cout << "Zakres N: " << konf.rozmiar_poczatkowy << "-" << konf.rozmiar_koncowy
         << ", powtorzenia: " << konf.liczba_powtorzen << endl;
        cout << "Rozmiar N | Sredni Czas [ms]" << endl;
    rysujPasekPostepu(0, wszystkieKroki, konf.pokazuj_pasek_postepu);

    for (int n = konf.rozmiar_poczatkowy; n <= konf.rozmiar_koncowy; n++) {
        double sumaCzasowMs = 0.0;

        for (int i = 1; i <= konf.liczba_powtorzen; i++) {
            Graf g;
            if (czySymetryczny) {
                g = generujGrafSymetryczny(n);
            } else {
                g = generujGrafAsymetryczny(n);
            }

            stoper.startStopera();
            PrzegladZupelny(g);
            stoper.stopStopera();

            sumaCzasowMs += stoper.pobierzCzasMs();

            aktualnyKrok++;
            rysujPasekPostepu(aktualnyKrok, wszystkieKroki, konf.pokazuj_pasek_postepu);
        }

        double sredniCzas = sumaCzasowMs / static_cast<double>(konf.liczba_powtorzen);

        if (konf.pokazuj_pasek_postepu) {
            cout << "\r" << string(60, ' ') << "\r";
        }

        cout << setw(9) << n << " | "
             << setw(16) << fixed << setprecision(3) << sredniCzas << endl;

        rysujPasekPostepu(aktualnyKrok, wszystkieKroki, konf.pokazuj_pasek_postepu);

        if (plik.is_open()) {
            plik << typProblemu << ";" << n << ";" << sredniCzas << "\n";
            plik.flush();
        }
    }

    if (konf.pokazuj_pasek_postepu) {
        cout << endl;
    }

    plik.close();
}

int main() {
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
        if(konf.algorytm == "BF"){
            ofstream czysc(konf.plik_wyjsciowy);
            czysc << "Typ;N;Sredni_Czas_ms\n";
            czysc.close();
            uruchomSymulacjePrzegladu(konf);
        }
        
    }
    return 0;
}