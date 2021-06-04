#pragma once

#include <string>
#include <mysql.h>
#include "User.h"


class Agency : public User
{
public:
	const string table_name = "agencies";

	void create();
	void drop();
	void insert(string mail, string pwd, string name);

};

