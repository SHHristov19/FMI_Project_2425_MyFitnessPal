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

    void clearConsole() 
    {
        std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear screen and reset cursor
    }

    void printAsciiDate()
    {
        // Get the current date
        time_t t = time(0);
        tm now;
        localtime_s(&now, &t);

        // Format: YYYY,MM,DD
        char date[11];
        strftime(date, sizeof(date), "%d.%m.%Y", &now);

        for (int row = 0; row < 6; row++) 
        { // Loop through rows of ASCII art (6 rows)
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
