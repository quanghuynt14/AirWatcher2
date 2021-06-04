#include <iostream>
#include "ProvidersView.h"
#include "AnalysisView.h"
#include "capture_user_input.h"

using namespace std;

int ProvidersView::authentification()
{
	cout << "Authentification provider" << endl;

	string mail = get_mail("Enter mail");
	string password = get_password("Enter password");

	Provider a;
	return a.auth(a.table_name, mail, sha256(password));
}

void ProvidersView::printService(int uId)
{
	Provider a;
	cout << endl;
	cout << "Bonjour " << a.findName(uId) << endl << endl;
	cout << "Service provider" << endl;
	cout << "1> Air Quality Index in a circular area at a given moment" << endl;
	cout << "2> Air Quality Index in a circular area for time period" << endl;
	cout << "3> Air Quality Index at a precise geographical position at a given moment" << endl;
	cout << "4> The impact of the cleaners on air quality" << endl;
	cout << "0> Log Out" << endl;
}

void ProvidersView::servicePage(int provider_id)
{
	while (provider_id != 0) {
		printService(provider_id);
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
			percentage_improvement(provider_id);
			break;
		case 0:
			provider_id = 0;
			break;
		default:
			break;
		}
	}
}