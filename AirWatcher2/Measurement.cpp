#include "Measurement.h"

void Measurement::print()
{
	std::cout << date << " " << sensorId << " " << attributeId << " " << value << std::endl;
}

void Measurement::create(MYSQL * conn)
{
	std::string query = "CREATE TABLE measurements(date TIMESTAMP, sensorId VARCHAR(20), attributeId VARCHAR(20), value FLOAT";
	query.append(", FOREIGN KEY (sensorId) REFERENCES sensors(id)");
	query.append(", FOREIGN KEY (attributeId) REFERENCES attributes(id))");
	int qstate = mysql_query(conn, query.c_str());
	if (!qstate) {
		puts("Successful create table measurements to database !");
	}
	else {
		puts(">< Creating table measurements to database has failed !");
	}
}

void Measurement::drop(MYSQL * conn)
{
	int qstate = mysql_query(conn, "DROP TABLE IF EXISTS measurements");
	if (!qstate) {
		puts("Successful drop table measurements to database !");
	}
	else {
		puts(">< Dropping table measurements to database has failed !");
	}
}

void Measurement::insert(MYSQL * conn, std::string date, std::string sensorId, std::string attributeId, std::string value) {
	std::string query = "INSERT INTO measurements(date, sensorId, attributeId, value) VALUES('" + date + "', '" + sensorId + "', '" + attributeId + "', " + value + ")";
	int qstate = mysql_query(conn, query.c_str());
}


void Measurement::loadCSV(MYSQL * conn)
{
	std::cout << "Wait 10-15 mins for load 146000 lines csv..." << std::endl;
	std::ifstream file;
	std::string date, senId, attId, val;

	drop(conn);
	create(conn);

	file.open("Data/measurements.csv");
	std::string record;
	
	while (getline(file, record, '\n'))
	{
		std::istringstream line(record);
		getline(line, date, ';');
		getline(line, senId, ';');
		getline(line, attId, ';');
		getline(line, val, ';');

		insert(conn, date, senId, attId, val);
	}


	file.close();
}
