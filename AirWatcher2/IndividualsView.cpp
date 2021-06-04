#include <iostream>
#include "IndividualsView.h"
#include "AnalysisView.h"
#include "capture_user_input.h"

using namespace std;

int IndividualsView::authentification()
{
	cout << "Authentification private individual" << endl;

	string mail = get_mail("Enter mail");
	string password = get_password("Enter password");

	Individual a;
	return a.auth(a.table_name, mail, sha256(password));
}

void IndividualsView::printService()
{
	cout << "Service private individual" << endl;
	cout << "1> Air Quality Index in a circular area at a given moment" << endl;
	cout << "2> Air Quality Index in a circular area for time period" << endl;
	cout << "3> Air Quality Index at a precise geographical position at a given moment" << endl;
	cout << "4> My profile" << endl;
	cout << "0> Log Out" << endl;
}
void IndividualsView::printProfile(int uId)
{
	Individual ind;
	vector<string> info = ind.findInfoById(uId);

	cout << "Private individual profile" << endl;
	cout << "id        : " << info[0] << endl;
	cout << "id_str    : " << info[1] << endl;
	cout << "mail      : " << info[2] << endl;
	cout << "name      : " << info[4] << endl;
	cout << "point     : " << info[5] << endl;
	cout << "sensor_id : " << info[6] << endl;
	cout << endl;
}

void IndividualsView::servicePage(int ind_id)
{
	while (ind_id != 0) {
		printService();
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
			printProfile(ind_id);
			break;
		case 0:
			ind_id = 0;
			break;
		default:
			break;
		}
	}
}