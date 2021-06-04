#include "Service.h"

void Service::initDB()
{
	cout << "Service : Init DB" << endl;

	// Create models 
	Sensor sensor;
	Cleaner cleaner;
	Attribute attribute;
	Measurement measurement;

	// Drop tables
	measurement.drop();
	sensor.drop();
	cleaner.drop();
	attribute.drop();

	// Create tables
	sensor.create();
	cleaner.create();
	attribute.create();
	measurement.create();

	// Load files CSV
	sensor.loadCSV();
	cleaner.loadCSV();
	attribute.loadCSV();
	measurement.loadCSV();

}

ATMO_index Service::calculateAirQualityIndex(float latitude, float longitude, float radius, string date)
{
	cout << "Service : calculateAirQualityIndex area and date" << endl;

	ATMO_index result;

	Sensor s;
	vector<string> nearbySensors = s.findNearbySensors(latitude, longitude, radius);

	if (nearbySensors.size() == 0) {
		result.haveData = false;
	}
	else {
		result.haveData = true;
		vector<float> avgGaz(4);
		cout << "Service : List of sensors in the selected area :" << endl;

		for (string sensor_id : nearbySensors)
		{
			cout << sensor_id << endl;

			Measurement m;
			vector<float> avgGaz_oneSensor = m.findAVGOneSensor(date, sensor_id);

			for (int i = 0; i < avgGaz.size(); i++) {
				avgGaz[i] += avgGaz_oneSensor[i];
			}
		}

		for (int i = 0; i < 4; i++)
		{
			avgGaz[i] /= nearbySensors.size();
			//cout << avgGaz[i] << endl;
		}

		result.getATMO(avgGaz);
	}

	cout << endl;
	return result;
}

ATMO_index Service::calculateAirQualityIndex(float latitude, float longitude, float radius, string dateBegin, string dateEnd)
{
	cout << "Service : calculateAirQualityIndex area and period" << endl;

	ATMO_index result;

	Sensor s;
	vector<string> nearbySensors = s.findNearbySensors(latitude, longitude, radius);

	if (nearbySensors.size() == 0) {
		result.haveData = false;
	}
	else {
		result.haveData = true;
		vector<float> avgGaz(4);
		cout << "Service : List of sensors in the selected area :" << endl;

		for (string sensor_id : nearbySensors)
		{
			cout << sensor_id << endl;

			Measurement m;
			vector<float> avgGaz_oneSensor = m.findAVGOneSensor(dateBegin, dateEnd, sensor_id);

			for (int i = 0; i < avgGaz.size(); i++) {
				avgGaz[i] += avgGaz_oneSensor[i];
			}
		}

		for (int i = 0; i < 4; i++)
		{
			avgGaz[i] /= nearbySensors.size();
			//cout << avgGaz[i] << endl;
		}


		result.getATMO(avgGaz);
	}

	cout << endl;
	return result;
}

ATMO_index Service::calculateAirQualityIndex(float latitude, float longitude, string date)
{
	cout << "Service : calculateAirQualityIndex position and date" << endl;

	ATMO_index result;

	Sensor s;

	vector<pair<float, int>> distance = s.findDistanceSensorsTo1Point(latitude, longitude);
	float sum = 0;
	for (int i = 0; i < distance.size(); i++) {
		//cout << distance[i].first << " " << distance[i].second << endl;
		sum += distance[i].first;
	}
	//cout << sum << endl;
	float sum2 = 0;
	vector<float> percentage(100);
	for (int i = 0; i < percentage.size(); i++) {
		percentage[i] = 100 - (distance[i].first*distance[i].first*(float)2.8 / sum) * 100;
		//cout << distance[i].first << " " << percentage[i] << endl;
		if (percentage[i] > 0) sum2 += percentage[i];
	}
	//cout << sum2 << endl;
	float sum3 = 0;
	for (int i = 0; i < percentage.size(); i++) {
		if (percentage[i] > 0) {
			percentage[i] = (percentage[i] / sum2) * 100;
			//cout << percentage[i] << endl;
			sum3 += percentage[i];
		}
		else {
			percentage[i] = 0;
		}
	}
	//cout << sum3 << endl;

	result.haveData = true;
	Measurement m;
	vector<float> avgGaz(4);

	vector<vector<float>> vec = m.findAVGAllSensor(date);

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 4; j++) {
			avgGaz[j] += vec[i][j] * percentage[i] / 100;
		}
	}
	result.getATMO(avgGaz);

	cout << endl;
	return result;
}

