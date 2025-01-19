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

    bool isDigit(char ch)
    {
        return ch >= '0' && ch <= '9';
    }

    size_t getDigits(std::string input)
    {
        std::string digits;

        for (char ch : input)
        {
            if (isDigit(ch))
            {
                digits += ch;
            }
        }

        return digits.empty() ? 0 : stoi(digits);
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
        std::cout << "\033[8;40;155t";
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

	// Gets the user input in lowercase
	std::string getInput()
	{
		std::string line;

        // Hide cursor
        hideCursor();

		
		std::getline(std::cin, line);
        
		toLower(line);

		return line;
	}

    std::string getActivityLevel(std::string level)
    {
        switch (level[0])
        {
        case '1':
            return ". VeryActive (6-7 days of training and very active daily life)";
        case '2':
            return ". ActiveJob (3-5 days of training and active daily life)";
        case '3':
            return ". ModerateActivity (1-3 days of training and moderately active daily life)";
        case '4':
            return ". LightActivity (Light exercise or sports 1-3 days a week)";
        case '5':
            return ". SedentaryJob (Little or no exercise, desk job)";
        }
    }

	std::string validatePassword(std::string password, bool isChangePassword)
	{
		if (isChangePassword && password.empty())
		{
			return std::string();
		}

		if (password.length() < 8)
		{
			return "Password must be at least 8 characters long!";
		}

		bool hasDigit = false;
		bool hasLowercase = false;
		bool hasUppercase = false;
		bool hasSpecialCharacter = false;

		for (size_t i = 0; i < password.length(); i++)
		{
			if (isdigit(password[i]))
			{
				hasDigit = true;
			}
			else if (islower(password[i]))
			{
				hasLowercase = true;
			}
			else if (isupper(password[i]))
			{
				hasUppercase = true;
			}
			else if (ispunct(password[i]))
			{
				hasSpecialCharacter = true;
			}
		}

		if (!hasDigit)
		{
			return "Password must contain at least one digit!";
		}

		if (!hasLowercase)
		{
			return "Password must contain at least one lowercase letter!";
		}

		if (!hasUppercase)
		{
			return "Password must contain at least one uppercase letter!";
		}

		if (!hasSpecialCharacter)
		{
			return "Password must contain at least one special character!";
		}

		return std::string();
	}

	void enterValidPassword(std::string& password, bool isUpdate)
	{
		while (true)
		{
			std::cout << TABULATION << "Enter your password: ";
			std::getline(std::cin, password);

			std::string errorMsg = validatePassword(password, isUpdate);

			if (errorMsg.empty())
			{
				return;
			}

			std::cin.clear();
			tools::clearLine();
			tools::colorRed();
			std::cout << TABULATION << errorMsg << std::endl;
			tools::resetColor();
		}
	}

	void enterValidType(const std::string types[], size_t typeSize, std::string errorMsg, std::string& type, std::string msg,bool isUpdate)
	{
		while (true)
		{
			std::cout << TABULATION << msg;
			std::getline(std::cin, type);

			if (isUpdate && type.empty())
			{
				return;
			}

			for (size_t i = 0; i < typeSize; i++)
			{
				if (type == types[i])
				{
					return;
				}
			}

			displayErrorAndClearLine();
		}
	}

	void enterValidString(std::string& data, std::string msg, bool isUpdate)
	{
		while (true)
		{
			std::cout << TABULATION << msg;
			std::getline(std::cin, data);

			if (isUpdate && data.empty())
			{
				return;
			}

			if (std::cin.fail() || data.empty() || data.length() > 25)
			{
				displayErrorAndClearLine();
			}
			else
			{
				return;
			}
		}
	}

    bool isStringOnlyDigits(std::string data)
    {
		// Check if the string is empty
		if (data.empty())
		{
			return false;
		}

		// Iterate through each character in the string
		for (char c : data)
		{
			// Check if the character is not a digit
			if (!std::isdigit(c))
			{
				return false;
			}
		}

		// Check if the length of the string is greater than 6
		return data.length() > 6 ? false : true;
    }

	void enterValidAge(std::string& age, std::string msg, bool isUpdate)
	{
		while (true)
		{
			std::cout << TABULATION << msg;
			std::getline(std::cin, age);

			if (isUpdate && age.empty())
			{
				return;
			}
			
			if (std::cin.fail() || !isStringOnlyDigits(age) || std::stoi(age) < MIN_AGE || std::stoi(age) > MAX_AGE)
			{
				displayErrorAndClearLine();
			}
			else
			{
				return;
			}
		}
	}

	void enterValidMeasurements(std::string& measurements, std::string msg, bool isUpdate)
	{
		while (true)
		{
			std::cout << TABULATION << msg;
			std::getline(std::cin, measurements);

			if (isUpdate && measurements.empty())
			{
				return;
			}

            if (std::cin.fail() || !isStringOnlyDigits(measurements) || std::stoi(measurements) < MIN_MEASUREMENTS || std::stoi(measurements) > MAX_MEASUREMENTS)
			{
				displayErrorAndClearLine();
			}
			else
			{
				return;
			}
		}
	}

	void enterValidCaloriesAndGrams(std::string& data, std::string msg, bool isUpdate)
	{
		while (true)
		{
			std::cout << TABULATION << msg;
			std::getline(std::cin, data);

			if (isUpdate && data.empty())
			{
				return;
			}

			if (std::cin.fail() || !isStringOnlyDigits(data) || std::stoi(data) < MIN_CALORIES_GRAMS || std::stoi(data) > MAX_CALORIES_GRAMS)
			{
				displayErrorAndClearLine();
			}
			else
			{
				return;
			}
		}
	}

	void displayErrorAndClearLine()
	{
		std::cin.clear();
		tools::clearLine();
		tools::colorRed();
		std::cout << TABULATION << INVALID_MSG << std::endl;
		tools::resetColor();
	}

	void printActivityLevels()
	{
		std::cout << std::endl;
		std::cout << TABULATION << "1. VeryActive (intense exercise or physical job)" << std::endl;
		std::cout << TABULATION << "2. ActiveJob (walking or standing most of the day)" << std::endl;
		std::cout << TABULATION << "3. ModerateActivity (light exercise or sports 3-5 days a week)" << std::endl;
		std::cout << TABULATION << "4. LightActivity (office work or sitting most of the day)" << std::endl;
		std::cout << TABULATION << "5. SedentaryJob (little or no exercise)" << std::endl;
	}

	void printGoalTypes()
	{
		std::cout << std::endl;
		std::cout << TABULATION << "1. LoseWeight" << std::endl;
		std::cout << TABULATION << "2. MaintainWeight" << std::endl;
		std::cout << TABULATION << "3. GainWeight" << std::endl;
	}
}