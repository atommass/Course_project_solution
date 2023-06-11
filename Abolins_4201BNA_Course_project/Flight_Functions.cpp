#include "Flight_Functions.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

#include <cstdlib> // to use system("cls");
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
		std::cout << std::setw(15) << flight.plane_model;
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
		numFlights = 0;
		std::ofstream output_file(sorted_file_name);

		if (output_file.is_open())
		{
			// Write sorted flight data to the file
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
			std::cout << "File created successfully." << std::endl;
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
	Flight *sort_flight_data = new Flight[MAX_FLIGHTS];

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
	} else
	{
		std::cin.ignore();
		std::cout << "Exit to MAIN MENU!" << std::endl;
		clear_console();
	}

	delete[] sort_flight_data;
	sort_flight_data = nullptr;
	
}







