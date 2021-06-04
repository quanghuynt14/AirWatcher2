#include "Individual.h"
#include "mysql_lib.h"

void Individual::create()
{
	MYSQL * conn = connect_database();

	string query = "CREATE TABLE " + table_name + "(";
	query.append("		id			int PRIMARY KEY AUTO_INCREMENT,");
	query.append("		id_str		varchar(20) UNIQUE,");
	query.append("		mail		varchar(100) UNIQUE,");
	query.append("		password	varchar(500),");
	query.append("		name		varchar(50),");
	query.append("		point		int,");
	query.append("		sensor_id	varchar(20),");
	query.append(" FOREIGN KEY (sensor_id) REFERENCES sensors(id)");
	query.append(");");

	int qstate = mysql_query(conn, query.c_str());
	display_message_create(conn, qstate, table_name);
}

void Individual::drop()
{
	MYSQL * conn = connect_database();

	string query = "DROP TABLE IF EXISTS " + table_name + ";";

	int qstate = mysql_query(conn, query.c_str());
	display_message_drop(conn, qstate, table_name);
}

void Individual::insert(string id_str, string mail, string pwd, string name, int point, string sensor_id)
{
	MYSQL * conn = connect_database();

	string query = "INSERT INTO " + table_name + "(id_str, mail, password, name, point, sensor_id) VALUES('" + id_str + "','" + mail + "', '" + pwd + "', '" + name + "', " + to_string(point) + ", '" + sensor_id + "');";

	int qstate = mysql_query(conn, query.c_str());
	display_message_insert(conn, qstate, table_name);
}

vector<string> Individual::findInfoById(const int ind_id)
{
	MYSQL * conn = connect_database();

	string query = "SELECT * FROM " + table_name + " WHERE id = " + to_string(ind_id) + ";";

	int qstate = mysql_query(conn, query.c_str());

	MYSQL_ROW row;
	MYSQL_RES * res;

	vector<string> info(7);

	if (!qstate) {
		res = mysql_store_result(conn);
		int no_row = 0;
		while (row = mysql_fetch_row(res)) {
			info[no_row++] = row[0];
			info[no_row++] = row[1];
			info[no_row++] = row[2];
			info[no_row++] = row[3];
			info[no_row++] = row[4];
			info[no_row++] = row[5];
			info[no_row++] = row[6];
		}
	}

	return info;
}

string Individual::findIdString(const int ind_id)
{
	MYSQL * conn = connect_database();

	string query = "SELECT id_str FROM " + table_name + " WHERE id = " + to_string(ind_id) + ";";

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

string Individual::findName(const int ind_id)
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

string Individual::findSensor(const int ind_id)
{
	MYSQL * conn = connect_database();

	string query = "SELECT sensor_id FROM " + table_name + " WHERE id = " + to_string(ind_id) + ";";

	int qstate = mysql_query(conn, query.c_str());
	MYSQL_ROW row;
	MYSQL_RES * res;

	string sensor_id;

	if (!qstate) {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			sensor_id = row[0];
		}
	}

	return sensor_id;
}

vector<int> Individual::findAllIndividual()
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


