#pragma once
#include <string>


struct Flight
{
	int flight_number{};
	std::string destination;
	std::string direction;
	struct DateAndTime
	{
		int year;
		int month;
		int day;
		int hour;
		int min;
	};
	DateAndTime time{};
	std::string plane_model;
};

struct Passenger
{
	int passenger_id{};
	std::string name;
	std::string surname;
	int flight_number{};
	std::string seat_number;
};
