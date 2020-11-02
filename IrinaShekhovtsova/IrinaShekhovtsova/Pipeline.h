#pragma once
#include <string>
#include <iostream>
class Pipeline
{
public:
    int ID;
    static int maxID;
    double length;
    int diameter;
    bool repair;
    Pipeline();

    friend std::istream& operator >> (std::istream& in, Pipeline& newpipe);
    friend std::ostream& operator << (std::ostream& out, const Pipeline& newpipe);
};

