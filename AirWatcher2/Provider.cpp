#include "Provider.h"
#include "mysql_lib.h"

void Provider::create()
{
	MYSQL * conn = connect_database();

	string query = "CREATE TABLE " + table_name + "(";
	query.append("		id			int PRIMARY KEY AUTO_INCREMENT,");
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

void Provider::insert(string mail, string pwd, string name, string cleaner_id)
{
	MYSQL * conn = connect_database();

	string query = "INSERT INTO " + table_name + "(mail, password, name, cleaner_id) VALUES('" + mail + "', '" + pwd + "', '" + name + "', '" + cleaner_id + "');";

	int qstate = mysql_query(conn, query.c_str());
	display_message_insert(conn, qstate, table_name);
}

