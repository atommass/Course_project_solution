#include "Flight_Functions.h"
#include "Passenger_Functions.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

#include <cstdlib> // to use system("cls"), std::rename(), std::remove();
#include <mutex> // mutual exclusion to prevent multiple threads from accessing shared resources at the same time

constexpr  int MAX_FLIGHTS = 100;
constexpr  int MAX_PASSENGERS = 500;

int numFlight = 0;
int numPassenger = 0;

void passengersOnFlight()
{
	std::cout << "Input the flight number you want to see passengers on: ";
	int flight_number;
	std::cin >> flight_number;

	Flight* flights = new Flight[MAX_FLIGHTS];
	Passenger* passengers = new Passenger[MAX_PASSENGERS];

	readFlightDataFromFile(flights, numFlight);
	readPassengerDataFromFile(passengers, numPassenger);

    bool foundFlight = false;

    for (int i = 0; i < numFlight; i++) {
        if (flights[i].flight_number == flight_number) {
            foundFlight = true;
            std::cout << "Passengers on Flight " << flight_number << std::endl << std::endl;
            std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
            std::cout << std::setw(12) << "Passenger ID" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(10) << "          " << "Date of flight" << std::setw(15) << "Destination" << std::endl;
            std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

           
            for (int j = 0; j < numPassenger; j++) {
                if (passengers[j].flight_number == flight_number) {
                    std::cout << std::setfill(' ');
                    std::cout << std::setw(12) << passengers[j].passenger_id;
                    std::cout << std::setw(15) << passengers[j].name;
                    std::cout << std::setw(15) << passengers[j].surname;

                    std::cout << std::setfill('0');
                    std::cout << "        " << std::setw(4) << flights[i].time.year << "/" << std::setw(2) << flights[i].time.month << "/" << std::setw(2) << flights[i].time.day;
                    std::cout << " " << std::setw(2) << flights[i].time.hour << ":" << std::setw(2) << flights[i].time.min;

                    std::cout << std::setfill(' ');
                    std::cout << std::setw(15) << flights[i].destination;
                    std::cout << std::endl;
                }
            }
            break;
        }
    }

    if (!foundFlight) {
        std::cout << "No flight with number " << flight_number << " found." << std::endl;
    }
    else {
        std::cout << "Do you want to create a new file to save the passenger data? (Y/N): ";
        char choice;
        std::cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            const std::string fileName = "flight_" + std::to_string(flight_number) + "_passengers.txt";
            std::ofstream outputFile(fileName);

            if (outputFile.is_open()) {
                outputFile << "Passengers on Flight " << flight_number << std::endl << std::endl;

                outputFile << "---------------------------------------------------------------------------------------------" << std::endl;
                outputFile << std::setw(12) << "Passenger ID" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(10) << "          " << "Date of flight" << std::setw(15) << "Destination" << std::endl;
                outputFile << "---------------------------------------------------------------------------------------------" << std::endl;

                for (int j = 0; j < numPassenger; j++) {
                    if (passengers[j].flight_number == flight_number) {
                        outputFile << std::setfill(' ');
                        outputFile << std::setw(12) << passengers[j].passenger_id;
                        outputFile << std::setw(15) << passengers[j].name;
                        outputFile << std::setw(15) << passengers[j].surname;

                        outputFile << std::setfill('0');
                        outputFile << "        " << std::setw(4) << flights[j].time.year << "/" << std::setw(2) << flights[j].time.month << "/" << std::setw(2) << flights[j].time.day;
                        outputFile << " " << std::setw(2) << flights[j].time.hour << ":" << std::setw(2) << flights[j].time.min;

                        outputFile << std::setfill(' ');
                        outputFile << std::setw(15) << flights[j].destination;
                        outputFile << std::endl;
                    }
                }
                outputFile.close();
                std::cout << "Passenger data written to " << fileName << std::endl;
            }
            else {
                std::cout << "Error: Unable to write to file." << std::endl;
            }
        }
    }

    delete[] flights;
    delete[] passengers;

    
}

void backupFlightData()
{
    Flight* flights = new Flight[MAX_FLIGHTS];
    readFlightDataFromFile(flights, numFlight);
    const std::string backupFileName = "flight_info_data_backup.txt";

    std::ofstream backupFile(backupFileName);

    if (backupFile.is_open())
    {
        for (int i = 0; i < numFlight; i++)
        {
            const Flight& flight = flights[i];

            backupFile << std::setfill(' ');
            backupFile << std::setw(8) << flight.flight_number;
            backupFile << std::setw(10) << flight.direction;

            backupFile << std::setfill('0');
            backupFile << std::right;
            backupFile << "          " << std::setw(4) << flight.time.year << "/" << std::setw(2) << flight.time.month << "/" << std::setw(2) << flight.time.day;
            backupFile << " " << std::setw(2) << flight.time.hour << ":" << std::setw(2) << flight.time.min;

            backupFile << std::setfill(' ');
            backupFile << std::setw(20) << flight.destination;
            backupFile << std::setw(15) << flight.plane_model;
            backupFile << std::endl;
        }

        backupFile.close();

        std::cout << "Flight data backup completed successfully." << std::endl;
    }
    else
    {
        std::cout << "Error: Unable to create backup file." << std::endl;
    }
}

