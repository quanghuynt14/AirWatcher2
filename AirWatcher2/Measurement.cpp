#include "Measurement.h"
#include "mysql_lib.h"

void Measurement::create()
{
	MYSQL * conn = connect_database();

	string query = "CREATE TABLE " + table_name + "(";
	query.append("		date			timestamp,");
	query.append("		sensor_id		varchar(20),");
	query.append("		attribute_id	varchar(20),");
	query.append("		value		float,");
	query.append(" FOREIGN KEY (sensor_id) REFERENCES sensors(id),");
	query.append(" FOREIGN KEY (attribute_id) REFERENCES attributes(id)");
	query.append(");");

	int qstate = mysql_query(conn, query.c_str());
	display_message_create(conn, qstate, table_name);
}

void Measurement::drop()
{
	MYSQL * conn = connect_database();

	string query = "DROP TABLE IF EXISTS " + table_name + ";";

	int qstate = mysql_query(conn, query.c_str());
	display_message_drop(conn, qstate, table_name);
}

void Measurement::insert(string date, string sensorId, string attributeId, string value) 
{
	MYSQL * conn = connect_database();

	string query = "INSERT INTO " + table_name + " VALUES('" + date + "', '" + sensorId + "', '" + attributeId + "', " + value + ")";
	
	int qstate = mysql_query(conn, query.c_str());
	display_message_insert(conn, qstate, table_name);
}


void Measurement::loadCSV()
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

vector<float> Measurement::findAVGOneSensor(string date, string sensorId)
{
	MYSQL * conn = connect_database();

	MYSQL_ROW row;
	MYSQL_RES * res;

	string query = "SELECT AVG(value) FROM measurements WHERE (date = '" + date + "') and sensor_id = '" + sensorId + "' group by attribute_id;";
	
	int qstate = mysql_query(conn, query.c_str());

	vector<float> avg(4);

	if (!qstate) {
		res = mysql_store_result(conn);
		int no_row = 0;
		while (row = mysql_fetch_row(res)) {
			avg[no_row++] = stof(row[0]);
		}
	}
	
	return avg;
}

// find avg(value) of know sensor, attribute and period
vector<float> Measurement::findAVGOneSensor(string dateBegin, string dateEnd, string sensorId)
{
	MYSQL * conn = connect_database();

	MYSQL_ROW row;
	MYSQL_RES * res;

	string query = "SELECT AVG(value) FROM measurements WHERE (date BETWEEN '" + dateBegin + "' and '" + dateEnd + "') and sensor_id = '" + sensorId + "' group by attribute_id;";
	
	int qstate = mysql_query(conn, query.c_str());
	//display_message_query(conn, qstate, table_name);

	vector<float> avg(4);

	if (!qstate) {
		res = mysql_store_result(conn);
		int no_row = 0;
		while (row = mysql_fetch_row(res)) {
			avg[no_row++] = stof(row[0]);
		}
	}

	return avg;
}

vector<vector<float>> Measurement::findAVGAllSensor(string date)
{
	MYSQL * conn = connect_database();

	MYSQL_ROW row;
	MYSQL_RES * res;

	string query = "SELECT sensor_id, AVG(value) FROM measurements WHERE (date = '" + date + "') group by sensor_id, attribute_id;";

	int qstate = mysql_query(conn, query.c_str());

	vector<vector<float>> avg(100, vector<float>(4));

	if (!qstate) {
		res = mysql_store_result(conn);
		//cout << res->row_count << endl;
		int no_row = 0;
		int no_att = 0;
		while (row = mysql_fetch_row(res)) {
			avg[no_row][no_att] = stof(row[1]);
			//cout << no_row << " " << no_att << endl;
			no_att++;
			if (no_att == 4) {
				no_row++;
				no_att = 0;
			}
		}
	}

	return avg;
}

vector<vector<float>> Measurement::findAVGAllSensor(string dateBegin, string dateEnd)
{
	MYSQL * conn = connect_database();

	MYSQL_ROW row;
	MYSQL_RES * res;

	string query = "SELECT sensor_id, AVG(value) FROM measurements WHERE (date BETWEEN '" + dateBegin + "' and '" + dateEnd + "') group by sensor_id, attribute_id;";

	int qstate = mysql_query(conn, query.c_str());

	vector<vector<float>> avg(100, vector<float>(4));

	if (!qstate) {
		res = mysql_store_result(conn);
		//cout << res->row_count << endl;
		int no_row = 0;
		int no_att = 0;
		while (row = mysql_fetch_row(res)) {
			avg[no_row][no_att] = stof(row[1]);
			//cout << no_row << " " << no_att << endl;
			no_att++;
			if (no_att == 4) {
				no_row++;
				no_att = 0;
			}
		}
	}

	return avg;
}

vector<float> Measurement::findValueOneSensorAllTime(string sensorId)
{
	MYSQL * conn = connect_database();

	MYSQL_ROW row;
	MYSQL_RES * res;

	string query = "SELECT value FROM measurements WHERE sensor_id = '" + sensorId + "';";

	int qstate = mysql_query(conn, query.c_str());
	//display_message_query(conn, qstate, table_name);

	vector<float> v;

	if (!qstate) {
		res = mysql_store_result(conn);
		
		while (row = mysql_fetch_row(res)) {
			v.push_back(stof(row[0]));
		}
	}

	return v;
}

vector<vector<float>> Measurement::findMultiplyByOneSensor(string dateBegin, string dateEnd, string sensorId)
{
	MYSQL * conn = connect_database();

	vector<float> avg_selected_sensor = findAVGOneSensor(dateBegin, dateEnd, sensorId);

	MYSQL_ROW row;
	MYSQL_RES * res;

	string query = "SELECT sensor_id, attribute_id, IF(attribute_id = 'O3', avg(value)*" + to_string(avg_selected_sensor[0]) + ",";
	query.append("		   IF(attribute_id = 'NO2',avg(value)*");
	query.append(to_string(avg_selected_sensor[1]));
	query.append(",		   IF(attribute_id='SO2',avg(value)*");
	query.append(to_string(avg_selected_sensor[2]));
	query.append(",		   avg(value)*");
	query.append(to_string(avg_selected_sensor[3]));
	query.append("))) FROM measurements ");
	query.append(" WHERE (date BETWEEN '" + dateBegin + "' and '" + dateEnd + "') ");
	query.append(" GROUP BY sensor_id, attribute_id; ");

	//cout << query << endl;
	int qstate = mysql_query(conn, query.c_str());

	vector<vector<float>> avg(100, vector<float> (4));

	if (!qstate) {
		res = mysql_store_result(conn);
		//cout << res->row_count << endl;
		int no_row = 0;
		int no_att = 0;
		while (row = mysql_fetch_row(res)) {
			//cout << row[0] << " " << row[1] << " " << row[2] << endl;
		
			avg[no_row][no_att] = stof(row[2]);
			//cout << no_row << " " << no_att << endl;
			no_att++;
			if (no_att == 4) {
				no_row++;
				no_att = 0;
			}
		}
	}

	return avg;
}
