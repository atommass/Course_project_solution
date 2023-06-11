#pragma once
#include "DataTypes.h"

// Date and time functions
std::string addDate();
Flight::DateAndTime add_date_and_time();

// Data input / output functions
// 1. Flight Data functions
void readFlightDataFromFile(Flight flights[], int& numFlight);
void viewFlightData();
void addFlightData();
void writeStructureToFile(Flight* flights, int n);

// Clear console
void clear_console();