#include "Cleaner.h"

void Cleaner::print()
{
	std::cout << id << " ";
	position.print();
	std::cout << startWork << " ";
	std::cout << finishWork << std::endl;

}
