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
	void insert(string mail, string pwd, string name, int point, string sensor_id);
	vector<string> findById(int id);

};


