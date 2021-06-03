#pragma once

#include <string>

using namespace std;

class User
{
public:
	virtual void create() = 0;
	string getMail();
	string getPassword();
	
private:
	string mail;
	string pwd_hashed;
};

