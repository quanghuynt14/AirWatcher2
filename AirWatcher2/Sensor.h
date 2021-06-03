#pragma once

#include <string>
#include <vector>
#include <mysql.h>

using namespace std;

struct Sensor
{
	const string table_name = "sensors";
	string id;
	float latitude;
	float longitude;

	void create();
	void drop();
	void insert(string id, string lat, string lon);
	void loadCSV();
	Sensor findById(string sensor_id);
	vector<string> findNearbySensors(float latitude, float longitude, float radius);
	vector<pair<float, int>> findDistanceSensorsTo1Point(float latitude, float longitude);
	string findClosestSensor(float latitude, float longitude);

};


