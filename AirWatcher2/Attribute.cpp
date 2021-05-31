#include "Attribute.h"

void Attribute::print()
{
	std::cout << id << " " << unit << " " << description << std::endl;
}

void Attribute::create(MYSQL * conn)
{
	int qstate = mysql_query(conn, "CREATE TABLE attributes(id VARCHAR(20) PRIMARY KEY, unit VARCHAR(20), description VARCHAR(50))");
	if (!qstate) {
		puts("Successful create table attributes to database !");
	}
	else {
		puts(">< Creating table attributes to database has failed !");
	}
}

void Attribute::drop(MYSQL * conn)
{
	int qstate = mysql_query(conn, "DROP TABLE IF EXISTS attributes");
	if (!qstate) {
		puts("Successful drop table attributes to database !");
	}
	else {
		puts(">< Dropping table attributes to database has failed !");
	}
}

void Attribute::insert(MYSQL * conn, std::string id, std::string unit, std::string description) {
	description = std::regex_replace(description, std::regex("'"), "\\'");
	std::string query = "INSERT INTO attributes(id, unit, description) VALUES('" + id + "', '" + unit + "', '" + description + "')";
	int qstate = mysql_query(conn, query.c_str());
	if (!qstate) {
		std::cout << "Successful insert into table attributes " << id << std::endl;
	}
	else {
		std::cout << ">< Inserting into table attributes " << id << " has failed !" << std::endl;
	}
}


void Attribute::loadCSV(MYSQL * conn)
{
	std::ifstream file;
	std::string id, uni, des;

	drop(conn);
	create(conn);

	file.open("Data/attributes.csv");
	std::string record;
	getline(file, record, '\n');
	while (getline(file, record, '\n'))
	{
		std::istringstream line(record);
		getline(line, id, ';');
		getline(line, uni, ';');
		getline(line, des, ';');

		insert(conn, id, uni, des);
	}
	file.close();
}