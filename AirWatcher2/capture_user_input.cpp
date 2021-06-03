#include "capture_user_input.h"

bool check_format_date(string date) 
{
	regex regLine(R"(\d{4}\-(0[1-9]|1[012])\-(0[1-9]|[12][0-9]|3[01])$)");

	if (regex_match(date, regLine)) {
		return true;
	}
	else {
		cout << "Wrong format date. (format YYYY-MM-DD) : ";
		return false;
	}
}

bool check_time_period(string date) 
{
	regex regLine(R"(2019\-(0[1-9]|1[012])\-(0[1-9]|[12][0-9]|3[01])$)");

	if (regex_match(date, regLine)) {
		return true;
	}
	else {
		cout << "No data for this time period. (Data sets 2019-01-01 to 2019-12-31) : ";
		return false;
	}
}

bool check_float(string num) 
{
	regex regLine(R"([-|+]?([0-9]*\.[0-9]+|[0-9]+)$)");

	if (regex_match(num, regLine)) {
		return true;
	}
	else {
		return false;
	}
}

bool check_sensor_id(string s) 
{
	regex regLine(R"(Sensor([1-9]|[1-9][0-9])$)");

	if (regex_match(s, regLine)) {
		return true;
	}
	else {
		return false;
	}
}

bool check_cleaner_id(string s)
{
	regex regLine(R"(Cleaner[0-1]$)");

	if (regex_match(s, regLine)) {
		return true;
	}
	else {
		return false;
	}
}

string get_date(string invite) 
{
	cout << invite << " (format YYYY-MM-DD) : ";
	string d;
	getline(cin, d);
	while (!check_format_date(d) || !check_time_period(d)) {
		getline(cin, d);
	}
	d.append(" 12:00:00");
	return d;
}

float get_float(string invite) 
{
	cout << invite << " : ";
	string f;
	getline(cin, f);
	while (!check_float(f)) {
		cout << "Wrong float. ";
		cout << invite << " : ";
		getline(cin, f);
	}
	return stof(f);
}

string get_sensor_id(string invite)
{
	cout << invite << " : ";
	string f;
	getline(cin, f);
	while (!check_sensor_id(f)) {
		cout << "Wrong sensor id. ";
		cout << invite << " : ";
		getline(cin, f);
	}
	return f;
}

string get_cleaner_id(string invite)
{
	cout << invite << " : ";
	string f;
	getline(cin, f);
	while (!check_cleaner_id(f)) {
		cout << "Wrong cleaner id. ";
		cout << invite << " : ";
		getline(cin, f);
	}
	return f;
}


