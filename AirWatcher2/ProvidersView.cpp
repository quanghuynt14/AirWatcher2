#include <iostream>
#include "ProvidersView.h"
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

void ProvidersView::printService()
{
	cout << "Service provider" << endl;
	cout << "1> Air Quality Index in a circular area at a given moment" << endl;
	cout << "2> Air Quality Index in a circular area for time period" << endl;
	cout << "3> Air Quality Index at a precise geographical position at a given moment" << endl;
	cout << "4> The impact of the cleaners on air quality" << endl;
	cout << "0> Log Out" << endl;
}