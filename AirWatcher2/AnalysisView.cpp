#include <iomanip>
#include <chrono>

#include "AnalysisView.h"
#include "capture_user_input.h"
#include "Service.h"

void AQI_area_moment()
{
	Service service;
	cout << "The calculation Air Quality Index in a circular area and a given moment" << endl;
	float latitude = get_float("Enter latitude center");
	float longitude = get_float("Enter longitude center");
	float radius = get_float("Enter radius of the circle (in km)");
	string date = get_date("Enter moment");

	// Start measuring time
	auto begin = std::chrono::high_resolution_clock::now();

	ATMO_index AQI = service.calculateAirQualityIndex(latitude, longitude, radius, date);
	//ATMO_index AQI = service.calculateAirQualityIndex(44, 1, 100, "2019-01-01 12:00:00");

	// Stop measuring time and calculate the elapsed time
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

	if (AQI.haveData) {
		cout << "+------+----------------+-------------" << endl;
		cout << "|      | Concentration  | Level       " << endl;
		cout << "+------+----------------+-------------" << endl;
		cout << "| O3   | " << fixed << setprecision(4) << AQI.gaz[0].concentration << setw(10) << "| " << AQI.gaz[0].level << endl;
		cout << "| NO2  | " << fixed << setprecision(4) << AQI.gaz[1].concentration << setw(10) << "| " << AQI.gaz[1].level << endl;
		cout << "| SO2  | " << fixed << setprecision(4) << AQI.gaz[2].concentration << setw(10) << "| " << AQI.gaz[2].level << endl;
		cout << "| PM10 | " << fixed << setprecision(4) << AQI.gaz[3].concentration << setw(10) << "| " << AQI.gaz[3].level << endl;
		cout << "+------+----------------+-------------" << endl << endl;
		
		cout << "ATMO Index " << AQI.atmoIndex << " level " << AQI.level << endl;
	}
	else {
		cout << "No sensors are in the selected area." << endl;
	}
	printf("(%.3f sec)\n\n", elapsed.count() * 1e-9);

}

void AQI_area_period()
{
	Service service;
	cout << "The calculation Air Quality Index in a circular area and a time period" << endl;
	float latitude = get_float("Enter latitude center");
	float longitude = get_float("Enter longitude center");
	float radius = get_float("Enter radius of the circle (in km)");
	string startT = get_date("Enter start time");
	string endT = get_date("Enter end time");

	// Start measuring time
	auto begin = std::chrono::high_resolution_clock::now();

	ATMO_index AQI = service.calculateAirQualityIndex(latitude, longitude, radius, startT, endT);
	//ATMO_index AQI = service.calculateAirQualityIndex(44, 2, 200, "2019-01-01 12:00:00", "2019-12-31 12:00:00");

	// Stop measuring time and calculate the elapsed time
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

	if (AQI.haveData) {
		cout << "+------+----------------+-------------" << endl;
		cout << "|      | Concentration  | Level       " << endl;
		cout << "+------+----------------+-------------" << endl;
		cout << "| O3   | " << fixed << setprecision(4) << AQI.gaz[0].concentration << setw(10) << "| " << AQI.gaz[0].level << endl;
		cout << "| NO2  | " << fixed << setprecision(4) << AQI.gaz[1].concentration << setw(10) << "| " << AQI.gaz[1].level << endl;
		cout << "| SO2  | " << fixed << setprecision(4) << AQI.gaz[2].concentration << setw(10) << "| " << AQI.gaz[2].level << endl;
		cout << "| PM10 | " << fixed << setprecision(4) << AQI.gaz[3].concentration << setw(10) << "| " << AQI.gaz[3].level << endl;
		cout << "+------+----------------+-------------" << endl << endl;

		cout << "ATMO Index " << AQI.atmoIndex << " level " << AQI.level << endl;
	}
	else {
		cout << "No sensors are in the selected area." << endl;
	}
	printf("(%.3f sec)\n\n", elapsed.count() * 1e-9);
}

