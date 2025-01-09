#include "include.h"

namespace tools
{
    void to_upper(std::string& data)
    {
        for (char& c : data)
        {
            if (c >= 'a' && c <= 'z') 
            {
                c -= ('a' - 'A'); // Convert lowercase to uppercase
            }
        }
    }

    std::string passwordHash(const std::string& password)
    {
        unsigned long hash = 5381; // prime number
        for (char c : password)
        {
            hash = ((hash << 5) + hash) + c;
        }

        // Convert hash value to a hexadecimal string
        std::string hashStr;
        while (hash > 0)
        {
            int remainder = hash % 16;
            hashStr += (remainder < 10) ? ('0' + remainder) : ('a' + (remainder - 10));
            hash /= 16;
        }

        // Reverse the string to get the correct hexadecimal representation
        std::reverse(hashStr.begin(), hashStr.end());

        // Convert the string to uppercase
        to_upper(hashStr);

        return hashStr;
    }

    std::string getDatetime(const char* format, int days)
    {
        // Get the current date
        time_t t = time(0);
        t += days * 24 * 60 * 60; // Add days to the current date

        tm now;
        localtime_s(&now, &t);

        char date[30];
        strftime(date, sizeof(date), format, &now);

        return date;
    }

    std::string generateGUID()
    {
        const char* chars = "0123456789ABCDEF"; // Hexadecimal characters
        std::string guid;

        // Use the current time as a source of randomness
        static unsigned long long timeSeed = std::time(nullptr);

        // Generate the GUID in the format: 8-4-4-4-12
        int sections[] = { 8, 4, 4, 4, 12 }; // Section lengths

        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < sections[i]; ++j)
            {
                // Use timeSeed combined with shifting and XOR to generate "random" values
                timeSeed ^= (timeSeed << 21);
                timeSeed ^= (timeSeed >> 35);
                timeSeed ^= (timeSeed << 4);

                // Extract a pseudo-random value between 0 and 15
                unsigned char randomValue = timeSeed & 0xF;

                // Map the random value to a hexadecimal character
                guid += chars[randomValue];
            }
            if (i < 4) 
            {
                guid += '-'; // Add a dash between sections
            }
        }

        return guid;
    }


    void clearConsole()
    {
        std::cout << "\033c"; // ANSI escape code to clear screen and reset cursor
    }

    void colorCyan()
    {
        std::cout << "\033[1;36m";
    }

    void colorBlue()
    {
        std::cout << "\033[1;34m";
    }

    void colorYellow()
    {
        std::cout << "\033[1;33m";
    }

    void colorGreen()
    {
        std::cout << "\033[1;32m";
    }

    void colorRed()
    {
        std::cout << "\033[1;31m";
    }

    void resetColor()
    {
        std::cout << "\033[0m";
    }

	void setConsoleSize()
	{
        // Set the terminal window size to width and height
        std::cout << "\033[8;40;140t";
	}

    void hideCursor()
    {
        std::cout << "\033[?25l"; // ANSI code to hide the cursor
    }

    void showCursor()
    {
        std::cout << "\033[?25h"; // ANSI code to show the cursor
    }

    // Function to move the cursor to a specific position
    void clearLine()
    {
		std::cout << "\033[A\33[2K\r" << std::flush; // ANSI escape code to move up one line and clear the line
    } 

	void toLower(std::string& data)
	{
		for (char& c : data)
		{
			c = std::tolower(c);
		}
	}

	std::string getInput()
	{
		std::string line;

        // Hide cursor
        hideCursor();

		
		std::getline(std::cin, line);
        
		toLower(line);

		return line;
	}
}