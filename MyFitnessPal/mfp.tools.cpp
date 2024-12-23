#include "include.h"

namespace mfp::tools
{
    void to_upper(std::string& data)
    {
        for (char& c : data) 
        {
            if (c >= 'a' && c <= 'z') {
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

    std::string getDate()
    {
        time_t timestamp;
        time(&timestamp);

        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &timestamp);

        // Reformat the date and time
        std::string formattedDateTime = std::string(buffer);
        std::string month = formattedDateTime.substr(4, 3);
        
        if (month == "Jan") {
            month = "01";
        }
        else if (month == "Feb") {
            month = "02";
        }
        else if (month == "Mar") {
            month = "03";
        }
        else if (month == "Apr") {
            month = "04";
        }
        else if (month == "May") {
            month = "05";
        }
        else if (month == "Jun") {
            month = "06";
        }
        else if (month == "Jul") {
            month = "07";
        }
        else if (month == "Aug") {
            month = "08";
        }
        else if (month == "Sep") {
            month = "09";
        }
        else if (month == "Oct") {
            month = "10";
        }
        else if (month == "Nov") {
            month = "11";
        }
        else if (month == "Dec") {
            month = "12";
        }

        std::string day = formattedDateTime.substr(8, 2);
        std::string year = formattedDateTime.substr(20, 4);
        std::string time = formattedDateTime.substr(11, 8);

        std::string formattedBuffer = month + "." + day + "." + year + " " + time;

        // Display the reformatted date and time
        return formattedBuffer;
    }
}
