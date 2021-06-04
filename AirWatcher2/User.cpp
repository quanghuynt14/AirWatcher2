#include "User.h"
#include "mysql_lib.h"

string User::getMail()
{
	return mail;
}

string User::getPassword()
{
	return pwd_hashed;
}

string User::getName()
{
	return name;
}

int User::auth(string tab, string mail, string pwd)
{
	MYSQL * conn = connect_database();

	string query = "SELECT * FROM ";
	query.append(tab);
	query.append(" WHERE mail = '" + mail + "' AND password = '" + pwd + "';");
	int qstate = mysql_query(conn, query.c_str());

	MYSQL_ROW row;
	MYSQL_RES * res;

	int id_auth = 0;

	if (!qstate) {
		res = mysql_store_result(conn);

		while (row = mysql_fetch_row(res)) {
			id_auth = stoi(row[0]);
		}
	}
	else {
		puts("Authentification failed !");
	}

	if (id_auth != 0) {
		cout << "You are connected." << endl << endl;
	}
	else {
		cout << "Wrong mail or password." << endl << endl;
	}
	return id_auth;
}
