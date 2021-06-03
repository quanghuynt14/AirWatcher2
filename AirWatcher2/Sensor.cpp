#include "Sensor.h"
#include "mysql_lib.h"

void Sensor::create()
{
	MYSQL * conn = connect_database();

	string query = "CREATE TABLE " + table_name + "(";
	query.append("		id			varchar(20) PRIMARY KEY,");
	query.append("		latitude	float,");
	query.append("		longitude	float");
	query.append(");");

	int qstate = mysql_query(conn, query.c_str());
	display_message_create(conn, qstate, table_name);
}

void Sensor::drop()
{
	MYSQL * conn = connect_database();

	string query = "DROP TABLE IF EXISTS " + table_name + ";";

	int qstate = mysql_query(conn, query.c_str());
	display_message_drop(conn, qstate, table_name);
}

void Sensor::insert(string id, string lat, string lon) 
{
	MYSQL * conn = connect_database();

	string query = "INSERT INTO " + table_name + " VALUES('" + id + "', " + lat + ", " + lon + ");";

	int qstate = mysql_query(conn, query.c_str());
	display_message_insert(conn, qstate, table_name);
}

void Sensor::loadCSV()
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

Sensor Sensor::findById(string sensor_id)
{
	MYSQL * conn = connect_database();

	string query = "SELECT * FROM ";
	query.append(table_name);
	query.append(" WHERE id = '" + sensor_id + "';");
	int qstate = mysql_query(conn, query.c_str());

	MYSQL_ROW row;
	MYSQL_RES * res;

	Sensor c;
	if (!qstate) {
		res = mysql_store_result(conn);
		//cout << res->row_count << endl;
		while (row = mysql_fetch_row(res)) {
			c.id = row[0];
			c.latitude = stof(row[1]);
			c.longitude = stof(row[2]);
		}
	}
	else {
		puts("Query failed !");
	}

	return c;
}

// radius in km
// distance in km
vector<string> Sensor::findNearbySensors(float latitude, float longitude, float radius)
{
	MYSQL * conn = connect_database();

	MYSQL_ROW row;
	MYSQL_RES * res;

	vector<string> sensorIDs;

	// Formula to calculate distance (in km) between two coordinates A, B
	// distance = 6371*acos( cos(radians(A.latitude)) * cos(radians(B.latitude)) * cos(radians(B.longitude) - radians(A.longitude)) + sin(radians(A.latitude)) * sin(radians(B.latitude)));
	string query = "SELECT id, (6371*acos(cos(radians(" + to_string(latitude) + "))*cos(radians(latitude))*cos(radians(longitude)-radians(" + to_string(longitude) + "))+sin(radians(" + to_string(latitude) + "))*sin(radians(latitude)))) as distance FROM sensors HAVING distance < "+ to_string(radius) + ";";

	int qstate = mysql_query(conn, query.c_str());
	if (!qstate) {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			sensorIDs.push_back(row[0]);
		}
	}
	else {
		puts("Query failed !");
	}

	return sensorIDs;
}

// distance in km
vector<pair<float, int>> Sensor::findDistanceSensorsTo1Point(float latitude, float longitude)
{
	MYSQL * conn = connect_database();

	MYSQL_ROW row;
	MYSQL_RES * res;

	vector<pair<float, int>> dis(100);

	// Formula to calculate distance (in km) between two coordinates A, B
	// distance = 6371*acos( cos(radians(A.latitude)) * cos(radians(B.latitude)) * cos(radians(B.longitude) - radians(A.longitude)) + sin(radians(A.latitude)) * sin(radians(B.latitude)));
	string query = "SELECT id, (6371*acos(cos(radians(" + to_string(latitude) + "))*cos(radians(latitude))*cos(radians(longitude)-radians(" + to_string(longitude) + "))+sin(radians(" + to_string(latitude) + "))*sin(radians(latitude)))) as distance FROM sensors;";

	int qstate = mysql_query(conn, query.c_str());
	if (!qstate) {
		res = mysql_store_result(conn);
		int no_row = 0;
		while (row = mysql_fetch_row(res)) {
			dis[no_row++] = make_pair(stof(row[1]), no_row);
		}
	}
	else {
		puts("Query failed !");
	}

	return dis;
}

string Sensor::findClosestSensor(float latitude, float longitude)
{
	MYSQL * conn = connect_database();

	MYSQL_ROW row;
	MYSQL_RES * res;

	string nearest_sensor;

	// Formula to calculate distance (in km) between two coordinates A, B
	// distance = 6371*acos( cos(radians(A.latitude)) * cos(radians(B.latitude)) * cos(radians(B.longitude) - radians(A.longitude)) + sin(radians(A.latitude)) * sin(radians(B.latitude)));
	string query = "SELECT id, (6371*acos(cos(radians(" + to_string(latitude) + "))*cos(radians(latitude))*cos(radians(longitude)-radians(" + to_string(longitude) + "))+sin(radians(" + to_string(latitude) + "))*sin(radians(latitude)))) as distance FROM sensors ORDER BY distance;";

	int qstate = mysql_query(conn, query.c_str());
	if (!qstate) {
		res = mysql_store_result(conn);
		//cout << res->row_count << endl;
		int no_row = 0;
		while (row = mysql_fetch_row(res)) {
			//cout << row[0] << " " << row[1] << endl;
			nearest_sensor = row[0];
			if (no_row == 1) break;
			no_row++;
		}
	}
	else {
		puts("Query failed !");
	}

	return nearest_sensor;
}