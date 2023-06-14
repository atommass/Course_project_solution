#include "Flight_Functions.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

#include <cstdlib> // to use system("cls"), std::rename(), std::remove();
#include <mutex> // mutual exclusion to prevent multiple threads from accessing shared resources at the same time


// view Flight data
constexpr int MAX_FLIGHTS = 100;
int numFlights = 0;

std::mutex console_mutex;
void clear_console()
{
	std::cout << "Press ENTER to continue..." << std::endl;

	if (std::cin.get() == '\n')
	{
		console_mutex.lock();
		system("cls");
		console_mutex.unlock();
	}

}

void readFlightDataFromFile(Flight flights[], int& numFlights)
{
	std::ifstream flight_data("flight_info_data.txt");
	if (!flight_data)
	{
		std::cerr << "Failed to open the file!" << std::endl;
		return;
	}
	std::string line;

	numFlights = 0;

	while (std::getline(flight_data, line) && numFlights < MAX_FLIGHTS)
	{
		std::istringstream iss(line);
		Flight flight;

		iss >> flight.flight_number >> flight.direction;

		std::string dateString, timeString;
		iss >> dateString >> timeString;

		std::istringstream dateStream(dateString);
		char delimiter;
		dateStream >> flight.time.year >> delimiter >> flight.time.month >> delimiter >> flight.time.day;

		std::istringstream timeStream(timeString);
		timeStream >> flight.time.hour >> delimiter >> flight.time.min;

		iss >> flight.destination;

		std::getline(iss, flight.plane_model);

		flights[numFlights] = flight;
		numFlights++;
	}

	flight_data.close();
}

void viewFlightData()
{
	Flight* existing_flights = new Flight[MAX_FLIGHTS];

	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(10) << "Flight no." << std::setw(12) << "Arr / Dep" << std::setw(15) << "Date" << std::setw(28) << "Destination" << std::setw(19) << "Plane model" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

	readFlightDataFromFile(existing_flights, numFlights);

	for (int i = 0; i < numFlights; i++)
	{
		const Flight& flight = existing_flights[i];
		std::cout << std::setfill(' ');
		std::cout << std::setw(8) << flight.flight_number;
		std::cout << std::setw(10) << flight.direction;

		std::cout << std::setfill('0');
		std::cout << std::right;
		std::cout << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
		std::cout << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

		std::cout << std::setfill(' ');
		std::cout << std::setw(20) << flight.destination;
		std::cout << std::setw(20) << flight.plane_model;
		std::cout << std::endl;

	}

	std::cout << "Exit to MAIN MENU!" << std::endl;

	delete[] existing_flights;
	existing_flights = nullptr;

	clear_console();

}

// Add data to flight data
void writeFlightStructureToFile(Flight* flights, int n)
{
	std::ofstream flight_data("flight_info_data.txt", std::ios::app);
	if (!flight_data)
	{
		std::cout << "Failed to open the file!" << std::endl;
		return;
	}

	for (int i = 0; i < n; i++) {

		std::cout << std::setfill(' ');
		flight_data << std::setw(15) << flights[i].flight_number;
		flight_data << std::setw(10) << flights[i].direction;

		std::cout << std::setfill('0');
		flight_data << "      " << std::setw(4) << flights[i].time.year << "/" << std::setw(2) << std::setfill('0') << flights[i].time.month << "/" << std::setw(2) << std::setfill('0') << flights[i].time.day;
		flight_data << " " << std::setw(2) << std::setfill('0') << flights[i].time.hour << ":" << std::setw(2) << std::setfill('0') << flights[i].time.min;

		std::cout << std::setfill(' ');
		flight_data << std::setw(20) << std::setfill(' ') << flights[i].destination;
		flight_data << std::setw(20) << std::setfill(' ') << flights[i].plane_model;
		flight_data << std::endl;
	}

	flight_data.close();
	std::cout << "Data has been written to flight_info_data.txt" << std::endl << std::endl;
}

void addFlightData()
{
	int n;
	std::cout << "Enter the number of flights to add: ";
	std::cin >> n;
	std::cin.ignore();

	Flight* new_flights = new Flight[n];

	for (int i = 0; i < n; i++)
	{
		std::cout << "Enter flight number: ";
		std::cin >> new_flights[i].flight_number;
		std::cin.ignore();

		std::cout << "Enter 'A' if it is an arrival time, 'D' if it is departure time: ";
		std::getline(std::cin, new_flights[i].direction);

		if (new_flights[i].direction == "A" || new_flights[i].direction == "a")
		{
			std::cout << "Enter Arrival date and time: " << std::endl;
			new_flights[i].time = add_date_and_time();
		}
		else
		{
			std::cout << "Enter Departure date and time: " << std::endl;
			new_flights[i].time = add_date_and_time();
		}
		std::cin.ignore();

		std::cout << "Enter destination: ";
		std::getline(std::cin, new_flights[i].destination);

		std::cout << "Enter plane model: ";
		std::getline(std::cin, new_flights[i].plane_model);

		std::cout << std::endl;
	}

	writeFlightStructureToFile(new_flights, n);
	delete[] new_flights;
	new_flights = nullptr;
	std::cout << "Data added successfully!" << std::endl;
	clear_console();
}

// Sorting Functions

