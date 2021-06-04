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
	//setupDatabase();

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
			while (agency_id != 0) {
				agenciesView.printService();
				int choix2 = get_choix("Enter choix", 6);

				switch (choix2)
				{
				case 1:
					AQI_area_moment();
					break;
				case 2:
					AQI_area_period();
					break;
				case 3:
					top_9_similar();
					break;
				case 4:
					AQI_position_moment();
					break;
				case 5:
					percentage_improvement();
					break;
				case 6:
					analyze_individual_data();
					break;
				case 0:
					agency_id = 0;
					break;
				default:
					break;
				}
			}
			break;
		case 2:
			provider_id = providersView.authentification();
			while (provider_id != 0) {
				providersView.printService();
				int choix2 = get_choix("Enter choix", 4);

				switch (choix2)
				{
				case 1:
					AQI_area_moment();
					break;
				case 2:
					AQI_area_period();
					break;
				case 3:
					AQI_position_moment();
					break;
				case 4:
					percentage_improvement();
					break;
				case 0:
					provider_id = 0;
					break;
				default:
					break;
				}
			}
			break;
		case 3:
			individual_id = individualsView.authentification();
			while (individual_id != 0) {
				int choix2 = get_choix("Enter choix", 4);

				switch (choix2)
				{
				case 1:
					AQI_area_moment();
					break;
				case 2:
					AQI_area_period();
					break;
				case 3:
					AQI_position_moment();
					break;
				case 4:
					individualsView.printProfile(individual_id);
					break;
				case 0:
					individual_id = 0;
					break;
				default:
					break;
				}
			}
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

	//Agency a;
	//a.drop();
	//a.create();
	//a.insert("obama@gov.us", sha256("obama123"), "Barack Obama");
	//a.insert("trump@gov.us", sha256("trump123"), "Donald Trump");
	//a.insert("macron@gouv.fr", sha256("macron123"), "Emmanuel Macron");
	//a.insert("queen@gov.uk", sha256("queen123"), "Queen Elizabeth II");

	//int agency_id = 0;

	//AgenciesView agenciesView;
	//agency_id = agenciesView.authentification();

	//cout << agency_id << endl;

	//Provider p;
	//p.drop();
	//p.create();
	//p.insert("edf@pro.air", sha256("edf123"), "EDF", "Cleaner0");
	//p.insert("engie@pro.air", sha256("engie123"), "Engie", "Cleaner1");
	
	//int provider_id = 0;

	//ProvidersView providersView;
	//provider_id = providersView.authentification();

	//cout << provider_id << endl;

	/*Individual ind;
	ind.drop();
	ind.create();
	ind.insert("huy@user.air", sha256("huy123"), "Huy", 0, "Sensor70");
	ind.insert("dat@user.air", sha256("dat123"), "Dat", 0, "Sensor36");

	int individual_id = 0;

	IndividualsView individualsView;
	individual_id = individualsView.authentification();

	cout << individual_id << endl;*/
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