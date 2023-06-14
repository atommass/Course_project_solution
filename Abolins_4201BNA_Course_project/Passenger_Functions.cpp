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
        output_file << "---------------------------------------------------------------------------------------------" << std::endl;
        output_file << std::setw(12) << "Passenger ID" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(15) << "Flight No." << std::setw(15) << "Seat No." << std::endl;
        output_file << "---------------------------------------------------------------------------------------------" << std::endl;

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
		std::cout << "File created successfully. Press ENTER!" << std::endl;
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

void searchPassengerData()
{
    Passenger* search_passenger_data = new Passenger[MAX_PASSENGERS];
    readPassengerDataFromFile(search_passenger_data, passengerCount);

    std::cout << "Select the search method: " << std::endl;
    std::cout << "1. Search by Passenger ID" << std::endl;
    std::cout << "2. Search by name" << std::endl;
    std::cout << "3. Search by surname" << std::endl;

    int search_method;
    std::cout << "Enter the number of the search method: ";
    std::cin >> search_method;
    std::cin.ignore(); // Ignore the newline character left in the input stream

    std::cout << std::endl;

    switch (search_method)
    {
    case 1:
    {
        // Search by Passenger ID
        int passenger_id;
        std::cout << "Enter the passenger ID to search: ";
        std::cin >> passenger_id;
        std::cin.ignore(); // Ignore the newline character left in the input stream

        bool found = false;

        std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(12) << "Passenger ID" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(15) << "Flight No." << std::setw(15) << "Seat No." << std::endl;
        std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < passengerCount; i++)
        {
            if (search_passenger_data[i].passenger_id == passenger_id)
            {
                found = true;
                const Passenger& passenger = search_passenger_data[i];
                std::cout << std::setfill(' ');
                std::cout << std::setw(12) << passenger.passenger_id;
                std::cout << std::setw(15) << passenger.name;
                std::cout << std::setw(15) << passenger.surname;
                std::cout << std::setw(15) << passenger.flight_number;
                std::cout << std::setw(15) << passenger.seat_number << std::endl;
            }
        }

        if (!found)
        {
            std::cout << "Passenger ID not found!" << std::endl;
        }
        break;
    }
    case 2:
    {
        std::string name;
        std::cout << "Enter the name to search: ";
        std::getline(std::cin, name);

        bool found = false;

        std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(12) << "Passenger ID" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(15) << "Flight No." << std::setw(15) << "Seat No." << std::endl;
        std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < passengerCount; i++)
        {
            if (search_passenger_data[i].name == name)
            {
                found = true;
                const Passenger& passenger = search_passenger_data[i];
                std::cout << std::setfill(' ');
                std::cout << std::setw(10) << passenger.passenger_id;
                std::cout << std::setw(15) << passenger.name;
                std::cout << std::setw(15) << passenger.surname;
                std::cout << std::setw(15) << passenger.flight_number;
                std::cout << std::setw(15) << passenger.seat_number << std::endl;
            }
        }

        if (!found)
        {
            std::cout << "Name not found!" << std::endl;
        }
        break;
    }
    case 3:
    {
        std::string surname;
        std::cout << "Enter the surname to search: ";
        std::getline(std::cin, surname);

        bool found = false;

        std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(12) << "Passenger ID" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(15) << "Flight No." << std::setw(15) << "Seat No." << std::endl;
        std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < passengerCount; i++)
        {
            if (search_passenger_data[i].surname == surname)
            {
                found = true;
                const Passenger& passenger = search_passenger_data[i];
                std::cout << std::setfill(' ');
                std::cout << std::setw(12) << passenger.passenger_id;
                std::cout << std::setw(15) << passenger.name;
                std::cout << std::setw(15) << passenger.surname;
                std::cout << std::setw(15) << passenger.flight_number;
                std::cout << std::setw(15) << passenger.seat_number << std::endl;
            }
        }

        if (!found)
        {
            std::cout << "Surname not found!" << std::endl;
        }
        break;
    }
    default:
        std::cout << "Invalid input!" << std::endl;
        break;
    }

    delete[] search_passenger_data;

    clear_console();
}


