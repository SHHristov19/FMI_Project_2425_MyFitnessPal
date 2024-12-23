#include "include.h"

namespace mfp::bll
{
	void signUp()
	{
		User user;
		std::cout << "Enter your first name: ";
		std::cin >> user.first_name;
		std::cout << "Enter your last name: ";
		std::cin >> user.last_name;
		std::cout << "Enter your age: ";
		std::cin >> user.age;
		std::cout << "Enter your gender [M/F]: ";
		std::cin >> user.gender;
		std::cout << "Enter your height (in cm): ";
		std::cin >> user.height;
		std::cout << "Enter your weight (in kg): ";
		std::cin >> user.weight;
		std::cout << "Enter your activity level [1-5]: ";
		std::cin >> user.activity_level;
		std::cout << "Enter your type [Standard/Premium]: ";
		std::cin >> user.type;
		std::cout << "Enter your username: ";
		std::cin >> user.username;
		std::cout << "Enter your password: ";
		std::cin >> user.password;
		user.password = mfp::tools::passwordHash(user.password);
		user.created_on = std::time(nullptr); 
		mfp::dal::writeDataToUsersFile(USERS_FILE_NAME, user);
	}
}
