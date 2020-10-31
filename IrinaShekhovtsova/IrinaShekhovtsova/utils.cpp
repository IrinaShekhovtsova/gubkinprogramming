#include "utils.h"
int CheckInt(int min, int max)
{
    double x;
    while ((std::cin >> x).fail() || x<min || x>max || x - (int)x != 0)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Type again in the range from " << min << " to " << max << ": ";
    }
    return (int)x;
}
double CheckDouble(double min, double max)
{
    double x;
    while ((std::cin >> x).fail() || x<min || x>max)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Type again in the range from " << min << " to " << max << ": ";
    }
    return x;
}