ATMO_index Service::calculateAirQualityIndex(float latitude, float longitude, string dateBegin, string dateEnd)
{
	cout << "Service : calculateAirQualityIndex position and period" << endl;

	ATMO_index result;

	Sensor s;

	vector<pair<float, int>> distance = s.findDistanceSensorsTo1Point(latitude, longitude);
	float sum = 0;
	for (int i = 0; i < distance.size(); i++) {
		//cout << distance[i].first << " " << distance[i].second << endl;
		sum += distance[i].first;
	}
	//cout << sum << endl;
	float sum2 = 0;
	vector<float> percentage(100);
	for (int i = 0; i < percentage.size(); i++) {
		percentage[i] = 100 - (distance[i].first*distance[i].first*(float)2 / sum) * 100;
		//cout << distance[i].first << " " << percentage[i] << endl;
		if (percentage[i] > 0) sum2 += percentage[i];
	}
	//cout << sum2 << endl;
	float sum3 = 0;
	for (int i = 0; i < percentage.size(); i++) {
		if (percentage[i] > 0) {
			percentage[i] = (percentage[i] / sum2) * 100;
			//cout << percentage[i] << endl;
			sum3 += percentage[i];
		}
		else {
			percentage[i] = 0;
		}
	}
	//cout << sum3 << endl;

	result.haveData = true;
	Measurement m;
	vector<float> avgGaz(4);

	vector<vector<float>> vec = m.findAVGAllSensor(dateBegin, dateEnd);

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 4; j++) {
			avgGaz[j] += vec[i][j] * percentage[i] / 100;
		}
	}
	result.getATMO(avgGaz);

	cout << endl;
	return result;
}

vector<pair<float, int>> Service::similarSensor(string dateBegin, string dateEnd, string sensor_id)
{
	cout << "Service : similarSensor period and sensor_id" << endl;

	vector<pair<float, int>> result(100);

	Measurement m;

	vector<float> vec_selected = m.findAVGOneSensor(dateBegin, dateEnd, sensor_id);

	vector<vector<float>> vec = m.findAVGAllSensor(dateBegin, dateEnd);

	for (int i = 0; i < vec.size(); i++) {
		float sum_a2 = 0;
		float sum_b2 = 0;
		float multi = 0;

		for (int j = 0; j < 4; j++) {
			multi += vec[i][j] * vec_selected[j];
			sum_a2 += vec[i][j] * vec[i][j];
			sum_b2 += vec_selected[j] * vec_selected[j];
		}

		// Cosine similarity formula
		result[i] = make_pair((multi / (sqrt(sum_a2)*sqrt(sum_b2))) * 100, i);
	}

	sort(result.rbegin(), result.rend());

	cout << endl;
	return result;
}

vector<pair<float, float>> Service::improveCleaner(string cleaner_id)
{
	cout << "Service : improveCleaner cleaner_id" << endl;

	Cleaner cc;
	Cleaner c = cc.findById(cleaner_id);

	//cout << c.latitude << " " << c.longitude << " " << c.start << " " << c.stop << endl;

	ATMO_index avant = calculateAirQualityIndex(c.latitude, c.longitude, "2019-01-01 12:00:00", c.start);
	//cout << avant.atmoIndex << endl;

	ATMO_index pendant = calculateAirQualityIndex(c.latitude, c.longitude, c.start, c.stop);
	//cout << pendant.atmoIndex << endl;

	vector<pair<float, float>> res;
	if (avant.haveData && pendant.haveData) {
		float a = (float)avant.atmoIndex;
		float m = (float)pendant.atmoIndex;
		res.push_back(make_pair(a, m));
		for (int i = 0; i < 4; i++) {
			res.push_back(make_pair(avant.gaz[i].concentration, pendant.gaz[i].concentration));
		}
	}
	cout << endl;
	return res;
}

float Service::analyzeIndividualData(string sensor_id)
{
	cout << "Service : analyzeIndividualData sensor_id" << endl;
	//TODO : return vector all sensor of individual 
	//       for all of them

	Sensor ss;
	Sensor indivi = ss.findById(sensor_id);

	//cout << indivi.latitude << " " << indivi.longitude << endl;
	string nearestSensor_id = indivi.findClosestSensor(indivi.latitude, indivi.longitude);
	
	//cout << nearestSensor_id << endl;
	Measurement m;

	vector<float> gov = m.findValueOneSensorAllTime(nearestSensor_id);

	vector<float> ind = m.findValueOneSensorAllTime(sensor_id);


	float mul = 0;
	float a2 = 0;
	float b2 = 0;
	for (int i = 0; i < 4; i++) {
		mul += gov[i] * ind[i];
		a2 += gov[i] * gov[i];
		b2 += ind[i] * ind[i];
	}

	// Cosine similarity formula
	float res = (mul / (sqrt(a2)*sqrt(b2))) * 100;

	cout << endl;
	return res;
}

