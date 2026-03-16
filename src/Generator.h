#pragma once

#include "WczytywanieGrafu.h"

Graf generujGrafSymetryczny(int rozmiar);
Graf generujGrafAsymetryczny(int rozmiar);
void generujBazePlikow(int min_n, int max_n, const std::string& katalogSym, const std::string& katalogAsym);
