#include "capture_user_input.h"
#include <conio.h>

string sha256(const string str)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}
	return ss.str();
}


bool check_format_date(const string date) 
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

bool check_time_period(const string date) 
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

bool check_float(const string num) 
{
	regex regLine(R"([-|+]?([0-9]*\.[0-9]+|[0-9]+)$)");

	if (regex_match(num, regLine)) {
		return true;
	}
	else {
		return false;
	}
}

bool check_sensor_id(const string s) 
{
	regex regLine(R"(Sensor([1-9]|[1-9][0-9])$)");

	if (regex_match(s, regLine)) {
		return true;
	}
	else {
		return false;
	}
}

bool check_cleaner_id(const string s)
{
	regex regLine(R"(Cleaner[0-1]$)");

	if (regex_match(s, regLine)) {
		return true;
	}
	else {
		return false;
	}
}

bool check_mail_validation(const string s)
{
	regex regLine(R"([_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4})$)");

	if (regex_match(s, regLine)) {
		return true;
	}
	else {
		return false;
	}
}

bool check_choix(const string s, const int upTo)
{
	regex regLine(R"([0-9]$)");

	if (regex_match(s, regLine)) {
		int h = stoi(s);
		if (h >= 0 && h <= upTo) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

string get_date(const string invite) 
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

float get_float(const string invite)
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

string get_sensor_id(const string invite)
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

string get_cleaner_id(const string invite)
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

string get_mail(const string invite)
{
	cout << invite << " : ";
	string f;
	getline(cin, f);
	while (!check_mail_validation(f)) {
		cout << "Wrong mail format. ";
		cout << invite << " : ";
		getline(cin, f);
	}
	return f;
}

string get_password(const string invite)
{
	cout << invite << " : ";

	string pass = "";

	char ch;

	ch = _getch();
	while (ch != 13) {//character 13 is enter
		pass.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	cout << endl;

	return pass;
}

int get_choix(const string invite, int upTo)
{
	cout << invite << " : ";
	string f;
	getline(cin, f);
	while (!check_choix(f, upTo)) {
		cout << "Wrong choix format. ";
		cout << invite << " : ";
		getline(cin, f);
	}
	return stoi(f);
}



