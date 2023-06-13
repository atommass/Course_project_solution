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

void writePassengerDataToFile(Passenger* passengers, int n)
{
	std::ofstream passenger_data("passenger_info_data.txt", std::ios::app);
	if (!passenger_data)
	{
		std::cout << "Failed to open the file!" << std::endl;
		return;
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << std::setfill(' ');
		passenger_data << std::setw(12) << passengers[i].passenger_id;
		passenger_data << std::setw(15) << passengers[i].name;
		passenger_data << std::setw(15) << passengers[i].surname;
		passenger_data << std::setw(15) << passengers[i].flight_number;
		passenger_data << std::setw(15) << passengers[i].seat_number << std::endl;
	}

	passenger_data.close();

	std::cout << "Data has been written to passenger_info_data.txt" << std::endl << std::endl;
}

void addPassengerData()
{
	int n;
	std::cout << "Enter the number of passengers to add: ";
	std::cin >> n;
	std::cin.ignore();

	Passenger* new_passengers = new Passenger[n];

	for (int i = 0; i < n; i++)
	{
		std::cout << "Enter passenger ID: ";
		std::cin >> new_passengers[i].passenger_id;
		std::cin.ignore();

		std::cout << "Enter passenger name: ";
		std::getline(std::cin, new_passengers[i].name);

		std::cout << "Enter passenger surname: ";
		std::getline(std::cin, new_passengers[i].surname);

		std::cout << "Enter flight number: ";
		std::cin >> new_passengers[i].flight_number;
		std::cin.ignore();

		std::cout << "Enter seat number: ";
		std::getline(std::cin, new_passengers[i].seat_number);

		std::cout << std::endl;
	}

	writePassengerDataToFile(new_passengers, n);

	delete[] new_passengers;
	new_passengers = nullptr;
	std::cout << "Data added successfully!" << std::endl;
	clear_console();
}

void createPassengerDataFile(const std::string& sorted_file_name, const Passenger* sorted_passenger_data, int numPassengers)
{
	std::ofstream output_file(sorted_file_name);

	if (output_file.is_open())
	{
		// Write sorted passenger data to the file
		for (int i = 0; i < numPassengers; i++)
		{
			const Passenger& passenger = sorted_passenger_data[i];
			std::cout << std::setfill(' ');
			output_file << std::setw(12) << passenger.passenger_id;
			output_file << std::setw(15) << passenger.name;
			output_file << std::setw(15) << passenger.surname;
			output_file << std::setw(15) << passenger.flight_number;
			output_file << std::setw(15) << passenger.seat_number << std::endl;
		}

		output_file.close();
		std::cout << "File created successfully." << std::endl;
	}
	else
	{
		std::cout << "Unable to create the file." << std::endl;
	}
}

