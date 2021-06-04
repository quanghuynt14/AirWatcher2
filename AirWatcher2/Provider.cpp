#include "Provider.h"
#include "mysql_lib.h"
#include "Provider.h"

void Provider::create()
{
	MYSQL * conn = connect_database();

	string query = "CREATE TABLE " + table_name + "(";
	query.append("		id			int PRIMARY KEY AUTO_INCREMENT,");
	query.append("		id_str		varchar(20) UNIQUE,");
	query.append("		mail		varchar(100) UNIQUE,");
	query.append("		password	varchar(500),");
	query.append("		name		varchar(50),");
	query.append("		cleaner_id	varchar(20) UNIQUE,");
	query.append(" FOREIGN KEY (cleaner_id) REFERENCES cleaners(id)");
	query.append(");");

	int qstate = mysql_query(conn, query.c_str());
	display_message_create(conn, qstate, table_name);
}

void Provider::drop()
{
	MYSQL * conn = connect_database();

	string query = "DROP TABLE IF EXISTS " + table_name + ";";

	int qstate = mysql_query(conn, query.c_str());
	display_message_drop(conn, qstate, table_name);
}

void Provider::insert(string id_str, string mail, string pwd, string name, string cleaner_id)
{
	MYSQL * conn = connect_database();

	string query = "INSERT INTO " + table_name + "(id_str, mail, password, name, cleaner_id) VALUES('" + id_str + "', '" + mail + "', '" + pwd + "', '" + name + "', '" + cleaner_id + "');";

	int qstate = mysql_query(conn, query.c_str());
	display_message_insert(conn, qstate, table_name);
}

string Provider::findCleanerByProvider(const int provider_id)
{
	MYSQL * conn = connect_database();

	string query = "SELECT cleaner_id FROM " + table_name + " WHERE id = " + to_string(provider_id) + ";";
	
	int qstate = mysql_query(conn, query.c_str());
	MYSQL_ROW row;
	MYSQL_RES * res;

	string cleaner_id;

	if (!qstate) {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			cleaner_id = row[0];
		}
	}

	return cleaner_id;
}

string Provider::findIdString(const int provider_id)
{
	MYSQL * conn = connect_database();

	string query = "SELECT id_str FROM " + table_name + " WHERE id = " + to_string(provider_id) + ";";

	int qstate = mysql_query(conn, query.c_str());
	MYSQL_ROW row;
	MYSQL_RES * res;

	string id_string;

	if (!qstate) {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			id_string = row[0];
		}
	}

	return id_string;
}

string Provider::findName(const int ind_id)
{
	MYSQL * conn = connect_database();

	string query = "SELECT name FROM " + table_name + " WHERE id = " + to_string(ind_id) + ";";

	int qstate = mysql_query(conn, query.c_str());
	MYSQL_ROW row;
	MYSQL_RES * res;

	string id_string;

	if (!qstate) {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			id_string = row[0];
		}
	}

	return id_string;
}

vector<int> Provider::findAllProvider()
{
	MYSQL * conn = connect_database();

	string query = "SELECT id FROM " + table_name + ";";

	int qstate = mysql_query(conn, query.c_str());
	MYSQL_ROW row;
	MYSQL_RES * res;

	vector<int> ids;

	if (!qstate) {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			ids.push_back(stoi(row[0]));
		}
	}

	return ids;
}

