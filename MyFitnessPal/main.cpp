#include "include.h"

int main() 
{
    tools::setConsoleSize();
    pl::printTitle();
    pl::printMenuOptions();

    while(true) 
    {
         char input = tools::getInput();
        switch (input)
        {
            case '1':
                tools::clearConsole();
                bll::signIn();
                break;
            case '2':
                tools::clearConsole();
                bll::signUp();
				break;
            case '3':
                return 0;
			default:
                tools::clearLine();
				break;
        }
    }
}