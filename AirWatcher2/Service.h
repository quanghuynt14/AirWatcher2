#pragma once

#include <iostream>
#include "Sensor.h"
#include "Cleaner.h"
#include "Attribute.h"
#include "Measurement.h"
#include "ATMO_index.h"

using namespace std;

class Service
{
public:
	void initDB();

	// circular area and given moment
	ATMO_index calculateAirQualityIndex(float latitude, float longitude, float radius, string date);

	// circular area and period of time
	ATMO_index calculateAirQualityIndex(float latitude, float longitude, float radius, string dateBegin, string dateEnd);

	// position and given moment
	ATMO_index calculateAirQualityIndex(float latitude, float longitude, string date);

	// position and period of time
	ATMO_index calculateAirQualityIndex(float latitude, float longitude, string dateBegin, string dateEnd);

	vector<pair<float, int>> similarSensor(string dateBegin, string dateEnd, string sensor_id);

	vector<pair<float, float>> improveCleaner(string cleaner_id);

	float analyzeIndividualData(string sensor_id);

};