void AQI_position_moment()
{
	Service service;

	cout << "The calculation Air Quality Index at a precise geographical position in the territory at a given moment" << endl;
	float latitude = get_float("Enter latitude position");
	float longitude = get_float("Enter longitude position");
	string date = get_date("Enter moment");

	// Start measuring time
	auto begin = std::chrono::high_resolution_clock::now();

	ATMO_index AQI = service.calculateAirQualityIndex(latitude, longitude, date);
	//ATMO_index AQI = service.calculateAirQualityIndex(45, 2, "2019-03-02 12:00:00");

	// Stop measuring time and calculate the elapsed time
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

	if (AQI.haveData) {
		cout << "+------+----------------+-------------" << endl;
		cout << "|      | Concentration  | Level       " << endl;
		cout << "+------+----------------+-------------" << endl;
		cout << "| O3   | " << fixed << setprecision(4) << AQI.gaz[0].concentration << setw(10) << "| " << AQI.gaz[0].level << endl;
		cout << "| NO2  | " << fixed << setprecision(4) << AQI.gaz[1].concentration << setw(10) << "| " << AQI.gaz[1].level << endl;
		cout << "| SO2  | " << fixed << setprecision(4) << AQI.gaz[2].concentration << setw(10) << "| " << AQI.gaz[2].level << endl;
		cout << "| PM10 | " << fixed << setprecision(4) << AQI.gaz[3].concentration << setw(10) << "| " << AQI.gaz[3].level << endl;
		cout << "+------+----------------+-------------" << endl << endl;

		cout << "ATMO Index " << AQI.atmoIndex << " level " << AQI.level << endl;
	}
	else {
		cout << "ERROR" << endl;
	}
	printf("(%.3f sec)\n\n", elapsed.count() * 1e-9);
}

void top_9_similar()
{
	Service service;
	cout << "Top 9 sensor similar with the selected sensor and a time period" << endl;
	string senID = get_sensor_id("Enter sensor id");
	string startT = get_date("Enter start time");
	string endT = get_date("Enter end time");

	// Start measuring time
	auto begin = std::chrono::high_resolution_clock::now();

	vector<pair<float, int>> res = service.similarSensor(startT, endT, senID);
	//vector<pair<float, int>> res = service.similarSensor("2019-01-01 12:00:00", "2019-05-01 12:00:00", "Sensor9");

	// Stop measuring time and calculate the elapsed time
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

	cout << "+-----+------------+-------------+" << endl;
	cout << "|     | SensorId   | Similarity  |" << endl;
	cout << "+-----+------------+-------------+" << endl;
	for (int i = 1; i < 10; i++) {
		cout << "| " << i << "   | Sensor" << setw(3) << res[i].second << setw(4) << " | " << fixed << setprecision(2) << res[i].first << "%" << setw(7) << "|" << endl;
	}
	cout << "+-----+------------+-------------+" << endl;
	printf("(%.3f sec)\n\n", elapsed.count() * 1e-9);
}

void percentage_improvement()
{
	Service service;
	cout << "Level of improvement in air quality" << endl;
	string cleID = get_cleaner_id("Enter cleaner id");

	// Start measuring time
	auto begin = std::chrono::high_resolution_clock::now();

	vector<pair<float, float>> r = service.improveCleaner(cleID);

	// Stop measuring time and calculate the elapsed time
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

	cout << "+-------------+-------+--------+----------+" << endl;
	cout << "|             | Avant | Apres  | Improve  |" << endl;
	cout << "+-------------+-------+--------+----------+" << endl;
	cout << "| ATMO Index  | " << fixed << setprecision(0) << r[0].first << setw(7) << " | " << fixed << setprecision(0) << r[0].second << setw(8) << "| " << fixed << setprecision(2) << setw(5) << (r[0].first - r[0].second) / r[0].first * 100 << setw(2) << "%" << setw(3) << "|" << endl;
	cout << "| Concen O3   | " << fixed << setprecision(2) << r[1].first << setw(3) << " | " << fixed << setprecision(2) << r[1].second << setw(4) << "| " << setw(5) << (r[1].first - r[1].second) / r[1].first * 100 << setw(2) << "%" << setw(3) << "|" << endl;
	cout << "| Concen NO2  | " << fixed << setprecision(2) << r[2].first << setw(3) << " | " << fixed << setprecision(2) << r[2].second << setw(4) << "| " << setw(5) << (r[2].first - r[2].second) / r[2].first * 100 << setw(2) << "%" << setw(3) << "|" << endl;
	cout << "| Concen SO2  | " << fixed << setprecision(2) << r[3].first << setw(3) << " | " << fixed << setprecision(2) << r[3].second << setw(4) << "| " << setw(5) << (r[3].first - r[3].second) / r[3].first * 100 << setw(2) << "%" << setw(3) << "|" << endl;
	cout << "| Concen PM10 | " << fixed << setprecision(2) << r[4].first << setw(3) << " | " << fixed << setprecision(2) << r[4].second << setw(4) << "| " << setw(5) << (r[4].first - r[4].second) / r[4].first * 100 << setw(2) << "%" << setw(3) << "|" << endl;
	cout << "+-------------+-------+--------+----------+" << endl;

	printf("(%.3f sec)\n\n", elapsed.count() * 1e-9);
}

void analyze_individual_data()
{
	Service service;
	if (service.analyzeIndividualData("Sensor70") < 90) {
		cout << "Sensor70 dishonest" << endl;
	}
	else {
		cout << "Sensor70 honest" << endl;
	}
	if (service.analyzeIndividualData("Sensor36") < 90) {
		cout << "Sensor36 dishonest" << endl;
	}
	else {
		cout << "Sensor36 honest" << endl;
	}
}