void createFlightDataFile(const std::string& sorted_file_name, const Flight* sort_flight_data, int numFlights)
{
	
	std::ofstream output_file(sorted_file_name);

	if (output_file.is_open())
	{
		// Write sorted flight data to the file
		output_file << "---------------------------------------------------------------------------------------------" << std::endl;
		output_file << std::setw(10) << "Flight no." << std::setw(12) << "Arr / Dep" << std::setw(15) << "Date" << std::setw(28) << "Destination" << std::setw(19) << "Plane model" << std::endl;
		output_file << "---------------------------------------------------------------------------------------------" << std::endl;
		for (int i = 0; i < numFlights; i++)
		{
			const Flight& flight = sort_flight_data[i];
			std::cout << std::setfill(' ');
			output_file << std::setw(15) << flight.flight_number;
			output_file << std::setw(10) << flight.direction;

			std::cout << std::setfill('0');
			output_file << "      " << std::setw(4) << flight.time.year << "/" << std::setw(2) << std::setfill('0') << flight.time.month << "/" << std::setw(2) << std::setfill('0') << flight.time.day;
			output_file << " " << std::setw(2) << std::setfill('0') << flight.time.hour << ":" << std::setw(2) << std::setfill('0') << flight.time.min;

			std::cout << std::setfill(' ');
			output_file << std::setw(20) << std::setfill(' ') << flight.destination;
			output_file << std::setw(20) << std::setfill(' ') << flight.plane_model;
			output_file << std::endl;
		}

		output_file.close();
		std::cout << "File created successfully. Press ENTER!" << std::endl;
	}
	else
	{
		std::cout << "Unable to create the file." << std::endl;
	}

}

// compare dates function

bool compareFlightsByDate(const Flight& flight_1, const Flight& flight_2)
{
	// Compare flights based on their date and time
	if (flight_1.time.year != flight_2.time.year)
		return flight_1.time.year < flight_2.time.year;
	if (flight_1.time.month != flight_2.time.month)
		return flight_1.time.month < flight_2.time.month;
	if (flight_1.time.day != flight_2.time.day)
		return flight_1.time.day < flight_2.time.day;
	if (flight_1.time.hour != flight_2.time.hour)
		return flight_1.time.hour < flight_2.time.hour;
	return flight_1.time.min < flight_2.time.min;
}

void sortFlightData()
{
	Flight* sort_flight_data = new Flight[MAX_FLIGHTS];

	readFlightDataFromFile(sort_flight_data, numFlights);

	std::cout << "Select the sorting method: " << std::endl;
	std::cout << "1. Sort by flight number" << std::endl;
	std::cout << "2. Sort by date" << std::endl;
	std::cout << "3. Sort by destination" << std::endl;

	int sort_method;
	std::cout << "Enter the number of the sorting method: ";
	std::cin >> sort_method;

	clear_console();

	switch (sort_method)
	{
	case 1:
		// Sort by flight number
		std::cout << "Do you want to sort flight number by ascending or descending order? (A/D): ";
		char sort_by_flight_number_option;
		std::cin >> sort_by_flight_number_option;
		std::cin.ignore();

		if (sort_by_flight_number_option == 'A' || sort_by_flight_number_option == 'a')
		{
			for (int i = 0; i < numFlights; i++)
			{
				for (int j = i + 1; j < numFlights; j++)
				{
					if (sort_flight_data[i].flight_number > sort_flight_data[j].flight_number)
					{
						Flight temp = sort_flight_data[i];
						sort_flight_data[i] = sort_flight_data[j];
						sort_flight_data[j] = temp;
					}
				}
			}
		}
		else if (sort_by_flight_number_option == 'D' || sort_by_flight_number_option == 'd')
		{
			for (int i = 0; i < numFlights; i++)
			{
				for (int j = i + 1; j < numFlights; j++)
				{
					if (sort_flight_data[i].flight_number < sort_flight_data[j].flight_number)
					{
						Flight temp = sort_flight_data[i];
						sort_flight_data[i] = sort_flight_data[j];
						sort_flight_data[j] = temp;
					}
				}
			}
		}
		else
		{
			std::cout << "Invalid input!" << std::endl;
		}
		break;
	case 2:
		// Sort by date
		std::cout << "Do you want to sort date and time by ascending or descending order? (A/D): ";
		char sort_by_date_and_time_option;
		std::cin >> sort_by_date_and_time_option;
		std::cin.ignore();

		if (sort_by_date_and_time_option == 'A' || sort_by_date_and_time_option == 'a')
		{
			for (int i = 0; i < numFlights; i++)
			{
				for (int j = i + 1; j < numFlights; j++)
				{
					if (compareFlightsByDate(sort_flight_data[i], sort_flight_data[j]))
					{
						Flight temp = sort_flight_data[i];
						sort_flight_data[i] = sort_flight_data[j];
						sort_flight_data[j] = temp;
					}
				}

			}
		}
		else if (sort_by_date_and_time_option == 'D' || sort_by_date_and_time_option == 'd')
		{
			for (int i = 0; i < numFlights; i++)
			{
				for (int j = i + 1; j < numFlights; j++)
				{
					if (!compareFlightsByDate(sort_flight_data[i], sort_flight_data[j]))
					{
						Flight temp = sort_flight_data[i];
						sort_flight_data[i] = sort_flight_data[j];
						sort_flight_data[j] = temp;
					}
				}
			}
		}
		else
		{
			std::cout << "Invalid input!" << std::endl;
		}
		break;

	case 3:
		// Sort by destination
		std::cout << "Do you want to sort destination by ascending or descending order? (A/D): ";
		char sort_by_destination_option;
		std::cin >> sort_by_destination_option;
		std::cin.ignore();

		if (sort_by_destination_option == 'A' || sort_by_destination_option == 'a') {
			for (int i = 0; i < numFlights - 1; i++)
			{
				for (int j = 0; j < numFlights - i - 1; j++)
				{
					if (sort_flight_data[j].destination > sort_flight_data[j + 1].destination)
					{
						Flight temp = sort_flight_data[j];
						sort_flight_data[j] = sort_flight_data[j + 1];
						sort_flight_data[j + 1] = temp;
					}
				}
			}
		}
		else if (sort_by_destination_option == 'D' || sort_by_destination_option == 'd')
		{
			for (int i = 0; i < numFlights - 1; i++)
			{
				for (int j = 0; j < numFlights - i - 1; j++)
				{
					if (sort_flight_data[j].destination < sort_flight_data[j + 1].destination)
					{
						Flight temp = sort_flight_data[j];
						sort_flight_data[j] = sort_flight_data[j + 1];
						sort_flight_data[j + 1] = temp;
					}
				}
			}

		}
		else
		{
			std::cout << "Invalid input!" << std::endl;
		}
		break;

	default:
		std::cout << "Invalid input!" << std::endl;
		break;
	}

	for (int i = 0; i < numFlights; i++)
	{
		Flight& flight = sort_flight_data[i];
		std::cout << std::setfill(' ');
		std::cout << std::setw(8) << flight.flight_number;
		std::cout << std::setw(10) << flight.direction;

		std::cout << std::setfill('0');
		std::cout << std::right;
		std::cout << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
		std::cout << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

		std::cout << std::setfill(' ');
		std::cout << std::setw(20) << flight.destination;
		std::cout << std::setw(15) << flight.plane_model;
		std::cout << std::endl;

	}


	std::cout << "Do you want to create a new text file with sorted flight data? (Y/N): ";
	char create_file_option;
	std::cin >> create_file_option;


	if (create_file_option == 'Y' || create_file_option == 'y') {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the newline character from previous input

		std::string sorted_file_name;
		std::cout << "Enter the file name: ";
		std::getline(std::cin, sorted_file_name);
		sorted_file_name += ".txt";

		createFlightDataFile(sorted_file_name, sort_flight_data, numFlights);
		std::cin.ignore();
		std::cout << "Exit to MAIN MENU!" << std::endl;
		clear_console();
	}
	else
	{
		std::cin.ignore();
		std::cout << "Exit to MAIN MENU!" << std::endl;
		clear_console();
	}

	delete[] sort_flight_data;
	sort_flight_data = nullptr;

}

