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
        std::cout << "6. Delete Data" << std::endl;
        std::cout << "7. Exit" << std::endl << std::endl;

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
            std::cout << "Select the search method: " << std::endl;
            // Perform search action
        }
        else if (main_menu_choice == 5) {
            std::cout << "Select the filter method: " << std::endl;
            // Perform filter action
        }
        else if (main_menu_choice == 6) {
            std::cout << "Select the delete method: " << std::endl;
            // Perform delete action
        }
        else if (main_menu_choice == 7) {
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



	//viewFlightData();

	//addFlightData();


	return 0;
}