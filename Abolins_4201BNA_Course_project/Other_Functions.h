#pragma once

#pragma once
#include "DataTypes.h"

void passengersOnFlight();
void backupFlightData();
void backupPassengerData();
void restoreFlightData();
void restorePassengerData();
void calculateTimeUntilFlight(int passengerID, Flight::DateAndTime currentTime);