void searchFlightData()
{
	Flight* flight_data = new Flight[MAX_FLIGHTS];
	readFlightDataFromFile(flight_data, numFlights);

	std::cout << "Select the search method: " << std::endl;
	std::cout << "1. Search by flight number" << std::endl;
	std::cout << "2. Search by date" << std::endl;
	std::cout << "3. Search by destination" << std::endl;

	int search_method;
	std::cout << "Enter the number of the search method: ";
	std::cin >> search_method;

	clear_console();

	switch (search_method)
	{
	case 1:

	{
		int flight_number;
		std::cout << "Enter the flight number to search: ";
		std::cin >> flight_number;
		std::cin.ignore();

		bool found = false;

		std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
		std::cout << std::setw(10) << "Flight no." << std::setw(12) << "Arr / Dep" << std::setw(15) << "Date" << std::setw(28) << "Destination" << std::setw(19) << "Plane model" << std::endl;
		std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

		for (int i = 0; i < numFlights; i++)
		{
			if (flight_data[i].flight_number == flight_number)
			{
				found = true;
				const Flight& flight = flight_data[i];
				std::cout << std::setfill(' ');
				std::cout << std::setw(8) << flight.flight_number;
				std::cout << std::setw(10) << flight.direction;

				std::cout << std::setfill('0');
				std::cout << std::right;
				std::cout << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
				std::cout << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

				std::cout << std::setfill(' ');
				std::cout << std::setw(20) << flight.destination;
				std::cout << std::setw(15) << flight.plane_model;
				std::cout << std::endl;
			}
		}


		if (!found)
		{
			std::cout << "Flight number not found!" << std::endl;
		}
		std::cout << std::endl;
		clear_console();

		break;
	}
	case 2:
	{
		int search_year, search_month, search_day;
		std::cout << "Enter the date to search (YYYY MM DD): ";
		std::cin >> search_year >> search_month >> search_day;
		std::cin.ignore();

		bool found = false;

		std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
		std::cout << std::setw(10) << "Flight no." << std::setw(12) << "Arr / Dep" << std::setw(15) << "Date" << std::setw(28) << "Destination" << std::setw(19) << "Plane model" << std::endl;
		std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

		for (int i = 0; i < numFlights; i++)
		{
			if (flight_data[i].time.year == search_year && flight_data[i].time.month == search_month && flight_data[i].time.day == search_day)
			{
				found = true;
				const Flight& flight = flight_data[i];
				std::cout << std::setfill(' ');
				std::cout << std::setw(8) << flight.flight_number;
				std::cout << std::setw(10) << flight.direction;

				std::cout << std::setfill('0');
				std::cout << std::right;
				std::cout << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
				std::cout << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

				std::cout << std::setfill(' ');
				std::cout << std::setw(20) << flight.destination;
				std::cout << std::setw(15) << flight.plane_model;
				std::cout << std::endl;
			}
		}

		if (!found)
		{
			std::cout << "Flights not found for the given date!" << std::endl;
		}
		std::cout << std::endl;
		clear_console();

		break;
	}
	case 3:
	{
		std::string search_destination;
		std::cout << "Enter the destination to search: ";
		std::getline(std::cin, search_destination);

		bool found = false;

		std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
		std::cout << std::setw(10) << "Flight no." << std::setw(12) << "Arr / Dep" << std::setw(15) << "Date" << std::setw(28) << "Destination" << std::setw(19) << "Plane model" << std::endl;
		std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

		for (int i = 0; i < numFlights; i++)
		{
			if (flight_data[i].destination == search_destination)
			{
				found = true;
				const Flight& flight = flight_data[i];
				std::cout << std::setfill(' ');
				std::cout << std::setw(8) << flight.flight_number;
				std::cout << std::setw(10) << flight.direction;

				std::cout << std::setfill('0');
				std::cout << std::right;
				std::cout << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
				std::cout << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

				std::cout << std::setfill(' ');
				std::cout << std::setw(20) << flight.destination;
				std::cout << std::setw(15) << flight.plane_model;
				std::cout << std::endl;
			}
		}

		if (!found)
		{
			std::cout << "Flights not found for the given destination!" << std::endl;
		}
		std::cout << std::endl;
		clear_console();
		break;
	}
	default:
		std::cout << "Invalid search method selected!" << std::endl;
	}

	delete[] flight_data;
}

