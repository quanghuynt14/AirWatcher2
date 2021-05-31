#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <mysql.h>

struct Sensor
{
	std::string id;
	float latitude;
	float longitude;

	void print();
	void create(MYSQL * );
	void drop(MYSQL * );
	void insert(MYSQL * , std::string , std::string , std::string );
	void loadCSV(MYSQL * );
};

#endif //SENSOR_H

