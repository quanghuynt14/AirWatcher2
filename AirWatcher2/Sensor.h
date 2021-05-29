#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include "Coordinate.h"

struct Sensor
{
	std::string id;
	Coordinate position;

	void print();
	void input();
};

#endif //SENSOR_H

