#pragma once
#include <algorithm>
#include <string>
#include <iostream>
#include <mysql.h>


using namespace std;

void display_message_create(MYSQL *, int, string);

void display_message_drop(MYSQL *, int, string);

void display_message_insert(MYSQL *, int, string);

void display_message_loadCSV(MYSQL *, int, string);

void display_message_query(MYSQL *, int, string);

string get_current_directory();

MYSQL * connect_database();