// Filter function

void createFilteredFlightDataFile(std::string file_name, const Flight* flight_data, int numFlights)
{
	std::ofstream file(file_name);

	if (file.is_open())
	{
		file << "---------------------------------------------------------------------------------------------" << std::endl;
		file << std::setw(10) << "Flight no." << std::setw(12) << "Arr / Dep" << std::setw(15) << "Date" << std::setw(28) << "Destination" << std::setw(19) << "Plane model" << std::endl;
		file << "---------------------------------------------------------------------------------------------" << std::endl;
		for (int i = 0; i < numFlights; i++)
		{
			const Flight& flight = flight_data[i];

			file << std::setfill(' ');
			file << std::setw(8) << flight.flight_number;
			file << std::setw(10) << flight.direction;

			file << std::setfill('0');
			file << std::right;
			file << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
			file << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

			file << std::setfill(' ');
			file << std::setw(20) << flight.destination;
			file << std::setw(15) << flight.plane_model;
			file << std::endl;
		}

		file.close();
		std::cout << "File created successfully! Press ENTER!" << std::endl;
	}
	else
	{
		std::cout << "Error opening file!" << std::endl;
	}
}


void filterFlightData()
{
	Flight* filter_flight_data = new Flight[MAX_FLIGHTS];
	numFlights = 0;
	int filter_flight_number_count = 0;
	readFlightDataFromFile(filter_flight_data, numFlights);

	std::cout << "Available filters:" << std::endl;
	std::cout << "1. Flight Number" << std::endl;
	std::cout << "2. Arrival/Departure" << std::endl;
	std::cout << "3. Date" << std::endl;
	std::cout << "4. Destination" << std::endl;
	std::cout << "5. Plane Model" << std::endl;
	std::cout << std::endl;

	int filter_flight_number = 0;
	std::string filter_direction = {};
	int filter_year = 0, filter_month = 0, filter_day = 0;
	std::string filter_destination = {};
	std::string filter_plane_model = {};

	const std::string filterOptions[5] = { "Flight Number", "Arrival/Departure", "Date", "Destination", "Plane Model" };

	std::cout << "How many filters do you want to apply? " << std::endl;
	int filter_count = 0;
	std::cout << "Enter the count of filters (MAX 5 filters):";
	std::cin >> filter_count;

	std::cout << std::endl;

	int* filterSelection = new int[filter_count];
	std::set<int> selectedFilters;  // To keep track of selected filter numbers

	for (int i = 0; i < filter_count; i++)
	{
		std::cout << "Enter the filter number " << i + 1 << ": ";
		int filter_input = 0;
		while (true)
		{
			std::cin >> filter_input;
			if (filter_input < 1 || filter_input > 5) {
				std::cout << "Invalid filter number entered! Please enter a filter number from 1 to 5: ";
			}
			else if (selectedFilters.count(filter_input) > 0) {
				std::cout << "The same filter number has already been entered! Please enter a different filter number: ";
			}
			else {
				selectedFilters.insert(filter_input);
				break;
			}
		}
		filterSelection[i] = filter_input;

	}

	std::cout << std::endl;
	std::cout << "Input necessary data for the selected filters belove!" << std::endl;
	std::cout << "The selected filters are: " << std::endl;
	for (int i = 0; i < filter_count; i++)
	{
		if (filterSelection[i] == 1)
		{
			std::cout << "Flight Number: ";
			std::cin >> filter_flight_number;
		}
		else if (filterSelection[i] == 2)
		{
			std::cout << "Arrival/Departure (A/D): ";
			std::cin >> filter_direction;
		}
		else if (filterSelection[i] == 3)
		{
			std::cout << "Date (YYYY MM DD): ";
			std::cin >> filter_year >> filter_month >> filter_day;
		}
		else if (filterSelection[i] == 4)
		{
			std::cout << "Destination (City): ";
			std::cin >> filter_destination;
		}
		else
		{
			std::cout << "Plane Model: ";
			std::cin >> filter_plane_model;
		}
	}

	bool found = false;

	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(10) << "Flight no." << std::setw(12) << "Arr / Dep" << std::setw(15) << "Date" << std::setw(28) << "Destination" << std::setw(19) << "Plane model" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

	for (int i = 0; i < numFlights; i++)
	{
		const Flight& flight = filter_flight_data[i];

		// Check if the flight matches the selected filters
		if ((filter_flight_number == 0 || flight.flight_number == filter_flight_number) &&
			(filter_direction.empty() || flight.direction == filter_direction) &&
			(filter_year == 0 || flight.time.year == filter_year) &&
			(filter_month == 0 || flight.time.month == filter_month) &&
			(filter_day == 0 || flight.time.day == filter_day) &&
			(filter_destination.empty() || flight.destination == filter_destination) &&
			(filter_plane_model.empty() || flight.plane_model == filter_plane_model))
		{
			found = true;
			std::cout << std::setfill(' ');
			std::cout << std::setw(8) << flight.flight_number;
			std::cout << std::setw(10) << flight.direction;

			std::cout << std::setfill('0');
			std::cout << std::right;
			std::cout << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
			std::cout << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

			std::cout << std::setfill(' ');
			std::cout << std::setw(20) << flight.destination;
			std::cout << std::setw(15) << flight.plane_model;
			std::cout << std::endl;
		}
	}

	if (!found)
	{
		std::cout << "No flights found matching the filter criteria!" << std::endl;
	}

	
	int nextAvailableIndex = 0; // Index to track the next available position in the array

	for (int i = 0; i < numFlights; i++)
	{
		const Flight& flight = filter_flight_data[i];

		// Check if the flight matches the selected filters
		if ((filter_flight_number == 0 || flight.flight_number == filter_flight_number) &&
			(filter_direction.empty() || flight.direction == filter_direction) &&
			(filter_year == 0 || flight.time.year == filter_year) &&
			(filter_month == 0 || flight.time.month == filter_month) &&
			(filter_day == 0 || flight.time.day == filter_day) &&
			(filter_destination.empty() || flight.destination == filter_destination) &&
			(filter_plane_model.empty() || flight.plane_model == filter_plane_model))
		{
			// Flight matches the filters, keep it in the array
			filter_flight_data[nextAvailableIndex] = flight;
			nextAvailableIndex++;
			found = true;
		}
	}
	// Update the number of flights to the new count
	filter_flight_number_count = nextAvailableIndex;

	// Copy the filtered flights back to the original array
	numFlights = filter_flight_number_count;
	for (int i = 0; i < filter_flight_number_count; i++) {
		filter_flight_data[i] = filter_flight_data[i];
	}
	
	std::cout << "Do you want to create a new text file with sorted flight data? (Y/N): ";
	char create_file_option;
	std::cin >> create_file_option;


	if (create_file_option == 'Y' || create_file_option == 'y') {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the newline character from previous input

		std::string filtered_file_name;
		std::cout << "Enter the file name: ";
		std::getline(std::cin, filtered_file_name);
		filtered_file_name += ".txt";

		createFilteredFlightDataFile(filtered_file_name, filter_flight_data, numFlights);
		std::cin.ignore();
		std::cout << "Exit to MAIN MENU!" << std::endl;
		clear_console();
	}
	else
	{
		std::cin.ignore();
		std::cout << "Exit to MAIN MENU!" << std::endl;
		clear_console();
	}

	delete[] filter_flight_data;
	delete[] filterSelection;

}

