#include "Pipeline.h"
#include "utils.h"
#include <math.h>

int Pipeline::maxID = 0;
int Pipeline::minID = 0;
Pipeline::Pipeline()
{
	minID = 1;
	ID = ++maxID;
	length = 0;
	diameter = 0;
	repair = false;
	in = -1;
	out = -1;
}
int Pipeline::GetID() const
{
	return ID;
}

int Pipeline::GetmaxID()
{
	return maxID;
}

int Pipeline::GetminID()
{
	return minID;
}

bool Pipeline::GetRepairStatus() const
{
	return repair;
}

int Pipeline::GetWeight() const
{
	return length;
}

int Pipeline::GetPerformance() const
{
	return round(sqrt(pow(diameter,5)/length));
}

void ChangeStatus(Pipeline& newpipe)
{
	newpipe.repair = !newpipe.repair;
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

std::ifstream& operator>>(std::ifstream& fin, Pipeline& newpipe)
{
	fin >> newpipe.length >> newpipe.diameter >> newpipe.repair;
	return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const Pipeline& newpipe)
{
	fout << newpipe.length << std::endl << newpipe.diameter << std::endl << newpipe.repair << std::endl;
	return fout;
}

