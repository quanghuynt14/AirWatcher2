#include "ATMO_index.h"
#include <iostream>

void ATMO_index::getATMO(vector<float> concenGaz)
{
	const string levels[11] = { "",
							   "\033[38;2;0;0;0;48;2;0;204;0mGood\033[0m", 
							   "\033[38;2;0;0;0;48;2;0;204;0mGood\033[0m",
							   "\033[38;2;0;0;0;48;2;102;204;0mSatisfactory\033[0m", 
							   "\033[38;2;0;0;0;48;2;102;204;0mSatisfactory\033[0m",
							   "\033[38;2;0;0;0;48;2;255;255;0mModerately polluted\033[0m",
							   "\033[38;2;0;0;0;48;2;255;153;0mPoor\033[0m", 
							   "\033[38;2;0;0;0;48;2;255;153;0mPoor\033[0m",
							   "\033[38;2;0;0;0;48;2;255;0;0mVery poor\033[0m", 
							   "\033[38;2;0;0;0;48;2;255;0;0mVery poor\033[0m",
							   "\033[38;2;0;0;0;48;2;165;42;42mSevere\033[0m" };
	// Calcul ATMO index
	vector<int> gazIndex = { 1, 1, 1, 1 };

	const int tab[4][9] = { { 29, 54,  79, 104, 129, 149, 179, 209, 239 },    //O3
							{ 29, 54,  84, 109, 134, 164, 199, 274, 399 },    //SO2
							{ 39, 79, 119, 159, 199, 249, 299, 399, 499 },    //NO2
							{  6, 13,  20,  27,  34,  41,  49,  64,  79 } };  //PM10

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 4; j++) {
			if (concenGaz[j] > tab[j][i]) gazIndex[j]++;
		}
	}

	gaz = vector<gazInfo>(4);
	for (int i = 0; i < 4; i++) {
		gaz[i].concentration = concenGaz[i];
		gaz[i].level = levels[gazIndex[i]];
	}

	atmoIndex = *max_element(gazIndex.begin(), gazIndex.end());
	level = levels[atmoIndex];
}
