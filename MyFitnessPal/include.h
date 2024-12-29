#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>

#include "models.h"
#include "constants.h"

namespace pl
{
	void printTitle();
	void clearConsole();
	void printAsciiDate();
}

namespace bll
{
	void signUp();
	void signIn();

	std::string enterValidPassword(std::string password);
	std::string validatePassword(std::string password);


	char enterValidType(const char types[], size_t typeSize, std::string errorMsg);
	float enterValidType(const float types[], size_t typeSize, std::string errorMsg);
	std::string enterValidType(const std::string types[], size_t typeSize, std::string errorMsg);


	void addMealForUser(User user);
	void addWorkoutForUser(User user);
}

namespace dal
{
	// Read data from files
	std::vector<User> readDataFromUsersFile();
	std::vector<Goal> readDataFromGoalsFile();
	std::vector<Meal> readDataFromMealsFile();
	std::vector<Workout> readDataFromWorkoutsFile(); 
	std::vector<DailySummary> readDataFromDailySummariesFile();
	std::vector<MacronutrientRatio> readDataFromMacronutrientRatiosFile();

	// Write data to files
	void writeDataToUsersFile(User user);
	void writeDataToGoalsFile(Goal goal);
	void writeDataToMealsFile(Meal meal);
	void writeDataToWorkoutsFile(Workout workout);
	void writeDataToDailySummariesFile(DailySummary dailySummary);
	void writeDataToMacronutrientRatioFile(MacronutrientRatio macronutrientRatio);

	// Update data from file
	void updateOrDeleteUser(User user, bool isUpdate);
	void updateOrDeleteGoal(Goal goal, bool isUpdate);
	void updateOrDeleteMeal(Meal meal, bool isUpdate);
	void updateOrDeleteWorkout(Workout workout, bool isUpdate);
	void updateOrDeleteDailySummary(DailySummary dailySummary, bool isUpdate);
	void updateOrDeleteMacronutrientRatio(MacronutrientRatio macronutrientRatio, bool isUpdate);

	User findUserByUsernameAndPassword(std::string username, std::string password);
	User getUserById(std::string id);
	Goal getGoalById(std::string id);
	Meal getMealById(std::string id);
	Workout getWorkoutById(std::string id);

	std::vector<Goal> getGoalsByUserId(std::string id);
	std::vector<Meal> getMealsByUserId(std::string id);
	std::vector<Workout> getWorkoutsByUserId(std::string id);
	std::vector<DailySummary> getDailySummariesByUserId(std::string id);
	std::vector<MacronutrientRatio> getMacronutrientRatioByUserId(std::string id);
}

namespace tools
{
	void to_upper(std::string& data);
	std::string passwordHash(const std::string& password);
	std::string getDatetime();
	std::string generateGUID();
}