#pragma once
#include "DataTypes.h"

// Date and time functions
std::string addDate();
Flight::DateAndTime add_date_and_time();

void readPassengerDataFromFile(Passenger passengers[], int& numPassenger);
void viewPassengerData();
void addPassengerData();
void writePassengerStructureToFile(Passenger* passengers, int n);
void createPassengerDataFile(const std::string& sorted_file_name, const Passenger* sorted_passenger_data, int numPassengers);
void sortPassengerData();
void searchPassengerData();
void filterPassengerData();
void editPassengerData();



