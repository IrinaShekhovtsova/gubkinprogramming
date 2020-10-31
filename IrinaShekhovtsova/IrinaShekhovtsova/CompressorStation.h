#pragma once
#include <string>
#include <iostream>
#include "utils.h"
class CompressorStation
{
public:
    int ID;
    static int maxID;
    std::string Name;
    int shops;
    int shops_working;
    double efficiency;
    CompressorStation();

    friend std::istream& operator >> (std::istream& in, CompressorStation& newstation);
    friend std::ostream& operator << (std::ostream& out, const CompressorStation& newstation);
    friend void EditStation(CompressorStation& newstation);
};

