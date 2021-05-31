#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include <mysql.h>

struct Attribute
{
	std::string id;
	std::string unit;
	std::string description;

	void print();
	void create(MYSQL *);
	void drop(MYSQL *);
	void insert(MYSQL *, std::string, std::string, std::string);
	void loadCSV(MYSQL *);
};

#endif //ATTRIBUTE_H

