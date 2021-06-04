#include "Individual.h"
#include "mysql_lib.h"

void Individual::create()
{
	MYSQL * conn = connect_database();

	string query = "CREATE TABLE " + table_name + "(";
	query.append("		id			int PRIMARY KEY AUTO_INCREMENT,");
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

void Individual::insert(string mail, string pwd, string name, int point, string sensor_id)
{
	MYSQL * conn = connect_database();

	string query = "INSERT INTO " + table_name + "(mail, password, name, point, sensor_id) VALUES('" + mail + "', '" + pwd + "', '" + name + "', " + to_string(point) + ", '" + sensor_id + "');";

	int qstate = mysql_query(conn, query.c_str());
	display_message_insert(conn, qstate, table_name);
}

vector<string> Individual::findById(int id)
{
	MYSQL * conn = connect_database();

	string query = "SELECT * FROM " + table_name + " WHERE id = " + to_string(id) + ";";

	int qstate = mysql_query(conn, query.c_str());

	MYSQL_ROW row;
	MYSQL_RES * res;

	vector<string> info(5);

	if (!qstate) {
		res = mysql_store_result(conn);
		int no_row = 0;
		while (row = mysql_fetch_row(res)) {
			info[no_row++] = row[0];
			info[no_row++] = row[1];
			info[no_row++] = row[3];
			info[no_row++] = row[4];
			info[no_row++] = row[5];
		}
	}

	return info;
}

