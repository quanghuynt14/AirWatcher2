#include "Sensor.h"

void Sensor::print()
{
	std::cout << id << " [" << latitude << ", " << longitude << "]" << std::endl;
}

void Sensor::create(MYSQL * conn)
{
	int qstate = mysql_query(conn, "CREATE TABLE sensors(id VARCHAR(20) PRIMARY KEY, latitude FLOAT, longitude FLOAT)");
	if (!qstate) {
		puts("Successful create table sensors to database !");
	}
	else {
		puts(">< Creating table sensors to database has failed !");
	}
}

void Sensor::drop(MYSQL * conn)
{
	int qstate = mysql_query(conn, "DROP TABLE IF EXISTS sensors");
	if (!qstate) {
		puts("Successful drop table sensors to database !");
	}
	else {
		puts(">< Dropping table sensors to database has failed !");
	}
}

void Sensor::insert(MYSQL * conn, std::string id, std::string latitude, std::string longitude) {
	std::string query = "INSERT INTO sensors(id, latitude, longitude) VALUES('" + id + "', " + latitude + ", " + longitude + ") ";
	int qstate = mysql_query(conn, query.c_str());
	if (!qstate) {
		std::cout << "Successful insert into table sensors " << id << std::endl;
	}
	else {
		std::cout << ">< Inserting into table sensors " << id << " has failed !" << std::endl;
	}
}

void Sensor::loadCSV(MYSQL * conn)
{
	std::ifstream file;
	std::string id, lat, lon;

	drop(conn);
	create(conn);

	file.open("Data/sensors.csv");
	std::string record;

	while (getline(file, record, '\n'))
	{
		std::istringstream line(record);
		getline(line, id, ';');
		getline(line, lat, ';');
		getline(line, lon, ';');

		insert(conn, id, lat, lon);
	}
	file.close();
}
