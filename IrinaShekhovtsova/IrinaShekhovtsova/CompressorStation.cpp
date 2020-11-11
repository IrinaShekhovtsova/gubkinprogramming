#include "CompressorStation.h"

int CompressorStation::maxID = 2000;
CompressorStation::CompressorStation()
{
    ID = ++maxID;
    Name = "NULL";
    shops = 0;
    shops_working = 0;
    efficiency = 0;
}

int CompressorStation::GetID() const
{
    return ID;
}

int CompressorStation::GetShopsWorking() const
{
    return shops_working;
}

std::istream& operator>>(std::istream& in, CompressorStation& newstation)
{
    std::cout << "Type the name: ";
    in.ignore();
    getline(in, newstation.Name);
    std::cout << "Type the amount of shops (0-200): ";
    newstation.shops = CheckInt(0, 200);
    std::cout << "Type the efficiency (0-1): ";
    newstation.efficiency = CheckDouble(0, 1);
    return in;
}
std::ostream& operator<<(std::ostream& out, const CompressorStation& newstation)
{
    out << "ID: " << newstation.ID << "\n";
    out << "The name: " << newstation.Name << "\n";
    out << "The amount of shops: " << newstation.shops << "\n";
    out << "The amount of working shops: " << newstation.shops_working << "\n";
    out << "The efficiency: " << newstation.efficiency << "\n";
    return out;
}

std::ifstream& operator>>(std::ifstream& fin, CompressorStation& newstation)
{
    fin.ignore();
    getline(fin, newstation.Name);
    fin >> newstation.shops >> newstation.shops_working >> newstation.efficiency;
    return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const CompressorStation& newstation)
{
    fout << newstation.Name << std::endl << newstation.shops << std::endl << newstation.shops_working << std::endl
         << newstation.efficiency << std::endl;
    return fout;
}

void EditStation(CompressorStation& newstation)
{
    std::cout << "To run a shop type 1, to stop a shop type 0: ";
    int n = CheckInt(0, 1);
    if (newstation.shops_working == 0 && n == 0) std::cout << "There are no working shops" << std::endl;
    else if (newstation.shops_working == newstation.shops && n == 1) std::cout << "All shops are working" << std::endl;
    else if (n == 1) newstation.shops_working += 1; else newstation.shops_working -= 1;
}


