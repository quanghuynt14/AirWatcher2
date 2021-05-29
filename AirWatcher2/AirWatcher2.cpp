#include <iostream>
#include "Sensor.h"
#include "Attribute.h"
#include "AgencyView.h"

int main()
{
	Sensor a = { "Sensor0", 2, 3 };
	Attribute attribute = { "O2", "mp3", "hehe" };
	a.print();
	a.input();
	attribute.print();

}


