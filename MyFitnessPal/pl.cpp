#include "include.h"

namespace pl
{
    void printTitle() 
    {
        std::cout << R"(
                                          ____        __                                   ____          ___      
                         /'\_/`\         /\  _`\   __/\ \__                               /\  _`\       /\_ \     
                        /\      \  __  __\ \ \L\_\/\_\ \ ,_\   ___      __    ____    ____\ \ \L\ \ __  \//\ \    
                        \ \ \__\ \/\ \/\ \\ \  _\/\/\ \ \ \/ /' _ `\  /'__`\ /',__\  /',__\\ \ ,__/'__`\  \ \ \   
                         \ \ \_/\ \ \ \_\ \\ \ \/  \ \ \ \ \_/\ \/\ \/\  __//\__, `\/\__, `\\ \ \/\ \L\.\_ \_\ \_ 
                          \ \_\\ \_\/`____ \\ \_\   \ \_\ \__\ \_\ \_\ \____\/\____/\/\____/ \ \_\ \__/.\_\/\____\
                           \/_/ \/_/`/___/> \\/_/    \/_/\/__/\/_/\/_/\/____/\/___/  \/___/   \/_/\/__/\/_/\/____/
                                       /\___/                                                                     
                                       \/__/   
                        
        )" << std::endl;
    }
    
    void printMenuOptions()
    {
		tools::colorBlue();
        std::cout << R"(
                                                     _     _    ___   ___ ___ _  _      
                                                    / |   | |  / _ \ / __|_ _| \| |     
                                                    | |_  | |_| (_) | (_ || || .` |     
                                                    |_(_) |____\___/ \___|___|_|\_|     
                                                     ___     ___ ___ ___ _  _ _   _ ___ 
                                                    |_  )   / __|_ _/ __| \| | | | | _ \
                                                     / / _  \__ \| | (_ | .` | |_| |  _/
                                                    /___(_) |___/___\___|_|\_|\___/|_|  
                                                     ____    _____  _____ _____         
                                                    |__ /   | __\ \/ /_ _|_   _|        
                                                     |_ \_  | _| >  < | |  | |          
                                                    |___(_) |___/_/\_\___| |_|          
                                                  
        )" << std::endl;
		tools::resetColor();
    }

    void printHelpTitle()
    {
        tools::colorRed();
        std::cout << R"(
                                                            _  _ ___ _    ___ 
                                                           | || | __| |  | _ \
                                                           | __ | _|| |__|  _/
                                                           |_||_|___|____|_|  
                                                                                
        )" << std::endl;
        tools::resetColor();
    }

	void printAddWorkoutTitle()
	{
		tools::colorBlue();
		std::cout << R"(
			                              _   ___  ___   __      _____  ___ _  _____  _   _ _____ 
			                             /_\ |   \|   \  \ \    / / _ \| _ \ |/ / _ \| | | |_   _|
			                            / _ \| |) | |) |  \ \/\/ / (_) |   / ' < (_) | |_| | | |  
			                           /_/ \_\___/|___/    \_/\_/ \___/|_|_\_|\_\___/ \___/  |_|  
																				
		)" << std::endl;
		tools::resetColor();
	}

    
    void printAddMealTitle()
    {
		tools::colorGreen();
		std::cout << R"(
			                                   _   ___  ___    __  __ ___   _   _    
			                                  /_\ |   \|   \  |  \/  | __| /_\ | |   
			                                 / _ \| |) | |) | | |\/| | _| / _ \| |__ 
			                                /_/ \_\___/|___/  |_|  |_|___/_/ \_\____|
																												
		)" << std::endl;
		tools::resetColor();
    }

    void printUpdateMealTitle()
    {
        tools::colorBlue();
        std::cout << R"(
			                           _   _ ___ ___   _ _____ ___   __  __ ___   _   _    
			                          | | | | _ \   \ /_\_   _| __| |  \/  | __| /_\ | |   
			                          | |_| |  _/ |) / _ \| | | _|  | |\/| | _| / _ \| |__ 
			                           \___/|_| |___/_/ \_\_| |___| |_|  |_|___/_/ \_\____|
																												
		)" << std::endl;
        tools::resetColor();
    }
    
	void printDeleteMealTitle()
	{
		tools::colorBlue();
		std::cout << R"(
			                           ___  ___ _    ___ _____ ___   __  __ ___   _   _    
			                          |   \| __| |  | __|_   _| __| |  \/  | __| /_\ | |   
			                          | |) | _|| |__| _|  | | | _|  | |\/| | _| / _ \| |__ 
			                          |___/|___|____|___| |_| |___| |_|  |_|___/_/ \_\____|
        )" << std::endl;
        tools::resetColor();
    } 

    void printUpdateWorkoutTitle()
    {
        tools::colorBlue();
        std::cout << R"(
			                    _   _ ___ ___   _ _____ ___   __      _____  ___ _  _____  _   _ _____ 
			                   | | | | _ \   \ /_\_   _| __|  \ \    / / _ \| _ \ |/ / _ \| | | |_   _|
			                   | |_| |  _/ |) / _ \| | | _|    \ \/\/ / (_) |   / ' < (_) | |_| | | |  
			                    \___/|_| |___/_/ \_\_| |___|    \_/\_/ \___/|_|_\_|\_\___/ \___/  |_|  
																												
		)" << std::endl;
        tools::resetColor();
    }

    void printDeleteWorkoutTitle()
    {
        tools::colorBlue();
        std::cout << R"(
			                     ___  ___ _    ___ _____ ___  __      _____  ___ _  _____  _   _ _____ 
			                    |   \| __| |  | __|_   _| __| \ \    / / _ \| _ \ |/ / _ \| | | |_   _|
			                    | |) | _|| |__| _|  | | | _|   \ \/\/ / (_) |   / ' < (_) | |_| | | |  
			                    |___/|___|____|___| |_| |___|   \_/\_/ \___/|_|_\_|\_\___/ \___/  |_|  
																												
		)" << std::endl;
        tools::resetColor();
    }
    
 
 
 
 
                                                                        

    void printUpdateUserTitle()
    {
        tools::colorBlue();
        std::cout << R"(
			                            _   _ ___ ___   _ _____ ___    _   _ ___ ___ ___ 
			                           | | | | _ \   \ /_\_   _| __|  | | | / __| __| _ \
			                           | |_| |  _/ |) / _ \| | | _|   | |_| \__ \ _||   /
			                            \___/|_| |___/_/ \_\_| |___|   \___/|___/___|_|_\
																												
		)" << std::endl;
        tools::resetColor();
    }

    void printLoginTitle()
    {
        std::cout << R"(
                                                       _    ___   ___ ___ _  _ 
                                                      | |  / _ \ / __|_ _| \| |
                                                      | |_| (_) | (_ || || .` |
                                                      |____\___/ \___|___|_|\_|

        )" << std::endl;
    }

    void printSignUpTitle()
    {
        std::cout << R"(
                                                      ___ ___ ___ _  _ _   _ ___ 
                                                     / __|_ _/ __| \| | | | | _ \
                                                     \__ \| | (_ | .` | |_| |  _/
                                                     |___/___\___|_|\_|\___/|_|  

        )" << std::endl;
    }

    void printAsciiDate(int days)
    {
		std::string date = tools::getDatetime(DATE_FORMAT, days); // Get the current date and time

        for (int row = 0; row < 6; row++) // Loop through rows of ASCII art (6 rows)
        { 
            std::cout << TABULATION; // Add tabulation before the first digit
            for (int i = 0; date[i] != '\0'; i++) 
            {
                if (date[i] == '.') 
                {
                    // Print separator row by row
                    std::cout << ASCII_SEPARATOR[row];
                }
                else 
                {
                    // Print digit row by row
                    std::cout << ASCII_DIGITS[date[i] - '0'][row];
                }
                std::cout << " "; // Space between characters
            }
            std::cout << std::endl;
        }
    }
}
