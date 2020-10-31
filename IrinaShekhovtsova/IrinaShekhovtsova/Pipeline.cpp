#include "Pipeline.h"
#include "utils.h"

int Pipeline::maxID = 1000;
Pipeline::Pipeline()
{
	ID = ++maxID;
	length = 0;
	diameter = 0;
	repair = false;
}
std::istream& operator>>(std::istream& in, Pipeline& newpipe)
{
	std::cout << "Type the length (0-2000): ";
	newpipe.length = CheckDouble(0, 2000);
	std::cout << "Type the diametr (0-1420): ";
	newpipe.diameter = CheckInt(0, 1420);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Pipeline& newpipe)
{
	out << "ID: " << newpipe.ID << "\n";
	out << "The length: " << newpipe.length << "\n";
	out << "The diametr: " << newpipe.diameter << "\n";
	(newpipe.repair == false) ? out << "Not in repair\n" : out << "In repair\n";
	return out;
}

