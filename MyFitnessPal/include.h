#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>

#include "models.h"
#include "constants.h"

namespace mfp::pl
{

}

namespace mfp::bll
{
	void signUp();
}

namespace mfp::dal
{
	// Read data from files
	std::vector<std::vector<User>> readDataFromUsersFile(std::string fileName);
	std::vector<std::vector<Goal>> readDataFromGoalsFile(std::string fileName);
	std::vector<std::vector<Meal>> readDataFromMealsFile(std::string fileName);
	std::vector<std::vector<Workout>> readDataFromWorkoutsFile(std::string fileName); 
	std::vector<std::vector<DailySummary>> readDataFromDailySummariesFile(std::string fileName);
	std::vector<std::vector<MacronutrientRatio>> readDataFromMacronutrientRatioFile(std::string fileName);

	// Write data to files
	void writeDataToUsersFile(std::string fileName, User data);
	void writeDataToGoalsFile(std::string fileName, std::vector<Goal> data);
	void writeDataToMealsFile(std::string fileName, std::vector<Meal> data);
	void writeDataToWorkoutsFile(std::string fileName, std::vector<Workout> data);
	void writeDataToDailySummariesFile(std::string fileName, std::vector<DailySummary> data);
	void writeDataToMacronutrientRatioFile(std::string fileName, std::vector<MacronutrientRatio> data);


}

namespace mfp::tools
{
	void to_upper(std::string& data);
	std::string passwordHash(const std::string& password);
	std::string getDate();
}