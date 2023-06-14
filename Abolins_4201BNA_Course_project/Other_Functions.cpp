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

    //clear_console();
}