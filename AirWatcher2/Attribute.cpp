#include "Attribute.h"
#include "mysql_lib.h"

void Attribute::create()
{
	MYSQL * conn = connect_database();

	string query = "CREATE TABLE " + table_name + "(";
	query.append("		id			varchar(20) PRIMARY KEY,");
	query.append("		unit		varchar(20),");
	query.append("		description	varchar(50)");
	query.append(");");

	int qstate = mysql_query(conn, query.c_str());
	display_message_create(conn, qstate, table_name);
}

void Attribute::drop()
{
	MYSQL * conn = connect_database();

	string query = "DROP TABLE IF EXISTS " + table_name + ";";

	int qstate = mysql_query(conn, query.c_str());
	display_message_drop(conn, qstate, table_name);
}

void Attribute::insert(string id, string unit, string des) 
{
	MYSQL * conn = connect_database();

	des = regex_replace(des, regex("'"), "\\'");
	string query = "INSERT INTO " + table_name + " VALUES('" + id + "', '" + unit + "', '" + des + "')";
	
	int qstate = mysql_query(conn, query.c_str());
	display_message_insert(conn, qstate, table_name);
}


void Attribute::loadCSV()
{
	MYSQL * conn = connect_database();

	ifstream file;
	string id, uni, des;

	file.open("Data/attributes.csv");
	string record;
	getline(file, record, '\n');
	while (getline(file, record, '\n'))
	{
		istringstream line(record);
		getline(line, id, ';');
		getline(line, uni, ';');
		getline(line, des, ';');

		insert(id, uni, des);
	}
	file.close();
}