#include "Functions.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

#include <cstdlib> // to use system("cls");
#include <mutex> // to use std::lock_guard<std::mutex> lock(mtx);

// view Flight data
constexpr int MAX_FLIGHTS = 100;
int numFlights = 0;

std::mutex console_mutex;
void clear_console()
{
	console_mutex.lock();
	system("cls");
	console_mutex.unlock();
}

void readFlightDataFromFile(Flight flights[], int& numFlight)
{
	std::ifstream flight_data("flight_info_data.txt");
	if (!flight_data)
	{
		std::cerr << "Failed to open the file!" << std::endl;
		return;
	}
	std::string line;

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

		iss >> flight.destination >> flight.plane_model;

		flights[numFlights] = flight;
		numFlights++;
	}

	flight_data.close();
}

void viewFlightData()
{
	Flight existing_flights[MAX_FLIGHTS];

	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(10) << "Flight no." << std::setw(15) << "Arr / Dep" << std::setw(15) << "Date" << std::setw(28) << "Destination" << std::setw(19) << "Plane model" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

	readFlightDataFromFile(existing_flights, numFlights);

	for (int i = 0; i < numFlights; i++)
	{
		const Flight& flight = existing_flights[i];
		std::cout << std::setw(10) << flight.flight_number << std::setw(10) << flight.direction << std::setw(15) << existing_flights[i].time.year << "/" << existing_flights[i].time.month << "/" << existing_flights[i].time.day << " " << existing_flights[i].time.hour << ":" << existing_flights[i].time.min << std::setw(20) << flight.destination << std::setw(20) << flight.plane_model;
		std::cout << std::endl;
	}

	std::cout << std::endl << "Press ENTER to exit view mode.";

	clear_console();
}

// Add data to flight data
void writeStructureToFile(Flight* flights, int n)
{
	std::ofstream flight_data("flight_info_data.txt", std::ios::app);
	if (!flight_data)
	{
		std::cout << "Failed to open the file!" << std::endl;
		return;
	}

	for (int i = 0; i < n; i++) {
		flight_data << std::setw(15) << flights[i].flight_number;
		flight_data << std::setw(10) << flights[i].direction;
		flight_data << std::setw(10) << flights[i].time.year << "/" << flights[i].time.month << "/" << flights[i].time.day << " " << flights[i].time.hour << ":" << flights[i].time.min;
		flight_data << std::setw(20) << flights[i].destination;
		flight_data << std::setw(20) << flights[i].plane_model << std::endl;
	}

	flight_data.close();
	std::cout << "Data has been written to flight_info_data.txt" << std::endl;
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

	writeStructureToFile(new_flights, n);
	std::cout << "Data added successfully! Press ENTER!";
	delete[] new_flights;

	clear_console();
}


void sortFlightData()
{
	Flight sort_flight_data[MAX_FLIGHTS];

	readFlightDataFromFile(sort_flight_data, numFlights);

	std::cout << "Select the sorting method: " << std::endl;
	std::cout << "1. Sort by flight number" << std::endl;
	std::cout << "2. Sort by date" << std::endl;
	std::cout << "3. Sort by destination" << std::endl;

	int sort_method;
	std::cin >> sort_method;

	switch (sort_method)
	{
	case 1:
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
		break;
	case 2:
		
		break;
	default:
		std::cout << "Invalid input!" << std::endl;
		break;
	}

	/*for (int i = 0; i < numFlights; i++)
	{
		const Flight& flight = sort_flight_data[i];
		std::cout << std::setw(10) << flight.flight_number << std::setw(10) << flight.direction << std::setw(15) << sort_flight_data[i].time.year << "/" << sort_flight_data[i].time.month << "/" << sort_flight_data[i].time.day << " " << sort_flight_data[i].time.hour << ":" << sort_flight_data[i].time.min << std::setw(20) << flight.destination << std::setw(20) << flight.plane_model;
		std::cout << std::endl;
	}*/


	

}
