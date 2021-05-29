#ifndef CLEANER_H
#define CLEANER_H

#include <string>
#include <ctime>
#include "Coordinate.h"

struct Cleaner
{
	std::string id;
	Coordinate position;
	std::time_t startWork;
	std::time_t finishWork;

	void print();
};

#endif //CLEANER_H

