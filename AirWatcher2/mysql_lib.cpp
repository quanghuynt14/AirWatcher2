#include "mysql_lib.h"

void display_message_create(MYSQL * conn, int queryState, string tableName)
{
	if (!queryState) {
		cout << "MySQL : Successful create table " << tableName << " to database" << endl;
	}
	else {
		cout << "MySQL : " << mysql_error(conn) << endl;
	}
}

void display_message_drop(MYSQL * conn, int queryState, string tableName)
{
	if (!queryState) {
		cout << "MySQL : Successful drop table " << tableName << " to database" << endl;
	}
	else {
		cout << "MySQL : " << mysql_error(conn) << endl;
	}
}

void display_message_insert(MYSQL * conn, int queryState, string tableName)
{
	if (!queryState) {
		cout << "MySQL : Successful insert table " << tableName << " to database" << endl;
	}
	else {
		cout << "MySQL : " << mysql_error(conn) << endl;
	}
}

void display_message_loadCSV(MYSQL * conn, int queryState, string tableName)
{
	if (!queryState) {
		cout << "MySQL : Successful load file " << tableName << ".csv to table " << tableName << endl;
	}
	else {
		cout << "MySQL : " << mysql_error(conn) << endl;
	}
}

void display_message_query(MYSQL * conn, int queryState, string tableName)
{
	if (!queryState) {
		cout << "MySQL : Successful query table " << tableName << endl;
	}
	else {
		cout << "MySQL : " << mysql_error(conn) << endl;
	}
}

string get_current_directory() {
	char buf[256];
	GetCurrentDirectoryA(256, buf);

	string dir = buf;
	replace(dir.begin(), dir.end(), char(92), char(47));
	dir.append("/Data/");
	return dir;
}

MYSQL * connect_database()
{
	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "root", "airwatcher2", 3306, NULL, 0);

	return conn;
}
