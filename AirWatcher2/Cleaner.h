#pragma once

#include <string>
#include <mysql.h>

using namespace std;

struct Cleaner
{
	const string table_name = "cleaners";
	string id;
	float latitude;
	float longitude;
	string start;
	string stop;

	void create();
	void drop();
	void insert(string id, string lat, string lon, string start, string stop);
	void loadCSV();
	Cleaner findById(string id);
};


