#include "DataTypes.h"
#include "Flight_Functions.h"
#include "Passenger_Functions.h"
#include "Other_Functions.h"
#include <string>
#include <iostream>
#include <fstream>


int main()
{
	std::cout << "**********************************" << std::endl;
	std::cout << "  WELCOME TO AIRPORT MANAGEMENT!" << std::endl;
	std::cout << "**********************************" << std::endl;
	std::cout << std::endl;

    int main_menu_choice = 0;

    while (true) {
        std::cout << "Main Menu" << std::endl;
        std::cout << "1. View Data" << std::endl;
        std::cout << "2. Add Data" << std::endl;
        std::cout << "3. Sort Data" << std::endl;
        std::cout << "4. Search Data" << std::endl;
        std::cout << "5. Filter Data" << std::endl;
        std::cout << "6. Edit Data" << std::endl;
        std::cout << "7. Delete Data" << std::endl;
        std::cout << "8. Additional Options" << std::endl;
        std::cout << "9. Exit" << std::endl << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> main_menu_choice;
        std::cout << std::endl << std::endl;

        if (main_menu_choice == 1) {

           
            std::cout << "Select data you want to view:" << std::endl;
            std::cout << "1. Flight data" << std::endl;
            std::cout << "2. Passengers" << std::endl;
            
            int view_choice;
            std::cout << "Enter your choice (1 or 2): ";
            std::cin >> view_choice;

            clear_console();

            if (view_choice == 1)
            {
				viewFlightData();
			}
            else if (view_choice == 2)
			{
				viewPassengerData();
			}
            else
			{
				std::cout << "Invalid input!" << std::endl;
                clear_console();
			}
        }
        else if (main_menu_choice == 2) {
            std::cout << "Select data you want to add:" << std::endl;
            std::cout << "1. Flight data" << std::endl;
            std::cout << "2. Passengers" << std::endl;

            int add_choice;
            std::cout << "Enter your choice: ";
            std::cin >> add_choice;

            clear_console();
            if (add_choice == 1)
            {
                addFlightData();
                
            }
            else if (add_choice == 2) 
            {
                addPassengerData();
               
            }
			else
			{
				std::cout << "Invalid input!" << std::endl;
				clear_console();
				continue;
			}
        	
        }
        else if (main_menu_choice == 3) {
            std::cout << "Select data you want to sort (1 or 2):" << std::endl;
            std::cout << "1. Flight data" << std::endl;
            std::cout << "2. Passengers" << std::endl;

            int sort_choice;
            std::cout << "Enter your choice: ";
            std::cin >> sort_choice;

            clear_console();

            if (sort_choice == 1)
            {
	           sortFlightData();
               
            }
            else if (sort_choice == 2)
            {
            	sortPassengerData();
                
			}
			else
			{
				std::cout << "Invalid input!" << std::endl;
	            clear_console();
	            continue;
			}
            
        }
        else if (main_menu_choice == 4) {
            std::cout << "Select data you want to search in (1 or 2):" << std::endl;
            std::cout << "1. Flight data" << std::endl;
            std::cout << "2. Passengers" << std::endl;

            int search_choice;
            std::cout << "Enter your choice: ";
            std::cin >> search_choice;

            clear_console();

            if (search_choice == 1)
            {
                
                searchFlightData();
               
            }
            else if (search_choice == 2)
            {
               
                searchPassengerData();
               
			}
			else
			{
				std::cout << "Invalid input!" << std::endl;
				clear_console();
				continue;
			}
        }
        else if (main_menu_choice == 5) 
        {
            std::cout << "Select data you want to filter (1 or 2):" << std::endl;
            std::cout << "1. Flight data" << std::endl;
            std::cout << "2. Passengers" << std::endl;
           
            int filter_choice;
            std::cout << "Enter your choice: ";
            std::cin >> filter_choice;

            clear_console();
            if (filter_choice == 1)
            {
              
            	filterFlightData();
                
			}
			else if (filter_choice == 2)
			{
              
				filterPassengerData();
                
			}
            else
			{
				std::cout << "Invalid input!" << std::endl;
	            clear_console();
	            continue;
			}
        }
        else if (main_menu_choice == 6) 
        {
            std::cout << "Select data you want to edit (1 or 2):" << std::endl;
            std::cout << "1. Flight data" << std::endl;
            std::cout << "2. Passengers" << std::endl;
            
            int edit_choice;
            std::cout << "Enter your choice: ";
            std::cin >> edit_choice;

            clear_console();

            if (edit_choice == 1)
            {
              
            	editFlightData();
              
			}
			else if (edit_choice == 2)
			{
			
				editPassengerData();

			}
            else
            {
            	std::cout << "Invalid input!" << std::endl;
				clear_console();
				continue;
            }
            
        }
		else if (main_menu_choice == 7)
		{
            clear_console();
			std::cout << "Select data you want to delete (1 or 2):" << std::endl;
            std::cout << "1. Flight data" << std::endl;
            std::cout << "2. Passengers" << std::endl;
            
            int delete_menu_choice;
            std::cout << "Enter your choice: ";
            std::cin >> delete_menu_choice;

            if (delete_menu_choice == 1)
            {
                clear_console();
                std::cout << "Select delete method: " << std::endl;
                std::cout << "1. Delete single flight data" << std::endl;
                std::cout << "2. Delete all flight data" << std::endl;
                std::cout << "3. Delete filtered flight data" << std::endl;
                std::cout << "Enter your choice: ";
                int delete_flight_data_choice;
                std::cin >> delete_flight_data_choice;

                if (delete_flight_data_choice == 1)
                {
            
                	deleteSingleFlightData();
                    std::cin.ignore();
                    clear_console();
				}
				else if (delete_flight_data_choice == 2)
				{
           
					deleteAllFlightData();
                    std::cin.ignore();
                    clear_console();
				}
				else if (delete_flight_data_choice == 3)
				{
	
					deleteFilteredFlightData();
                    std::cin.ignore();
                    clear_console();
				}
				else
				{
					std::cout << "Invalid input!" << std::endl;
					clear_console();
					continue;
				}
			}
			else if (delete_menu_choice == 2)
			{
                clear_console();
                std::cout << "Select delete method: " << std::endl;
                std::cout << "1. Delete single passenger data" << std::endl;
                std::cout << "2. Delete all passenger data" << std::endl;
                std::cout << "3. Delete filtered passenger data" << std::endl;
                std::cout << "Enter your choice: ";
                int delete_passenger_data_choice;
                std::cin >> delete_passenger_data_choice;

                if (delete_passenger_data_choice == 1)
                {
               
					deleteSinglePassenger();
                    std::cin.ignore();
                    clear_console();
                }
                else if (delete_passenger_data_choice == 2)
                {
         
					deleteAllPassengers();
                    std::cin.ignore();
                    clear_console();
				}
				else if (delete_passenger_data_choice == 3)
				{
			
					deleteFilteredPassengers();
                    std::cin.ignore();
                    clear_console();
				}
				else
				{
					std::cout << "Invalid input!" << std::endl;
					clear_console();
					continue;
				}
			}
			else
			{
				std::cout << "Invalid input!" << std::endl;
				clear_console();
				continue;
			}

		}
        else if (main_menu_choice == 8)
        {
            // Additional features
            std::cout << "Select the action you want to do: " << std::endl;
            std::cout << "1. See passengers on a flight" << std::endl;
            std::cout << "2. Perform data backup" << std::endl;
            std::cout << "3. Restore from backup" << std::endl;
            std::cout << "4. See time until flight" << std::endl;

            int additional_features_choice;
            std::cout << "Enter your choice: ";
            std::cin >> additional_features_choice;

            if (additional_features_choice == 1)
            {
            	clear_console();
				passengersOnFlight();
                std::cin.ignore();
                clear_console();
            }
            else if (additional_features_choice == 2)
            {
            	clear_console();
                // Preform data backup
                std::cout << "Which data do you want to back up?" << std::endl;
                std::cout << "1. Flight Data" << std::endl;
                std::cout << "2. Passenger Data" << std::endl;
                std::cout << "3. Both" << std::endl;

                std::cout << "Enter your choice: ";
                int userChoice;
                std::cin >> userChoice;

                if (userChoice == 1)
                {
                    backupFlightData();
                    std::cin.ignore();
                    clear_console();
                }
                else if (userChoice == 2)
                {
                    backupPassengerData();
                    std::cin.ignore();
                    clear_console();
                }
                else if (userChoice == 3)
                {
                    backupFlightData();
                    backupPassengerData();
                    std::cin.ignore();
                    clear_console();
                }
				else
				{
					std::cout << "Invalid input!" << std::endl;
					std::cin.ignore();
					clear_console();
					continue;
				}

            }
            else if (additional_features_choice == 3)
            {
                clear_console();
                std::cout << "Which data do you want to restore?" << std::endl;
                std::cout << "1. Flight Data" << std::endl;
                std::cout << "2. Passenger Data" << std::endl;
                std::cout << "3. Both" << std::endl;

                std::cout << "Enter your choice: ";
                int userChoice;
                std::cin >> userChoice;

                if (userChoice == 1)
                {
                	restoreFlightData();
					std::cin.ignore();
					clear_console();
				}
				else if (userChoice == 2)
				{
					restorePassengerData();
					std::cin.ignore();
					clear_console();
				}
				else if (userChoice == 3)
				{
					restoreFlightData();
					restorePassengerData();
					std::cin.ignore();
					clear_console();
                }
                else
                {
                    std::cout << "Invalid input!" << std::endl;
                    std::cin.ignore();
                    clear_console();
                    continue;
                }

            }
            else if (additional_features_choice == 4)
            {
				clear_console();
                std::cout << "Time until selected passenger's flight." << std::endl << std::endl;
	            // See time until selected passengers flight
                std::cout << "Enter selected passenger's ID number: ";
                int selected_passengerID;
                std::cin >> selected_passengerID;

                std::cout << std::endl;

                std::cout << "Enter current date and time (DD/MM/YYYY HH:MM): ";
                Flight::DateAndTime current_date_and_time = add_date_and_time();

                calculateTimeUntilFlight(selected_passengerID, current_date_and_time);

                std::cin.ignore();
                clear_console();

            }
            else
            {
                std::cout << "Invalid input!";
                std::cin.ignore();
                clear_console();
                continue;
            }



		}
        else if (main_menu_choice == 9) {
            std::cout << "Are you sure you want to terminate the program? (Y/N): ";
            std::string terminate_choice;
            std::cin >> terminate_choice;
            if (terminate_choice == "Y" || terminate_choice == "y") {
                std::cout << "Exiting the program..." << std::endl;
                break; 
            }
            else {
                std::cout << "Returning to the main menu..." << std::endl;
                clear_console();
                continue;  
            }
        }
        else {
            std::cout << "Invalid input!" << std::endl;
            clear_console();
        }
    }

    std::cout << "Goodbye!" << std::endl;



	

	return 0;
}