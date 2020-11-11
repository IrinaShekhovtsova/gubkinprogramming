#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "utils.h"
class CompressorStation
{
    static int maxID;
    static int minID;
    int ID;
    int shops_working;
    double efficiency;
    int shops;
    std::string Name;

public:
    CompressorStation();

    int GetID() const;
    int GetShopsWorking() const;
    int GetShops() const;
    std::string GetName() const;
    static int GetmaxID();
    static int GetminID();
    friend std::istream& operator >> (std::istream& in, CompressorStation& newstation);
    friend std::ostream& operator << (std::ostream& out, const CompressorStation& newstation);
    friend std::ifstream& operator>>(std::ifstream& in, CompressorStation& newstation);
    friend std::ofstream& operator<<(std::ofstream& fout, const CompressorStation& newstation);
    friend void EditStation(CompressorStation& newstation);
};

