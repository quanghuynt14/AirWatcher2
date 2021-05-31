#include <mysql.h>
#include <iostream>
#include "Sensor.h"
#include "Cleaner.h"
#include "Attribute.h"
#include "Measurement.h"
#include "Service.h"

void Service::initDB()
{
	MYSQL* conn;

	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "root", "airwatcher2", 3306, NULL, 0);

	if (conn) {
		puts("Successful connection to database");

		Sensor s;
		s.loadCSV(conn);

		Cleaner c;
		c.loadCSV(conn);

		Attribute a;
		a.loadCSV(conn);
		
		Measurement m;
		m.loadCSV(conn);

	}
	else {
		puts(">< Connection to database has failed");

	}

	delete conn;
}
