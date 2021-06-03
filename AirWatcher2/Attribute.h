#pragma once

#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include <mysql.h>

using namespace std;

struct Attribute
{
	const string table_name = "attributes";

	void create();
	void drop();
	void insert(string id, string unit, string des);
	void loadCSV();
};

