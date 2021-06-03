#pragma once

#include <string>
#include <regex>
#include <iostream>

using namespace std;

bool check_format_date(string);
bool check_time_period(string);
bool check_float(string);
bool check_sensor_id(string);
bool check_cleaner_id(string);

string get_date(string);
float get_float(string);
string get_sensor_id(string);
string get_cleaner_id(string);


