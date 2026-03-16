#pragma once

#include <vector>
#include "WczytywanieGrafu.h"

int policzKosztTrasy(const Graf& graf, const std::vector<int>& trasaMiast);
int NajblizszySasiad(const Graf& graf);

void PrzegladZupelny(const Graf& graf);