#include "Flight_Functions.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

#include <cstdlib> // to use system("cls"), std::rename(), std::remove();
#include <mutex> // mutual exclusion to prevent multiple threads from accessing shared resources at the same time

const int MAX_PASSENGERS = 500;
int passengerCount = 0;

void readPassengerDataFromFile(Passenger passengers[], int& passengerCount)
{
	
	std::ifstream passenger_data("passenger_info_data.txt");
	if (!passenger_data)
	{
		std::cerr << "Failed to open the file!" << std::endl;
		return;
	}
	std::string line;

	passengerCount = 0;

	while (std::getline(passenger_data, line) && passengerCount < MAX_PASSENGERS)
	{
		std::istringstream iss(line);
		Passenger passenger;

		iss >> passenger.passenger_id >> passenger.name >> passenger.surname >> passenger.flight_number >> passenger.seat_number;
		
		passengers[passengerCount] = passenger;
		passengerCount++;
	}

	passenger_data.close();
}

void viewPassengerData()
{
	
	Passenger* passengers = new Passenger[MAX_PASSENGERS];
	

	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(12) << "Passenger ID" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(15) << "Flight No." << std::setw(15) << "Seat No." << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

	readPassengerDataFromFile(passengers, passengerCount);

	for (int i = 0; i < passengerCount; i++)
	{
		const Passenger& passenger = passengers[i];
		std::cout << std::setfill(' ');
		std::cout << std::setw(12) << passenger.passenger_id;
		std::cout << std::setw(15) << passenger.name;
		std::cout << std::setw(15) << passenger.surname;
		std::cout << std::setw(15) << passenger.flight_number;
		std::cout << std::setw(15) << passenger.seat_number << std::endl;
	}

	std::cout << "Exit to MAIN MENU!" << std::endl;

	delete[] passengers;
	passengers = nullptr;

	clear_console();
}

