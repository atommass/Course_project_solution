#include "DataTypes.h"
#include "Functions.h"
#include <string>
#include <iostream>
#include <fstream>


int main()
{
	std::cout << "**********************************" << std::endl;
	std::cout << "  WELCOME TO AIRPORT MANAGEMENT!" << std::endl;
	std::cout << "**********************************" << std::endl;
	std::cout << std::endl;

	std::cout << "MAIN MENU: " << std::endl;
	std::cout << "	1. View data" << std::endl;
	std::cout << "	2. Add data" << std::endl;
	std::cout << "	3. Edit or Sort data" << std::endl;
	std::cout << "	4. Search data" << std::endl;
	std::cout << "	5. Filter data" << std::endl;
	std::cout << "	6. Delete data" << std::endl;

	viewFlightData();

	addFlightData();


	return 0;
}