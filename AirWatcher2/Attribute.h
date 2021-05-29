#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <iostream>
#include <string>

struct Attribute
{
	std::string id;
	std::string unit;
	std::string description;

	void print();
};

#endif //ATTRIBUTE_H

