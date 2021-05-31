#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <mysql.h>
#include <ctime>

struct Measurement
{
	std::time_t date;
	std::string sensorId;
	std::string attributeId;
	float value;

	void print();
	void create(MYSQL *);
	void drop(MYSQL *);
	void insert(MYSQL *, std::string, std::string, std::string, std::string);
	void loadCSV(MYSQL *);
};

