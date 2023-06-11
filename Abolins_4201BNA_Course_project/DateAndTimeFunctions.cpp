
#include "Flight_Functions.h"
#include "DataTypes.h"
#include <iomanip>
#include <iostream>
#include <sstream>

Flight::DateAndTime add_date_and_time()
{
	Flight::DateAndTime new_time; 

	std::cout << "Input date in format (YYYY / MM / DD)" << std::endl;

	// ----- Year input -----
	std::cout << "Input flight year (YYYY): ";
	while (!(std::cin >> new_time.year) || new_time.year < 0 || std::to_string(new_time.year).length() != 4)
	{
		std::cerr << "Invalid year. Please enter a non-negative four-digit value." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::cin.ignore();

	// ----- Month input -----
	std::cout << "Input flight month (MM): ";
	while (!(std::cin >> new_time.month) || new_time.month < 1 || new_time.month > 12)
	{
		std::cerr << "Invalid month. Please enter a valid value (1-12)." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	// ----- Day input -----
	std::cout << "Input flight date (DD): ";
	while (!(std::cin >> new_time.day) || new_time.day < 1 || new_time.day > 31)
	{
		std::cerr << "Invalid day. Please enter a valid value (1-31)." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

																																			// Validate day amount based on the input month
	if ((new_time.month == 4 || new_time.month == 6 || new_time.month == 9 || new_time.month == 11) && new_time.day > 30)
	{
		std::cerr << "Invalid day. The selected month has only 30 days." << std::endl;
		return add_date_and_time();																											// Prompt for date input again
	}

	if (new_time.month == 2)
	{
		const bool is_leap_year = (new_time.year % 4 == 0 && new_time.year % 100 != 0) || (new_time.year % 400 == 0);
		if ((is_leap_year && new_time.day > 29) || (!is_leap_year && new_time.day > 28))
		{
			std::cerr << "Invalid day. February has " << (is_leap_year ? "29" : "28") << " days in the selected year." << std::endl;
			return add_date_and_time();																										// Prompt for date input again
		}
	}

	std::cout << std::endl;
	

	std::cout << "Input time in format HH : MM" << std::endl;

	// ----- Hour input -----
	std::cout << "Input hour (HH): ";
	while (!(std::cin >> new_time.hour) || new_time.hour < 0 || new_time.hour > 23)
	{
		std::cerr << "Invalid hour. Please enter a valid value (0-23)." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	// ----- Minute input -----
	std::cout << "Input min (MM): ";
	while (!(std::cin >> new_time.min) || new_time.min < 0 || new_time.min > 59)
	{
		std::cerr << "Invalid minute. Please enter a valid value (0-59)." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return new_time;
}