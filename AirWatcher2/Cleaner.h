#ifndef CLEANER_H
#define CLEANER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <mysql.h>
#include <ctime>

struct Cleaner
{
	std::string id;
	float latitude;
	float longitude;
	std::time_t startWork;
	std::time_t stopWork;

	void print();
	void create(MYSQL *);
	void drop(MYSQL *);
	void insert(MYSQL *, std::string, std::string, std::string, std::string, std::string);
	void loadCSV(MYSQL *);
};

#endif //CLEANER_H

