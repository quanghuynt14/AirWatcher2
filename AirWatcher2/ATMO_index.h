#pragma once

#include <vector>
#include <algorithm>

using namespace std;

struct gazInfo {
	float concentration;
	string level;
};

struct ATMO_index {
	bool haveData;
	int atmoIndex;
	string level;
	vector<gazInfo> gaz;

	void getATMO(vector<float>);
};

