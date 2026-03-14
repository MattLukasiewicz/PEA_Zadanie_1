#include "Stoper.h"

#include <iomanip>
#include <sstream>

void Stoper::startStopera() {
    czasStart = std::chrono::high_resolution_clock::now();
}

void Stoper::stopStopera() {
    czasStop = std::chrono::high_resolution_clock::now();
}

double Stoper::pobierzCzasMs() const {
    std::chrono::duration<double, std::milli> roznica = czasStop - czasStart;
    return roznica.count();
}


