#include "Cleaner.h"

void Cleaner::print()
{
	std::cout << id << " [" << latitude << ", " << longitude << "] ";
	std::cout << startWork << " ";
	std::cout << stopWork << std::endl;
}

void Cleaner::create(MYSQL * conn)
{
	int qstate = mysql_query(conn, "CREATE TABLE cleaners(id VARCHAR(20) PRIMARY KEY, latitude FLOAT, longitude FLOAT, start TIMESTAMP, stop TIMESTAMP)");
	if (!qstate) {
		puts("Successful create table cleaners to database !");
	}
	else {
		puts(">< Creating table cleaners to database has failed !");
	}
}

void Cleaner::drop(MYSQL * conn)
{
	int qstate = mysql_query(conn, "DROP TABLE IF EXISTS cleaners");
	if (!qstate) {
		puts("Successful drop table cleaners to database !");
	}
	else {
		puts(">< Dropping table cleaners to database has failed !");
	}
}

void Cleaner::insert(MYSQL * conn, std::string id, std::string latitude, std::string longitude, std::string start, std::string stop) {
	std::string query = "INSERT INTO cleaners(id, latitude, longitude, start, stop) VALUES('" + id + "', " + latitude + ", " + longitude + ", '" + start + "', '" + stop + "')";
	int qstate = mysql_query(conn, query.c_str());
	if (!qstate) {
		std::cout << "Successful insert into table cleaners " << id << std::endl;
	}
	else {
		std::cout << ">< Inserting into table cleaners " << id << " has failed !" << std::endl;
	}
}


void Cleaner::loadCSV(MYSQL * conn)
{
	std::ifstream file;
	std::string id, lat, lon, sta, sto;

	drop(conn);
	create(conn);

	file.open("Data/cleaners.csv");
	std::string record;

	while (getline(file, record, '\n'))
	{
		std::istringstream line(record);
		getline(line, id, ';');
		getline(line, lat, ';');
		getline(line, lon, ';');
		getline(line, sta, ';');
		getline(line, sto, ';');

		insert(conn, id, lat, lon, sta, sto);
	}
	file.close();
}
