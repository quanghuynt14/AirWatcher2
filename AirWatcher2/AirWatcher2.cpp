#include <iostream>
#include <string>
#include <chrono>
#include <openssl/sha.h>

#include "capture_user_input.h"
#include "Service.h"

#include "AnalysisView.h"
#include "AgenciesView.h"
#include "ProvidersView.h"
#include "IndividualsView.h"

#include "Agency.h"
#include "Provider.h"
#include "Individual.h"

using namespace std;

void setupDatabase();
void printHome();

int main()
{
	setupDatabase();

	AgenciesView agenciesView;
	ProvidersView providersView;
	IndividualsView individualsView;

	int agency_id = 0;
	int provider_id = 0;
	int individual_id = 0;

	bool ok = true;

	while (ok) {
		printHome();
		int choix = get_choix("Enter choix", 3);

		switch (choix)
		{
		case 1:
			agency_id = agenciesView.authentification();
			agenciesView.servicePage(agency_id);
			break;
		case 2:
			provider_id = providersView.authentification();
			providersView.servicePage(provider_id);
			break;
		case 3:
			individual_id = individualsView.authentification();
			individualsView.servicePage(individual_id);
			break;
		case 0:
			ok = false;
			break;
		default:
			break;
		}
	}
	

	//AQI_area_moment();
	
	//AQI_area_period();

	//top_9_similar();

	//AQI_position_moment();

	//percentage_improvement();

	//analyze_individual_data();

	
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

void printHome()
{
	cout << "Welcome to AirWatcher2 Application" << endl;
	cout << "1> Agency" << endl;
	cout << "2> Provider" << endl;
	cout << "3> User" << endl;
	cout << "0> Exit" << endl;
}