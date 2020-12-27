#pragma once
#include <string>
#include <iostream>
#include <fstream>
class Pipeline
{
    bool repair;
    int ID;
    int length;
    int diameter;
    static int maxID;
    static int minID;
public:   
    int in;
    int out;
    Pipeline();

    int GetID() const;
    static int GetmaxID();
    static int GetminID();
    bool GetRepairStatus() const;
    int GetWeight() const;
    int GetPerformance() const;
    friend void ChangeStatus(Pipeline& newpipe);
    friend std::istream& operator >> (std::istream& in, Pipeline& newpipe);
    friend std::ostream& operator << (std::ostream& out, const Pipeline& newpipe);
    friend std::ifstream& operator>>(std::ifstream& fin, Pipeline& newpipe);
    friend std::ofstream& operator<<(std::ofstream& fout, const Pipeline& newpipe);
};

