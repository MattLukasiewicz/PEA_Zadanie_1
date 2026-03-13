#pragma once

#include <chrono>
#include <string>

class Stoper {
public:
	void startStopera();
	void stopStopera();
	double pobierzCzasSekundy() const;

private:
	std::chrono::high_resolution_clock::time_point czasStart;
	std::chrono::high_resolution_clock::time_point czasStop;
};

std::string formatujCzasNaukowo(double sekundy);
