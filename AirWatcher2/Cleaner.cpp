#include "Cleaner.h"
#include "mysql_lib.h"

void Cleaner::create()
{
	MYSQL * conn = connect_database();

	string query = "CREATE TABLE " + table_name + "(";
	query.append("		id			varchar(20) PRIMARY KEY,");
	query.append("		latitude	float,");
	query.append("		longitude	float,");
	query.append("		start		timestamp,");
	query.append("		stop		timestamp");
	query.append(");");

	int qstate = mysql_query(conn, query.c_str());
	display_message_create(conn, qstate, table_name);
}

void Cleaner::drop()
{
	MYSQL * conn = connect_database();

	string query = "DROP TABLE IF EXISTS " + table_name + ";";

	int qstate = mysql_query(conn, query.c_str());
	display_message_drop(conn, qstate, table_name);
}

void Cleaner::insert(string id, string lat, string lon, string start, string stop) 
{
	MYSQL * conn = connect_database();

	string query = "INSERT INTO " + table_name + " VALUES('" + id + "', " + lat + ", " + lon + ", '" + start + "', '" + stop + "');";

	int qstate = mysql_query(conn, query.c_str());
	display_message_insert(conn, qstate, table_name);
}


void Cleaner::loadCSV()
{
	MYSQL * conn = connect_database();

	string query = "LOAD DATA INFILE '";
	query.append(get_current_directory());
	query.append(table_name);
	query.append(".csv'");
	query.append("INTO TABLE ");
	query.append(table_name);
	query.append(" FIELDS TERMINATED BY ';';");

	int qstate = mysql_query(conn, query.c_str());
	display_message_loadCSV(conn, qstate, table_name);
}

Cleaner Cleaner::findById(string cleaner_id)
{
	MYSQL * conn = connect_database();

	string query = "SELECT * FROM ";
	query.append(table_name);
	query.append(" WHERE id = '" + cleaner_id + "';");
	int qstate = mysql_query(conn, query.c_str());

	MYSQL_ROW row;
	MYSQL_RES * res;

	Cleaner c;
	if (!qstate) {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			c.id = row[0];
			c.latitude = stof(row[1]);
			c.longitude = stof(row[2]);
			c.start = row[3];
			c.stop = row[4];
			//cout << row[0] << " " << row[1] << " " << row[2] << " " << row[3] << " " << row[4] << endl;
		}
	}
	else {
		puts("Query failed !");
	}

	return c;
}