void filterPassengerData()
{
    Passenger* filter_passenger_data = new Passenger[MAX_PASSENGERS];
    int numPassengers = 0;
    int filter_passenger_count = 0;
    readPassengerDataFromFile(filter_passenger_data, numPassengers);

    std::cout << "Available filters:" << std::endl;
    std::cout << "1. Flight number" << std::endl;
    std::cout << "2. Name" << std::endl;
    std::cout << "3. Surname" << std::endl;
    std::cout << std::endl;

    int filter_flight_number = 0;
    std::string filter_name = {};
    std::string filter_surname = {};

    std::cout << "How many filters do you want to apply? " << std::endl;
    int filter_count = 0;
    std::cout << "Enter the count of filters (MAX 3 filters): ";
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
            if (filter_input < 1 || filter_input > 3) {
                std::cout << "Invalid filter number entered! Please enter a filter number from 1 to 3: ";
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
    std::cout << "Input necessary data for the selected filters below!" << std::endl;
    std::cout << "Selected filters: " << std::endl;

    for (int i = 0; i < filter_count; i++)
    {
        if (filterSelection[i] == 1)
        {
            std::cout << "Flight Number: ";
            std::cin >> filter_flight_number;
        }
        else if (filterSelection[i] == 2)
        {
            std::cout << "Name: ";
            std::cin.ignore();
            std::getline(std::cin, filter_name);
        }
        else if (filterSelection[i] == 3)
        {
            std::cout << "Surname: ";
            std::cin.ignore();
            std::getline(std::cin, filter_surname);
        }
    }

    bool found = false;

    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(12) << "Passenger ID" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(15) << "Flight No." << std::setw(15) << "Seat No." << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

    for (int i = 0; i < numPassengers; i++)
    {
        const Passenger& passenger = filter_passenger_data[i];

        // Check if the passenger matches the selected filters
        if ((filter_flight_number == 0 || passenger.flight_number == filter_flight_number) &&
            (filter_name.empty() || passenger.name == filter_name) &&
            (filter_surname.empty() || passenger.surname == filter_surname))
        {
            found = true;
            std::cout << std::setfill(' ');
            std::cout << std::setw(12) << passenger.passenger_id;
            std::cout << std::setw(15) << passenger.name;
            std::cout << std::setw(15) << passenger.surname;
            std::cout << std::setw(15) << passenger.flight_number;
            std::cout << std::setw(15) << passenger.seat_number << std::endl;
        }
    }

    if (!found)
    {
        std::cout << "No passengers found matching the filter criteria!" << std::endl;
    }

    int nextAvailableIndex = 0;

    for (int i = 0; i < numPassengers; i++)
    {
    	const Passenger& passenger = filter_passenger_data[i];

		// Check if the passenger matches the selected filters
		if ((filter_flight_number == 0 || passenger.flight_number == filter_flight_number) &&
		(filter_name.empty() || passenger.name == filter_name) &&
		(filter_surname.empty() || passenger.surname == filter_surname))
		{
			filter_passenger_data[nextAvailableIndex] = passenger;
			nextAvailableIndex++;
		}
	}

    // Update the number of flights to the new count
    filter_passenger_count = nextAvailableIndex;

    // Copy the filtered flights back to the original array
    numPassengers = filter_passenger_count;
    for (int i = 0; i < filter_passenger_count; i++) {
        filter_passenger_data[i] = filter_passenger_data[i];
    }

    std::cout << "Do you want to create a new text file with filtered passenger data? (Y/N): ";
    char create_file_option;
    std::cin >> create_file_option;

    if (create_file_option == 'Y' || create_file_option == 'y')
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the newline character from previous input

        std::string filtered_file_name;
        std::cout << "Enter the file name: ";
        std::getline(std::cin, filtered_file_name);
        filtered_file_name += ".txt";

        createPassengerDataFile(filtered_file_name, filter_passenger_data, numPassengers);
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

    delete[] filter_passenger_data;
    delete[] filterSelection;

}

void editPassengerData()
{
    passengerCount = 0;
    Passenger* edit_passenger_data = new Passenger[MAX_PASSENGERS];
    readPassengerDataFromFile(edit_passenger_data, passengerCount);
    std::cout << "Available Passenger data for editing." << std::endl << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(12) << "Passenger ID" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(15) << "Flight No." << std::setw(15) << "Seat No." << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

    for (int i = 0; i < passengerCount; i++)
    {
        const Passenger& passenger = edit_passenger_data[i];
        std::cout << std::setfill(' ');
        std::cout << std::setw(12) << passenger.passenger_id;
        std::cout << std::setw(15) << passenger.name;
        std::cout << std::setw(15) << passenger.surname;
        std::cout << std::setw(15) << passenger.flight_number;
        std::cout << std::setw(15) << passenger.seat_number << std::endl;

    }
    std::cout << std::endl;
    int passenger_number;
    std::cout << "Enter the passenger ID number you want to edit: ";
    std::cin >> passenger_number;

    clear_console();

    int passenger_index = -1;
    for (int i = 0; i < passengerCount; i++)
    {
        if (edit_passenger_data[i].passenger_id == passenger_number)
        {
            passenger_index = i;
            break;
        }
    }

    if (passenger_index == -1)
    {
        std::cout << "Flight not found!" << std::endl;
        delete[] edit_passenger_data;
        return;
    }

    std::cout << "Passenger data before editing:" << std::endl;
    const Passenger& passenger = edit_passenger_data[passenger_index];
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(12) << "Passenger ID" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(15) << "Flight No." << std::setw(15) << "Seat No." << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << std::setw(12) << passenger.passenger_id;
    std::cout << std::setw(15) << passenger.name;
    std::cout << std::setw(15) << passenger.surname;
    std::cout << std::setw(15) << passenger.flight_number;
    std::cout << std::setw(15) << passenger.seat_number << std::endl;

    std::cout << "Do you want to edit the selected passenger data (Y/N): ";
    char edit_choice;
    std::cin >> edit_choice;

    if (edit_choice == 'Y' || edit_choice == 'y') {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the newline character from previous input

        // New flight data input
    	std::cout << "Enter passenger ID: ";
        std::cin >> edit_passenger_data[passenger_index].passenger_id;
        std::cin.ignore();

        std::cout << "Enter passenger name: ";
        std::getline(std::cin, edit_passenger_data[passenger_index].name);

        std::cout << "Enter passenger surname: ";
        std::getline(std::cin, edit_passenger_data[passenger_index].surname);

        std::cout << "Enter flight number: ";
        std::cin >> edit_passenger_data[passenger_index].flight_number;
        std::cin.ignore();

        std::cout << "Enter seat number: ";
        std::getline(std::cin, edit_passenger_data[passenger_index].seat_number);

        std::cout << std::endl;

        std::cout << "Do you want to rewrite the data in the original file (Y/N): ";
        char rewrite_choice;
        std::cin >> rewrite_choice;

        if (rewrite_choice == 'Y' || rewrite_choice == 'y') {
            std::ofstream passenger_data_file("passenger_info_data.txt", std::ios::out | std::ios::trunc);

            if (!passenger_data_file)
            {
                std::cerr << "Failed to open the file for writing!" << std::endl;
                delete[] edit_passenger_data;
                return;
            }

            // Write updated flight data to the file

            for (int i = 0; i < passengerCount; i++)
            {
                const Passenger& passenger = edit_passenger_data[i];
                passenger_data_file << std::setfill(' ');
                passenger_data_file << std::setw(12) << passenger.passenger_id;
                passenger_data_file << std::setw(15) << passenger.name;
            	passenger_data_file << std::setw(15) << passenger.surname;
				passenger_data_file << std::setw(15) << passenger.flight_number;
				passenger_data_file << std::setw(15) << passenger.seat_number << std::endl;

            }

            passenger_data_file.close();

            std::cout << "Passenger data updated and rewritten successfully!" << std::endl;
        }
        else {
            std::cout << "Passenger data updated successfully!" << std::endl;
        }

        clear_console();

    }
    else
    {
        std::cin.ignore();
        std::cout << "Exit to MAIN MENU!" << std::endl;
        clear_console();
    }

    delete[] edit_passenger_data;
}


void deleteSinglePassenger()
{
		passengerCount = 0;
	Passenger* delete_passenger_data = new Passenger[MAX_PASSENGERS];
	readPassengerDataFromFile(delete_passenger_data, passengerCount);
	std::cout << "Available Passenger data for deleting." << std::endl << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(12) << "Passenger ID" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(15) << "Flight No." << std::setw(15) << "Seat No." << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

	for (int i = 0; i < passengerCount; i++)
	{
		const Passenger& passenger = delete_passenger_data[i];
		std::cout << std::setfill(' ');
		std::cout << std::setw(12) << passenger.passenger_id;
		std::cout << std::setw(15) << passenger.name;
		std::cout << std::setw(15) << passenger.surname;
		std::cout << std::setw(15) << passenger.flight_number;
		std::cout << std::setw(15) << passenger.seat_number << std::endl;

	}
	std::cout << std::endl;
	int passenger_number;
	std::cout << "Enter the passenger ID number you want to delete: ";
	std::cin >> passenger_number;

	clear_console();

	int passenger_index = -1;
	for (int i = 0; i < passengerCount; i++)
	{
		if (delete_passenger_data[i].passenger_id == passenger_number)
		{
			passenger_index = i;
			break;
		}
	}

	if (passenger_index == -1)
	{
		std::cout << "Flight not found!" << std::endl;
		delete[] delete_passenger_data;
		return;
	}

	std::cout << "Passenger data before deleting:" << std::endl;
	const Passenger& passenger = delete_passenger_data[passenger_index];
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(12) << "Passenger ID" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(15) << "Flight No." << std::setw(15) << "Seat No." << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

    std::cout << std::setfill(' ');
    std::cout << std::setw(12) << passenger.passenger_id;
    std::cout << std::setw(15) << passenger.name;
    std::cout << std::setw(15) << passenger.surname;
    std::cout << std::setw(15) << passenger.flight_number;
    std::cout << std::setw(15) << passenger.seat_number << std::endl;

    std::cout << "Do you want to delete the selected passenger data (Y/N): ";
    char delete_choice;
    std::cin >> delete_choice;

    if (delete_choice == 'Y' || delete_choice == 'y')
    {
    	std::ofstream temp_passenger_data_file("temp_passenger_info_data.txt", std::ios::out | std::ios::trunc);

		if (!temp_passenger_data_file)
		{
			std::cerr << "Failed to open the file for writing!" << std::endl;
			delete[] delete_passenger_data;
			return;
		}

		// Write updated flight data to the file

		for (int i = 0; i < passengerCount; i++)
		{
            if (i == passenger_index)
            {
                const Passenger& passenger = delete_passenger_data[i];
                temp_passenger_data_file << std::setfill(' ');
                temp_passenger_data_file << std::setw(12) << passenger.passenger_id;
                temp_passenger_data_file << std::setw(15) << passenger.name;
                temp_passenger_data_file << std::setw(15) << passenger.surname;
                temp_passenger_data_file << std::setw(15) << passenger.flight_number;
                temp_passenger_data_file << std::setw(15) << passenger.seat_number << std::endl;
            }
		}

        temp_passenger_data_file.close();

        if (std::remove("passenger_info_data.txt") != 0)
        {
        	std::cerr << "Error deleting file!" << std::endl;
			delete[] delete_passenger_data;
			return;
		}

        if (std::rename("temp_passenger_info_data.txt", "passenger_info_data.txt") != 0)
        {
        	std::cerr << "Error renaming file!" << std::endl;
            delete[] delete_passenger_data;
            return;
        }

		std::cout << "Passenger data deleted successfully!" << std::endl;
	}
	else
	{
		std::cin.ignore();
		std::cout << "Exit to MAIN MENU!" << std::endl;
		clear_console();
    }

    delete[] delete_passenger_data;

    clear_console();
}

void deleteAllPassengers()
{
	std::cout << "Do you want to delete all passenger data (Y/N): ";
	char delete_choice;
	std::cin >> delete_choice;

	if (delete_choice == 'Y' || delete_choice == 'y')
	{
		std::ofstream temp_passenger_data_file("temp_passenger_info_data.txt", std::ios::out | std::ios::trunc);

		if (!temp_passenger_data_file)
		{
			std::cerr << "Failed to open the file for writing!" << std::endl;
			return;
		}

		temp_passenger_data_file.close();

		if (std::remove("passenger_info_data.txt") != 0)
		{
			std::cerr << "Error deleting file!" << std::endl;
			return;
		}

		if (std::rename("temp_passenger_info_data.txt", "passenger_info_data.txt") != 0)
		{
			std::cerr << "Error renaming file!" << std::endl;
			return;
		}

		std::cout << "All passenger data deleted successfully!" << std::endl;
	}
	else
	{
        std::cout << "Passenger data deletion canceled!" << std::endl;
		std::cin.ignore();
		std::cout << "Exit to MAIN MENU!" << std::endl;
		clear_console();
	}

    clear_console();
}

void deleteFilteredPassengers()
{
	Passenger* delete_passenger_data = new Passenger[MAX_PASSENGERS];
    passengerCount = 0;
    int filter_delete_passenger_count = 0;
    readPassengerDataFromFile(delete_passenger_data, passengerCount);

    std::cout << "Available filters for passenger data:" << std::endl;
    std::cout << "1. Flight number" << std::endl;
    std::cout << "2. Seat number" << std::endl;
    std::cout << "3. Surname" << std::endl;
    std::cout << std::endl;

    int filter_delete_flight_number = 0;
    std::string filter_delete_seat_number = {};
    std::string filter_delete_surname = {};

    std::cout << "How many filters do you want to apply? ";
    int filter_count = 0;
    std::cout << "Enter the count of filters (MAX 3 filters): ";
    std::cin >> filter_count;

    std::cout << std::endl;

    int* filter_delete_selection = new int[filter_count];
    std::set<int> filter_delete_selection_set;

    for (int i = 0; i < filter_count; i++)
    {
    	std::cout << "Enter the filter number " + i + 1 << ": ";
		int filter_delete_selection_input = 0;
        while (true)
        {
            std::cin >> filter_delete_selection_input;
        	if (filter_delete_selection_input < 1 || filter_delete_selection_input > 3)
        	{
	        	std::cout << "Invalid filter number! Please enter a valid filter number: ";
							}
            else if (filter_delete_selection_set.count(filter_delete_selection_input) > 0)
            {
                std::cout << "The same filter number has already been entered! Please enter a different filter number: ";
            }
			else
			{
                filter_delete_selection_set.insert(filter_delete_selection_input);
				break;
			}
		}
        filter_delete_selection[i] = filter_delete_selection_input;
	}

    std::cout << std::endl;
    std::cout << "Input necessary data for the selected filters below!" << std::endl;
    std::cout << "Selected filters: " << std::endl;

    for (int i = 0; i < filter_count; i++)
    {
        if (filter_delete_selection[i] == 1)
        {
            std::cout << "Flight Number: ";
            std::cin >> filter_delete_flight_number;
        }
        else if (filter_delete_selection[i] == 2)
        {
            std::cout << "Seat number: ";
            std::cin.ignore();
            std::getline(std::cin, filter_delete_seat_number);
        }
        else if (filter_delete_selection[i] == 3)
        {
            std::cout << "Surname: ";
            std::cin.ignore();
            std::getline(std::cin, filter_delete_surname);
        }
    }

    bool found = false;

    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(12) << "Passenger ID" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(15) << "Flight No." << std::setw(15) << "Seat No." << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

    for (int i = 0; i < passengerCount; i++)
    {
        const Passenger& passenger = delete_passenger_data[i];

        // Check if the passenger matches the selected filters
        if ((filter_delete_flight_number == 0 || passenger.flight_number == filter_delete_flight_number) &&
            (filter_delete_seat_number.empty() || passenger.seat_number == filter_delete_seat_number) &&
            (filter_delete_surname.empty() || passenger.surname == filter_delete_surname))
        {
            found = true;
            std::cout << std::setfill(' ');
            std::cout << std::setw(12) << passenger.passenger_id;
            std::cout << std::setw(15) << passenger.name;
            std::cout << std::setw(15) << passenger.surname;
            std::cout << std::setw(15) << passenger.flight_number;
            std::cout << std::setw(15) << passenger.seat_number << std::endl;
        }
    }

    int passenger_index = -1;
    for (int i = 0; i < passengerCount; i++)
    {
        if (delete_passenger_data[i].flight_number = filter_delete_flight_number)
        {
	        passenger_index = i;
			break;
        }
	}

    if (!found)
    {
        std::cout << "No passengers found matching the filter criteria!" << std::endl;
    }

    int next_passenger_index = 0;
    for (int i = 0; i < passengerCount; i++)
    {
        const Passenger& passenger = delete_passenger_data[i];

        if ((filter_delete_flight_number == 0 || passenger.flight_number == filter_delete_flight_number) &&
            (filter_delete_seat_number.empty() || passenger.seat_number == filter_delete_seat_number) &&
            (filter_delete_surname.empty() || passenger.surname == filter_delete_surname))
        {
            delete_passenger_data[next_passenger_index] = passenger;
            next_passenger_index++;
        	found = true;
        }
		
	}

    filter_delete_passenger_count = next_passenger_index;
    passengerCount = filter_delete_passenger_count;
    for (int i = 0; i < filter_delete_passenger_count; i++)
    {
        delete_passenger_data[i] = delete_passenger_data[i];
	}

    std::cout << "Do you want to delete the filtered passengers? (Y/N): ";
    char delete_passenger_choice;
    std::cin >> delete_passenger_choice;

    if (delete_passenger_choice == 'Y' || delete_passenger_choice == 'y')
    {
    	std::ofstream temp_delete_passenger_file("temp_passenger_info_data.txt", std::ios::out | std::ios::trunc);

		if (!temp_delete_passenger_file)
		{
			std::cerr << "Error opening temporary data file!" << std::endl;
            delete[] delete_passenger_data;
            return;
		}

        for (int i = 0; i < passengerCount; i++)
        {
	        if (i != passenger_index)
	        {
                const Passenger& passenger = delete_passenger_data[i];
	        	temp_delete_passenger_file << delete_passenger_data[i].passenger_id << std::endl;
		        temp_delete_passenger_file << delete_passenger_data[i].name << std::endl;
		        temp_delete_passenger_file << delete_passenger_data[i].surname << std::endl;
		        temp_delete_passenger_file << delete_passenger_data[i].flight_number << std::endl;
		        temp_delete_passenger_file << delete_passenger_data[i].seat_number << std::endl;
	        }
        }
		
        temp_delete_passenger_file.close();

        if (std::remove("passenger_info_data.txt") != 0)
        {
        	std::cerr << "Error deleting passenger_info_data.txt!" << std::endl;
			delete[] delete_passenger_data;
			return;
		}

        if (std::rename("temp_passenger_info_data.txt", "passenger_info_data.txt") != 0)
        {
        	std::cerr << "Error renaming temp_passenger_info_data.txt!" << std::endl;
			delete[] delete_passenger_data;
			return;
		}

        delete[] delete_passenger_data;

		std::cout << "Passengers that match selected filters deleted successfully!" << std::endl;

        clear_console();
	}
	else 
    {
		std::cout << "Passengers not deleted!" << std::endl;
        delete[] delete_passenger_data;
        clear_console();

		return;
	}

}