void editFlightData()
{
	numFlights = 0;
	Flight* edit_flight_data = new Flight[MAX_FLIGHTS];
	readFlightDataFromFile(edit_flight_data, numFlights);
	std::cout << "Available flight data for editing." << std::endl << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(10) << "Flight no." << std::setw(12) << "Arr / Dep" << std::setw(15) << "Date" << std::setw(28) << "Destination" << std::setw(19) << "Plane model" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

	for (int i = 0; i < numFlights; i++)
	{
		const Flight& flight = edit_flight_data[i];
		std::cout << std::setfill(' ');
		std::cout << std::setw(8) << flight.flight_number;
		std::cout << std::setw(10) << flight.direction;

		std::cout << std::setfill('0');
		std::cout << std::right;
		std::cout << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
		std::cout << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

		std::cout << std::setfill(' ');
		std::cout << std::setw(20) << flight.destination;
		std::cout << std::setw(20) << flight.plane_model;
		std::cout << std::endl;

	}
	std::cout << std::endl;
	int flight_number;
	std::cout << "Enter the flight number you want to edit: ";
	std::cin >> flight_number;

	clear_console();

	int flight_index = -1;
	for (int i = 0; i < numFlights; i++)
	{
		if (edit_flight_data[i].flight_number == flight_number)
		{
			flight_index = i;
			break;
		}
	}

	if (flight_index == -1)
	{
		std::cout << "Flight not found!" << std::endl;
		delete[] edit_flight_data;
		return;
	}

	std::cout << "Flight data before editing:" << std::endl;
	const Flight& flight = edit_flight_data[flight_index];
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(10) << "Flight no." << std::setw(12) << "Arr / Dep" << std::setw(15) << "Date" << std::setw(28) << "Destination" << std::setw(19) << "Plane model" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setfill(' ');
	std::cout << std::setw(8) << flight.flight_number;
	std::cout << std::setw(10) << flight.direction;

	std::cout << std::setfill('0');
	std::cout << std::right;
	std::cout << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
	std::cout << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

	std::cout << std::setfill(' ');
	std::cout << std::setw(20) << flight.destination;
	std::cout << std::setw(20) << flight.plane_model;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Do you want to edit the selected flight data (Y/N): ";
	char edit_choice;
	std::cin >> edit_choice;

	if (edit_choice == 'Y' || edit_choice == 'y') {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the newline character from previous input

		// New flight data input
		std::cout << "Enter the new flight number: ";
		std::cin >> edit_flight_data[flight_index].flight_number;
		std::cin.ignore();

		std::cout << "Enter the new direction (A/D): ";
		std::getline(std::cin, edit_flight_data[flight_index].direction);

		if (edit_flight_data[flight_index].direction == "A" || edit_flight_data[flight_index].direction == "a")
		{
			std::cout << "Enter new Arrival date and time: " << std::endl;
			edit_flight_data[flight_index].time = add_date_and_time();
		}
		else
		{
			std::cout << "Enter new Departure date and time: " << std::endl;
			edit_flight_data[flight_index].time = add_date_and_time();
		}
		std::cin.ignore();

		std::cout << "Enter the new destination: ";
		std::getline(std::cin, edit_flight_data[flight_index].destination);

		std::cout << "Enter the new plane model: ";
		std::getline(std::cin, edit_flight_data[flight_index].plane_model);

		std::cout << std::endl;

		std::cout << "Do you want to rewrite the data in the original file (Y/N): ";
		char rewrite_choice;
		std::cin >> rewrite_choice;

		if (rewrite_choice == 'Y' || rewrite_choice == 'y') {
			std::ofstream flight_data_file("flight_info_data.txt", std::ios::out | std::ios::trunc);

			if (!flight_data_file)
			{
				std::cerr << "Failed to open the file for writing!" << std::endl;
				delete[] edit_flight_data;
				return;
			}

			// Write updated flight data to the file
			
			for (int i = 0; i < numFlights; i++)
			{
				const Flight& flight = edit_flight_data[i];
				flight_data_file << std::setfill(' ');
				flight_data_file << std::setw(8) << flight.flight_number;
				flight_data_file << std::setw(10) << flight.direction;

				flight_data_file << std::setfill('0');
				flight_data_file << std::right;
				flight_data_file << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
				flight_data_file << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

				flight_data_file << std::setfill(' ');
				flight_data_file << std::setw(20) << flight.destination;
				flight_data_file << std::setw(20) << flight.plane_model;
				flight_data_file << std::endl;

			}

			flight_data_file.close();

			std::cout << "Flight data updated and rewritten successfully!" << std::endl;
		}
		else {
			std::cout << "Flight data updated successfully!" << std::endl;
		}

		clear_console();
		
	}
	else
	{
		std::cin.ignore();
		std::cout << "Exit to MAIN MENU!" << std::endl;
		clear_console();
	}

	delete[] edit_flight_data;
}

