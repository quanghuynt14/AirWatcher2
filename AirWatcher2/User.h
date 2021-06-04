#pragma once

#include <string>

using namespace std;

class User
{
public:
	virtual void create() = 0;
	string getMail();
	string getPassword();
	string getName();
	int auth(string tab, string mail, string pwd);
	
private:
	string mail;
	string pwd_hashed;
	string name;
};

