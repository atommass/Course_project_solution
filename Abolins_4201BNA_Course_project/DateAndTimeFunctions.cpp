#include "Functions.h"
#include "DataTypes.h"
#include <iostream>
#include <sstream>

Flight::DateAndTime add_date_and_time()
{
	Flight::DateAndTime new_time; 
	// Date input
	std::cout << "Input date in format (YYYY / MM / DD)" << std::endl;
	std::cout << "Input flight year (YYYY): ";
	std::cin >> new_time.year;
	std::cin.ignore();
	std::cout << "Input flight month (MM): ";
	std::cin >> new_time.month;
	std::cout << "Input flight date (DD): ";
	std::cin >> new_time.day;
	// Time input
	std::cout << "Input time in format HH : MM" << std::endl;
	std::cout << "Input hour (HH): ";
	std::cin >> new_time.hour;
	std::cout << "Input min (MM): ";
	std::cin >> new_time.min;

	return new_time;
}