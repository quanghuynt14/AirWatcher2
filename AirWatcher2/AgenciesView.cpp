#include <iostream>
#include "AgenciesView.h"
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

void AgenciesView::printService()
{
	cout << "Service agency" << endl;
	cout << "1> Air Quality Index in a circular area at a given moment" << endl;
	cout << "2> Air Quality Index in a circular area for time period" << endl;
	cout << "3> Top 9 sensors have the same data" << endl;
	cout << "4> Air Quality Index at a precise geographical position at a given moment" << endl;
	cout << "5> The impact of the cleaners on air quality" << endl;
	cout << "6> Analyze the data provided by a private individual’s sensor" << endl;
	cout << "0> Log Out" << endl;
}