// Delete flight data

void deleteSingleFlightData()
{
	
	Flight* delete_flight_data = new Flight[MAX_FLIGHTS];
	readFlightDataFromFile(delete_flight_data, numFlights);

	if (numFlights == 0)
	{
		std::cout << "No flight data found!" << std::endl;
		return;
	}

	std::cout << "Available flight data for deletion." << std::endl << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(10) << "Flight no." << std::setw(12) << "Arr / Dep" << std::setw(15) << "Date" << std::setw(28) << "Destination" << std::setw(19) << "Plane model" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

	for (int i = 0; i < numFlights; i++)
	{
		const Flight& flight = delete_flight_data[i];
		std::cout << std::setfill(' ');
		std::cout << std::setw(8) << flight.flight_number;
		std::cout << std::setw(10) << flight.direction;

		std::cout << std::setfill('0');
		std::cout << std::right;
		std::cout << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
		std::cout << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

		std::cout << std::setfill(' ');
		std::cout << std::setw(20) << flight.destination;
		std::cout << std::setw(20) << flight.plane_model;
		std::cout << std::endl;

	}

	std::cout << "Enter the flight number you want to delete: ";
	int flight_number;
	std::cin >> flight_number;

	clear_console();

	int flight_index = -1;
	for (int i = 0; i < numFlights; i++)
	{
		if (delete_flight_data[i].flight_number == flight_number)
		{
			flight_index = i;
			break;
		}
	}

	if (flight_index == -1)
	{
		std::cout << "Flight not found!" << std::endl;
		delete[] delete_flight_data;
		return;
	}

	std::cout << "Flight data before deleting:" << std::endl;

	const Flight& flight = delete_flight_data[flight_index];
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(10) << "Flight no." << std::setw(12) << "Arr / Dep" << std::setw(15) << "Date" << std::setw(28) << "Destination" << std::setw(19) << "Plane model" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

	// -----------------------------------------------------
	std::cout << std::setfill(' ');
	std::cout << std::setw(8) << flight.flight_number;
	std::cout << std::setw(10) << flight.direction;

	std::cout << std::setfill('0');
	std::cout << std::right;
	std::cout << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
	std::cout << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

	std::cout << std::setfill(' ');
	std::cout << std::setw(20) << flight.destination;
	std::cout << std::setw(15) << flight.plane_model;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Do you want to delete the selected flight data (Y/N): ";
	char delete_choice;
	std::cin >> delete_choice;

	if (delete_choice == 'Y' || delete_choice == 'y') {
		// Create a temporary file to store the flight data without the deleted entry
		std::ofstream temp_file("temp_flight_info_data.txt", std::ios::out | std::ios::trunc);
		if (!temp_file)
		{
			std::cerr << "Failed to create temporary file for writing!" << std::endl;
			delete[] delete_flight_data;
			return;
		}

		// Write flight data to the temporary file, excluding the deleted entry
		for (int i = 0; i < numFlights; i++)
		{
			if (i != flight_index)
			{
				const Flight& flight = delete_flight_data[i];
				temp_file << std::setfill(' ');
				temp_file << std::setw(8) << flight.flight_number;
				temp_file << std::setw(10) << flight.direction;

				temp_file << std::setfill('0');
				temp_file << std::right;
				temp_file << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
				temp_file << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

				temp_file << std::setfill(' ');
				temp_file << std::setw(20) << flight.destination;
				temp_file << std::setw(15) << flight.plane_model;
				temp_file << std::endl;
			}
		}

		temp_file.close();

		// Remove the original file
		if (std::remove("flight_info_data.txt") != 0)
		{
			std::cerr << "Failed to remove the original file!" << std::endl;
			// Handle the error as needed
			delete[] delete_flight_data;
			return;
		}

		// Rename the temporary file to the original file name
		if (std::rename("temp_flight_info_data.txt", "flight_info_data.txt") != 0)
		{
			std::cerr << "Failed to rename the file!" << std::endl;
			// Handle the error as needed
			delete[] delete_flight_data;
			return;
		}

		std::cout << "Flight data deleted successfully!" << std::endl;
	}
	else
	{
		std::cin.ignore();
		std::cout << "Exit to MAIN MENU!" << std::endl;
		clear_console();
	}

	delete[] delete_flight_data;

	clear_console();
}

