#include "Stoper.h"

#include <iomanip>
#include <sstream>

void Stoper::startStopera() {
    czasStart = std::chrono::high_resolution_clock::now();
}

void Stoper::stopStopera() {
    czasStop = std::chrono::high_resolution_clock::now();
}

double Stoper::pobierzCzasSekundy() const {
    std::chrono::duration<double> roznica = czasStop - czasStart;
    return roznica.count();
}

std::string formatujCzasNaukowo(double sekundy) {
    std::ostringstream zformatowanyCzas;
    zformatowanyCzas << std::scientific << std::setprecision(2) << sekundy;
    return zformatowanyCzas.str();
}
