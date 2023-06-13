#pragma once
#include "DataTypes.h"

// Date and time functions
std::string addDate();
Flight::DateAndTime add_date_and_time();

void readPassengerDataFromFile(Passenger passengers[], int& numPassenger);
void viewPassengerData();

