#pragma once

#include <string>
#include <regex>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

using namespace std;

bool check_format_date(const string);
bool check_time_period(const string);
bool check_float(const string);
bool check_sensor_id(const string);
bool check_cleaner_id(const string);
bool check_mail_validation(const string);

string get_date(const string);
float get_float(const string);
string get_sensor_id(const string);
string get_cleaner_id(const string);
string get_mail(const string);
string get_password(const string);
int get_choix(const string, int upTo);

string sha256(const string str);

