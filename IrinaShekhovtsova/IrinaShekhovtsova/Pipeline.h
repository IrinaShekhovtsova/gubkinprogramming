#pragma once
#include <string>
#include <iostream>
#include <fstream>
class Pipeline
{
    bool repair;
    int ID;

public:    
    double length;
    int diameter;
    static int maxID;
    Pipeline();

    int GetID() const;
    int GetRepairStatus() const;
    friend void ChangeStatus(Pipeline& newpipe);
    friend std::istream& operator >> (std::istream& in, Pipeline& newpipe);
    friend std::ostream& operator << (std::ostream& out, const Pipeline& newpipe);
    friend std::ifstream& operator>>(std::ifstream& in, Pipeline& newpipe);
    friend std::ofstream& operator<<(std::ofstream& fout, const Pipeline& newpipe);
};

