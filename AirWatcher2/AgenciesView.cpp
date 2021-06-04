#include <iostream>
#include "AgenciesView.h"
#include "AnalysisView.h"
#include "capture_user_input.h"

using namespace std;

int AgenciesView::authentification()
{
	cout << "Authentification agency" << endl;

	string mail = get_mail("Enter mail");
	string password = get_password("Enter password");

	Agency a;
	return a.auth(a.table_name, mail, sha256(password));
}

void AgenciesView::printService(int uId)
{
	Agency a;
	cout << endl;
	cout << "Bonjour " << a.findName(uId) << endl << endl;
	cout << "Service agency" << endl;
	cout << "1> Air Quality Index in a circular area at a given moment" << endl;
	cout << "2> Air Quality Index in a circular area for time period" << endl;
	cout << "3> Top 9 sensors have the same data" << endl;
	cout << "4> Air Quality Index at a precise geographical position at a given moment" << endl;
	cout << "5> The impact of the cleaners on air quality" << endl;
	cout << "6> Analyze the data provided by a private individual sensor" << endl;
	cout << "0> Log Out" << endl;
}

void AgenciesView::servicePage(int agency_id)
{
	while (agency_id != 0) {
		printService(agency_id);
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
}