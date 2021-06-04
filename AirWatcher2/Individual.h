#pragma once

#include <string>
#include <vector>
#include <mysql.h>
#include "User.h"


class Individual : public User
{
public:
	const string table_name = "individuals";

	void create();
	void drop();
	void insert(string id_str, string mail, string pwd, string name, int point, string sensor_id);
	vector<string> findInfoById(const int id);
	string findIdString(const int id);
	string findName(const int id);
	string findSensor(const int ind_id);
	vector<int> findAllIndividual();

};


