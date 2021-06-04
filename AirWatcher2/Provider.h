#pragma once

#include <string>
#include <vector>
#include <mysql.h>
#include "User.h"


class Provider : public User
{
public:
	const string table_name = "providers";

	void create();
	void drop();
	void insert(string id_str, string mail, string pwd, string name, string cleaner_id);

	string findIdString(const int provider_id);
	string findCleanerByProvider(const int provider_id);
	vector<int> findAllProvider();
};

