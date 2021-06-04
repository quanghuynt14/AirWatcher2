#pragma once

#include <string>
#include <mysql.h>
#include "User.h"


class Provider : public User
{
public:
	const string table_name = "providers";

	void create();
	void drop();
	void insert(string mail, string pwd, string name, string cleaner_id);


};

