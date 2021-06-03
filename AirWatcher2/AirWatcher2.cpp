#include <iostream>
#include <string>
#include <chrono>

#include "capture_user_input.h"
#include "Service.h"
#include "AnalysisView.h"

using namespace std;

void setupDatabase();

int main()
{
	//setupDatabase();

	
	//AQI_area_moment();
	
	//AQI_area_period();


	//top_9_similar();

	//AQI_position_moment();


	//percentage_improvement();

	analyze_individual_data();
	return 0;
}

void setupDatabase()
{
	// Start measuring time
	auto begin = std::chrono::high_resolution_clock::now();

	Service service;
	service.initDB();

	// Stop measuring time and calculate the elapsed time
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	printf("(%.3f sec)\n\n", elapsed.count() * 1e-9);
}