void sortPassengerData()
{
    Passenger* sort_passenger_data = new Passenger[MAX_PASSENGERS];

    readPassengerDataFromFile(sort_passenger_data, passengerCount);

    std::cout << "Select the sorting method:" << std::endl;
    std::cout << "1. Sort by passenger ID" << std::endl;
    std::cout << "2. Sort by name" << std::endl;
    std::cout << "3. Sort by surname" << std::endl;

    int sort_method;
    std::cout << "Enter the number of the sorting method: ";
    std::cin >> sort_method;

    clear_console();

    switch (sort_method)
    {
    case 1:
        // Sort by passenger ID
        std::cout << "Do you want to sort passenger ID by ascending or descending order? (A/D): ";
        char sort_by_passenger_id_option;
        std::cin >> sort_by_passenger_id_option;
        std::cin.ignore();

        if (sort_by_passenger_id_option == 'A' || sort_by_passenger_id_option == 'a')
        {
            for (int i = 0; i < passengerCount - 1; i++)
            {
                for (int j = 0; j < passengerCount - i - 1; j++)
                {
                    if (sort_passenger_data[j].passenger_id > sort_passenger_data[j + 1].passenger_id)
                    {
                        Passenger temp = sort_passenger_data[j];
                        sort_passenger_data[j] = sort_passenger_data[j + 1];
                        sort_passenger_data[j + 1] = temp;
                    }
                }
            }
        }
        else if (sort_by_passenger_id_option == 'D' || sort_by_passenger_id_option == 'd')
        {
            for (int i = 0; i < passengerCount - 1; i++)
            {
                for (int j = 0; j < passengerCount - i - 1; j++)
                {
                    if (sort_passenger_data[j].passenger_id < sort_passenger_data[j + 1].passenger_id)
                    {
                        Passenger temp = sort_passenger_data[j];
                        sort_passenger_data[j] = sort_passenger_data[j + 1];
                        sort_passenger_data[j + 1] = temp;
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
        // Sort by name
        std::cout << "Do you want to sort name by ascending or descending order? (A/D): ";
        char sort_by_name_option;
        std::cin >> sort_by_name_option;
        std::cin.ignore();

        if (sort_by_name_option == 'A' || sort_by_name_option == 'a')
        {
            for (int i = 0; i < passengerCount - 1; i++)
            {
                for (int j = 0; j < passengerCount - i - 1; j++)
                {
                    if (sort_passenger_data[j].name > sort_passenger_data[j + 1].name)
                    {
                        Passenger temp = sort_passenger_data[j];
                        sort_passenger_data[j] = sort_passenger_data[j + 1];
                        sort_passenger_data[j + 1] = temp;
                    }
                }
            }
        }
        else if (sort_by_name_option == 'D' || sort_by_name_option == 'd')
        {
            for (int i = 0; i < passengerCount - 1; i++)
            {
                for (int j = 0; j < passengerCount - i - 1; j++)
                {
                    if (sort_passenger_data[j].name < sort_passenger_data[j + 1].name)
                    {
                        Passenger temp = sort_passenger_data[j];
                        sort_passenger_data[j] = sort_passenger_data[j + 1];
                        sort_passenger_data[j + 1] = temp;
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
        // Sort by surname
        std::cout << "Do you want to sort surname by ascending or descending order? (A/D): ";
        char sort_by_surname_option;
        std::cin >> sort_by_surname_option;
        std::cin.ignore();

        if (sort_by_surname_option == 'A' || sort_by_surname_option == 'a')
        {
            for (int i = 0; i < passengerCount - 1; i++)
            {
                for (int j = 0; j < passengerCount - i - 1; j++)
                {
                    if (sort_passenger_data[j].surname > sort_passenger_data[j + 1].surname)
                    {
                        Passenger temp = sort_passenger_data[j];
                        sort_passenger_data[j] = sort_passenger_data[j + 1];
                        sort_passenger_data[j + 1] = temp;
                    }
                }
            }
        }
        else if (sort_by_surname_option == 'D' || sort_by_surname_option == 'd')
        {
            for (int i = 0; i < passengerCount - 1; i++)
            {
                for (int j = 0; j < passengerCount - i - 1; j++)
                {
                    if (sort_passenger_data[j].surname < sort_passenger_data[j + 1].surname)
                    {
                        Passenger temp = sort_passenger_data[j];
                        sort_passenger_data[j] = sort_passenger_data[j + 1];
                        sort_passenger_data[j + 1] = temp;
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

    for (int i = 0; i < passengerCount; i++)
    {
        const Passenger& passenger = sort_passenger_data[i];
        std::cout << std::setfill(' ');
        std::cout << std::setw(12) << passenger.passenger_id;
        std::cout << std::setw(15) << passenger.name;
        std::cout << std::setw(15) << passenger.surname;
        std::cout << std::setw(15) << passenger.flight_number;
        std::cout << std::setw(15) << passenger.seat_number << std::endl;
    }

    std::cout << "Do you want to create a new text file with sorted passenger data? (Y/N): ";
    char create_file_option;
    std::cin >> create_file_option;

    if (create_file_option == 'Y' || create_file_option == 'y')
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the newline character from previous input

        std::string sorted_file_name;
        std::cout << "Enter the file name: ";
        std::getline(std::cin, sorted_file_name);
        sorted_file_name += ".txt";

        createPassengerDataFile(sorted_file_name, sort_passenger_data, passengerCount);
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

    delete[] sort_passenger_data;
    sort_passenger_data = nullptr;
}