void backupPassengerData()
{
	Passenger* passengers = new Passenger[MAX_PASSENGERS];
    readPassengerDataFromFile(passengers, numPassenger);

    const std::string backupFileName = "passenger_info_data_backup.txt";

    std::ofstream backupFile(backupFileName);

    if (backupFile.is_open())
    {
	    for (int i = 0; i < numPassenger; i++)
	    {
	    	const Passenger& passenger = passengers[i];

            backupFile << std::setfill(' ');
            backupFile << std::setw(12) << passenger.passenger_id;
            backupFile << std::setw(15) << passenger.name;
            backupFile << std::setw(15) << passenger.surname;
            backupFile << std::setw(15) << passenger.flight_number;
            backupFile << std::setw(15) << passenger.seat_number << std::endl;
	    }

		backupFile.close();

		std::cout << "Passenger data backup completed successfully." << std::endl;
    }
    else
    {
        std::cout << "Error: Unable to create backup file." << std::endl;
    }

}


void restoreFlightData()
{
    const std::string backupFileName = "flight_info_data_backup.txt";
    const std::string flightFileName = "flight_info_data.txt";
    const std::string tempFileName = "flight_info_data_temp.txt";

    std::ifstream backupFile(backupFileName);
    if (!backupFile.is_open())
    {
        std::cout << "Error: Unable to open backup file." << std::endl;
        return;
    }

    std::ofstream tempFile(tempFileName);
    if (!tempFile.is_open())
    {
        std::cout << "Error: Unable to create temporary file." << std::endl;
        backupFile.close();
        return;
    }

    std::string line;
    while (std::getline(backupFile, line))
    {
        tempFile << line << std::endl;
    }

    backupFile.close();
    tempFile.close();

    // Delete the main data file
    if (std::remove(flightFileName.c_str()) != 0)
    {
        std::cout << "Error: Unable to delete main data file." << std::endl;
        return;
    }

    // Rename the temporary file to the main data file name
    if (std::rename(tempFileName.c_str(), flightFileName.c_str()) != 0)
    {
        std::cout << "Error: Unable to rename temporary file to main data file name." << std::endl;
        return;
    }

    std::cout << "Flight data restored successfully." << std::endl;
}





void restorePassengerData()
{
    const std::string backupFileName = "passenger_info_data_backup.txt";
    const std::string passengerFileName = "passenger_info_data.txt";
    const std::string tempFileName = "passenger_info_data_temp.txt";

    std::ifstream backupFile(backupFileName);
    if (!backupFile.is_open())
    {
        std::cout << "Error: Unable to open backup file." << std::endl;
        return;
    }

    std::ofstream tempFile(tempFileName);
    if (!tempFile.is_open())
    {
        std::cout << "Error: Unable to create temporary file." << std::endl;
        backupFile.close();
        return;
    }

    std::string line;
    while (std::getline(backupFile, line))
    {
        tempFile << line << std::endl;
    }

    backupFile.close();
    tempFile.close();

    // Delete the main data file
    if (std::remove(passengerFileName.c_str()) != 0)
    {
        std::cout << "Error: Unable to delete main data file." << std::endl;
        return;
    }

    // Rename the temporary file to the main data file name
    if (std::rename(tempFileName.c_str(), passengerFileName.c_str()) != 0)
    {
        std::cout << "Error: Unable to rename temporary file to main data file name." << std::endl;
        return;
    }

    std::cout << "Passenger data restored successfully." << std::endl;
}




void calculateTimeUntilFlight(int passengerID, Flight::DateAndTime currentTime)
{
	Passenger* passengers = new Passenger[MAX_PASSENGERS];
    readPassengerDataFromFile(passengers, numPassenger);

    Flight* flights = new Flight[MAX_FLIGHTS];
    readFlightDataFromFile(flights, numFlight);

    int found_passenger_index = -1;
    for (int i = 0; i < numPassenger; i++)
    {
        if (passengers[i].passenger_id == passengerID)
        {
            found_passenger_index = i;
            break;
        }
    }

    const int found_flight_number = passengers[found_passenger_index].flight_number;

    int found_flight_index = -1;
    for (int i = 0; i < numFlight; i++)
    {
    	if (flights[i].flight_number == found_flight_number)
	    {
	    	found_flight_index = i;
			break;
		}
	}
    

    // Calculate the difference between the current time and the flight time
    if (found_flight_index != -1)
    {
        const Flight::DateAndTime flightTime = flights[found_flight_index].time;

        const int year_diff = flightTime.year - currentTime.year;
        const int month_diff = flightTime.month - currentTime.month;
        const int days_diff = flightTime.day - currentTime.day;
        const int hours_diff = flightTime.hour - currentTime.hour;
        const int minutes_diff = flightTime.min - currentTime.min;

        //Convert all to minutes
        const int total_minutes = year_diff * 525600 + month_diff * 43800 + days_diff * 1440 + hours_diff * 60 + minutes_diff;

        if (total_minutes >= 0)
        {
            const int days = total_minutes / 1440;
            const int hours = (total_minutes % 1440) / 60;
            const int minutes = (total_minutes % 1440) % 60;
            std::cout << "Time until flight: " << days << " days, " << hours << " hours, " << minutes << " minutes." << std::endl;
        }
        else
        {
            std::cout << std::endl;
        	std::cout << "Flight has already departed." << std::endl;
		}
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Passenger ID not found." << std::endl;
    }

    delete[] passengers;
    delete[] flights;

    
}
