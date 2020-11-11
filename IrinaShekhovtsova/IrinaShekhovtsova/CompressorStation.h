#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "utils.h"
class CompressorStation
{
    int ID;
    int shops_working;
    double efficiency;

public:
    std::string Name;
    int shops;
    static int maxID;
    CompressorStation();

    int GetID() const;
    int GetShopsWorking() const;
    friend std::istream& operator >> (std::istream& in, CompressorStation& newstation);
    friend std::ostream& operator << (std::ostream& out, const CompressorStation& newstation);
    friend std::ifstream& operator>>(std::ifstream& in, CompressorStation& newstation);
    friend std::ofstream& operator<<(std::ofstream& fout, const CompressorStation& newstation);
    friend void EditStation(CompressorStation& newstation);
};

