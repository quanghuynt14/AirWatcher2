#include <iostream>
#include "IndividualsView.h"
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
	vector<string> info = ind.findById(uId);

	cout << "id        : " << info[0] << endl;
	cout << "mail      : " << info[1] << endl;
	cout << "name      : " << info[3] << endl;
	cout << "point     : " << info[4] << endl;
	cout << "sensor_id : " << info[5] << endl;
}
