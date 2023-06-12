#include "DataTypes.h"
#include "Flight_Functions.h"
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
        std::cout << "8. Exit" << std::endl << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> main_menu_choice;
        std::cout << std::endl << std::endl;

        if (main_menu_choice == 1) {

           
            std::cout << "Select data you want to view:" << std::endl;
            std::cout << "1. Flight data" << std::endl;
            std::cout << "2. Passengers" << std::endl;
            std::cout << "3. Planes" << std::endl;

            int view_choice;
            std::cout << "Enter your choice (1, 2 or 3): ";
            std::cin >> view_choice;

            clear_console();

            if (view_choice == 1)
				{
					// View flight data
					viewFlightData();
				}
            else if (view_choice == 2)
				{
					// View passengers
				}
            else if (view_choice == 3)
				{
					// View planes
				}
            else
				{
					std::cout << "Invalid input!" << std::endl;
                    clear_console();
				}
        }
        else if (main_menu_choice == 2) {
            addFlightData();
        }
        else if (main_menu_choice == 3) {
            std::cout << "Select data you want to sort (1, 2 or 3):" << std::endl;
            std::cout << "1. Flight data" << std::endl;
            std::cout << "2. Passengers" << std::endl;
            std::cout << "3. Planes" << std::endl;

            int sort_choice;
            std::cout << "Enter your choice: ";
            std::cin >> sort_choice;

            clear_console();

            if (sort_choice == 1)
            {
	            // Sort flight data
                sortFlightData();
            }
            else if (sort_choice == 2)
            {
            	// Sort passengers
			}
			else if (sort_choice == 3)
			{
				// Sort planes
			}
			else
			{
				std::cout << "Invalid input!" << std::endl;
	            clear_console();
	            continue;
			}
            
        }
        else if (main_menu_choice == 4) {
            std::cout << "Select data you want to search in (1, 2 or 3):" << std::endl;
            std::cout << "1. Flight data" << std::endl;
            std::cout << "2. Passengers" << std::endl;
            std::cout << "3. Planes" << std::endl;

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
            	// Search passengers
			}
			else if (search_choice == 3)
			{
				// Search planes
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
            clear_console();
            filterFlightData();
        }
        else if (main_menu_choice == 6) 
        {
            clear_console();
            editFlightData();
        }
		else if (main_menu_choice == 7)
		{
            clear_console();
			std::cout << "Select data you want to delete (1, 2 or 3):" << std::endl;
            std::cout << "1. Flight data" << std::endl;
            std::cout << "2. Passengers" << std::endl;
            std::cout << "3. Planes" << std::endl;

            int delete_menu_choice;
            std::cout << "Enter your choice: ";
            std::cin >> delete_menu_choice;

            if (delete_menu_choice == 1)
            {
                clear_console();
                std::cout << "Select delete method: ";
                std::cout << "1. Delete single flight data" << std::endl;
                std::cout << "2. Delete all flight data" << std::endl;
                std::cout << "3. Delete filtered flight data" << std::endl;
                std::cout << "Enter your choice: ";
                int delete_flight_data_choice;
                std::cin >> delete_flight_data_choice;

                if (delete_flight_data_choice == 1)
                {
                	deleteSingleFlightData();
				}
				else if (delete_flight_data_choice == 2)
				{
					//deleteAllFlightData();
				}
				else if (delete_flight_data_choice == 3)
				{
					//deleteFilteredFlightData();
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
				// Delete passengers
			}
			else if (delete_menu_choice == 3)
			{
				// Delete planes
			}
			else
			{
				std::cout << "Invalid input!" << std::endl;
				clear_console();
				continue;
			}

		}
        else if (main_menu_choice == 8) {
            std::cout << "Are you sure you want to terminate the program? (Y/N): ";
            std::string terminate_choice;
            std::cin >> terminate_choice;
            if (terminate_choice == "Y" || terminate_choice == "y") {
                std::cout << "Exiting the program..." << std::endl;
                break;  // Exit the loop and terminate the program
            }
            else {
                std::cout << "Returning to the main menu..." << std::endl;
                clear_console();
                continue;  // Continue to the next iteration of the loop
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