void deleteAllFlightData()
{
	std::cout << "Are you sure you want to delete all flight data? (Y/N): ";
	char confirmation;
	std::cin >> confirmation;

	if (confirmation == 'Y' || confirmation == 'y')
	{
		if (std::remove("flight_info_data.txt") != 0)
		{
			std::cerr << "Failed to remove the original file!" << std::endl;
			return;
		}

		// Rename the temporary file to the original file name
		std::ifstream temp_file("temp_flight_info_data.txt", std::ios::in);
		std::ofstream original_file("flight_info_data.txt", std::ios::out | std::ios::trunc);

		if (!temp_file || !original_file)
		{
			std::cerr << "Failed to rename the file!" << std::endl;
			return;
		}

		original_file << temp_file.rdbuf();

		temp_file.close();
		original_file.close();

		// Delete the temporary file
		if (std::remove("temp_flight_info_data.txt") != 0)
		{
			std::cerr << "Failed to delete the temporary file!" << std::endl;
			return;
		}

		std::cout << "Flight data deleted successfully!" << std::endl;
	}
	else
	{
		std::cout << "Flight data deletion canceled." << std::endl;
		std::cin.ignore();
		std::cout << "Exit to MAIN MENU!" << std::endl;
		clear_console();
	}

	clear_console();
}

