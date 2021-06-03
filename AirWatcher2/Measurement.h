#pragma once

#include <string>
#include <vector>
#include <mysql.h>

using namespace std;

struct Measurement
{
	const string table_name = "measurements";

	void create();
	void drop();
	void insert(string date, string sensorId, string attributeId, string value);
	void loadCSV();

	vector<float> findAVGOneSensor(string date, string sensorId);

	vector<float> findAVGOneSensor(string dateBegin, string dateEnd, string sensorId);
	
	vector<vector<float>> findAVGAllSensor(string date);
	
	vector<vector<float>> findAVGAllSensor(string dateBegin, string dateEnd);
	
	vector<float> findValueOneSensorAllTime(string sensorId);
	
	vector<vector<float>> findMultiplyByOneSensor(string dateBegin, string dateEnd, string sensorId);
};