void deleteFilteredFlightData()
{
	Flight* filter_for_delete_flight_data = new Flight[MAX_FLIGHTS];
	numFlights = 0;
	int filter_delete_flight_number_count = 0;
	readFlightDataFromFile(filter_for_delete_flight_data, numFlights);

	std::cout << "Available filters:" << std::endl;
	std::cout << "1. Flight Number" << std::endl;
	std::cout << "2. Arrival/Departure" << std::endl;
	std::cout << "3. Date" << std::endl;
	std::cout << "4. Destination" << std::endl;
	std::cout << "5. Plane Model" << std::endl;
	std::cout << std::endl;

	int filter_delete_flight_number = 0;
	std::string filter_delete_direction = {};
	int filter_delete_year = 0, filter_delete_month = 0, filter_delete_day = 0;
	std::string filter_delete_destination = {};
	std::string filter_delete_plane_model = {};

	const std::string filter_options[5] = { "Flight Number", "Arrival/Departure", "Date", "Destination", "Plane Model" };

	std::cout << "How many filters do you want to apply? " << std::endl;
	int filter_count = 0;
	std::cout << "Enter the count of filters (MAX 5 filters):";
	std::cin >> filter_count;

	std::cout << std::endl;

	int* filter_delete_selection = new int[filter_count];
	std::set<int> selectedFilters;  // To keep track of selected filter numbers

	for (int i = 0; i < filter_count; i++)
	{
		std::cout << "Enter the filter number " << i + 1 << ": ";
		int filter_delete_input = 0;
		while (true)
		{
			std::cin >> filter_delete_input;
			if (filter_delete_input < 1 || filter_delete_input > 5) {
				std::cout << "Invalid filter number entered! Please enter a filter number from 1 to 5: ";
			}
			else if (selectedFilters.count(filter_delete_input) > 0) {
				std::cout << "The same filter number has already been entered! Please enter a different filter number: ";
			}
			else {
				selectedFilters.insert(filter_delete_input);
				break;
			}
		}
		filter_delete_selection[i] = filter_delete_input;

	}

	std::cout << std::endl;
	std::cout << "Input necessary data for the selected filters belove!" << std::endl;
	std::cout << "The selected filters are: " << std::endl;
	for (int i = 0; i < filter_count; i++)
	{
		if (filter_delete_selection[i] == 1)
		{
			std::cout << "Flight Number: ";
			std::cin >> filter_delete_flight_number;
		}
		else if (filter_delete_selection[i] == 2)
		{
			std::cout << "Arrival/Departure (A/D): ";
			std::cin >> filter_delete_direction;
		}
		else if (filter_delete_selection[i] == 3)
		{
			std::cout << "Date (YYYY MM DD): ";
			std::cin >> filter_delete_year >> filter_delete_month >> filter_delete_day;
		}
		else if (filter_delete_selection[i] == 4)
		{
			std::cout << "Destination (City): ";
			std::cin >> filter_delete_destination;
		}
		else
		{
			std::cout << "Plane Model: ";
			std::cin >> filter_delete_plane_model;
		}
	}

	bool found = false;

	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(10) << "Flight no." << std::setw(12) << "Arr / Dep" << std::setw(15) << "Date" << std::setw(28) << "Destination" << std::setw(19) << "Plane model" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

	for (int i = 0; i < numFlights; i++)
	{
		const Flight& flight = filter_for_delete_flight_data[i];

		// Check if the flight matches the selected filters
		if ((filter_delete_flight_number == 0 || flight.flight_number == filter_delete_flight_number) &&
			(filter_delete_direction.empty() || flight.direction == filter_delete_direction) &&
			(filter_delete_year == 0 || flight.time.year == filter_delete_year) &&
			(filter_delete_month == 0 || flight.time.month == filter_delete_month) &&
			(filter_delete_day == 0 || flight.time.day == filter_delete_day) &&
			(filter_delete_destination.empty() || flight.destination == filter_delete_destination) &&
			(filter_delete_plane_model.empty() || flight.plane_model == filter_delete_plane_model))
		{
			found = true;
			std::cout << std::setfill(' ');
			std::cout << std::setw(8) << flight.flight_number;
			std::cout << std::setw(10) << flight.direction;

			std::cout << std::setfill('0');
			std::cout << std::right;
			std::cout << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
			std::cout << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

			std::cout << std::setfill(' ');
			std::cout << std::setw(20) << flight.destination;
			std::cout << std::setw(15) << flight.plane_model;
			std::cout << std::endl;
		}
	}

	int flight_index = -1;
	for (int i = 0; i < numFlights; i++)
	{
		if (filter_for_delete_flight_data[i].flight_number == filter_delete_flight_number)
		{
			flight_index = i;
			break;
		}
	}

	if (!found)
	{
		std::cout << "No flights found matching the filter criteria!" << std::endl;
	}
	int nextAvailableIndex = 0; // Index to track the next available position in the array

	for (int i = 0; i < numFlights; i++)
	{
		const Flight& flight = filter_for_delete_flight_data[i];

		// Check if the flight matches the selected filters
		if ((filter_delete_flight_number == 0 || flight.flight_number == filter_delete_flight_number) &&
			(filter_delete_direction.empty() || flight.direction == filter_delete_direction) &&
			(filter_delete_year == 0 || flight.time.year == filter_delete_year) &&
			(filter_delete_month == 0 || flight.time.month == filter_delete_month) &&
			(filter_delete_day == 0 || flight.time.day == filter_delete_day) &&
			(filter_delete_destination.empty() || flight.destination == filter_delete_destination) &&
			(filter_delete_plane_model.empty() || flight.plane_model == filter_delete_plane_model))
		{
			// Flight matches the filters, keep it in the array
			filter_for_delete_flight_data[nextAvailableIndex] = flight;
			nextAvailableIndex++;
			found = true;
		}
	}
	// Update the number of flights to the new count
	filter_delete_flight_number_count = nextAvailableIndex;

	// Copy the filtered flights back to the original array
	numFlights = filter_delete_flight_number_count;
	for (int i = 0; i < filter_delete_flight_number_count; i++) {
		filter_for_delete_flight_data[i] = filter_for_delete_flight_data[i];
	}

	std::cout << "Do you want to delete all the flights that match the selected filters? (Y/N): ";
	char filter_delete_confirm;
	std::cin >> filter_delete_confirm;

	if (filter_delete_confirm == 'Y' || filter_delete_confirm == 'y')
	{
		// Create a temporary file to store the flight data without the deleted entry
		std::ofstream temp_file("temp_flight_info_data.txt", std::ios::out | std::ios::trunc);
		if (!temp_file)
		{
			std::cerr << "Failed to create temporary file for writing!" << std::endl;
			delete[] filter_for_delete_flight_data;
			return;
		}

		// Write flight data to the temporary file, excluding the deleted entry
		for (int i = 0; i < numFlights; i++)
		{
			if (i != flight_index)
			{
				const Flight& flight = filter_for_delete_flight_data[i];
				temp_file << std::setfill(' ');
				temp_file << std::setw(8) << flight.flight_number;
				temp_file << std::setw(10) << flight.direction;

				temp_file << std::setfill('0');
				temp_file << std::right;
				temp_file << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
				temp_file << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

				temp_file << std::setfill(' ');
				temp_file << std::setw(20) << flight.destination;
				temp_file << std::setw(15) << flight.plane_model;
				temp_file << std::endl;
			}
		}

		temp_file.close();

		// Remove the original file
		if (std::remove("flight_info_data.txt") != 0)
		{
			std::cerr << "Failed to remove the original file!" << std::endl;
			// Handle the error as needed
			delete[] filter_for_delete_flight_data;
			return;
		}

		// Rename the temporary file to the original file name
		if (std::rename("temp_flight_info_data.txt", "flight_info_data.txt") != 0)
		{
			std::cerr << "Failed to rename the file!" << std::endl;
			// Handle the error as needed
			delete[] filter_for_delete_flight_data;
			return;
		}
		std::cout << "All the flights that match the selected filters have been deleted!" << std::endl;
	}
	else
	{
		std::cout << "No flights have been deleted!" << std::endl;
	}


}
 