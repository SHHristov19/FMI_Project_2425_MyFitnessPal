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
	void printAsciiDate(int days = 0);
	void printMenuOptions();
	void printLoginTitle();
	void printSignUpTitle();
	void printHelpTitle();
	void printCRUDMenuOptions();

	void printAddMealTitle();
	void printAddWorkoutTitle();
}

namespace bll
{
	
	void mainPanel();
	void signUp();
	void signIn();
	void homePanel(User user);

	void printHelp(User user);
	void printDateAndWelcome(std::string firstName, std::string lastName, int days = 0);
	void printDailySymmary(User user, int days = 0);

	std::string enterValidPassword(std::string password);
	std::string validatePassword(std::string password);


	char enterValidType(const char types[], size_t typeSize, std::string errorMsg);
	std::string enterValidType(const std::string types[], size_t typeSize, std::string errorMsg);

	void updateDailySummaryOnAddingMeal(Meal meal, User user, int days = 0);
	void addMealForUser(User user, int days = 0);
	void updateDailySummaryOnAddingWorkout(Workout workout, User user, int days = 0);
	void addWorkoutForUser(User user, int days = 0);

	void getGoalForUser(std::string goalId);

	void getAllMealsForUser(std::string userId, int days);
	void getMealForUser(std::string userId, std::string mealId);

	void getWorkoutForUser(std::string userId, std::string workoutId);
	void getAllWorkoutsForUser(std::string userId, int days);

	double calculateBMR(User user);
	int calculateGoalCalories(User user, std::string goalType, unsigned calorieAdjustment);

	DailySummary createDailySummary(User user, Goal goal);
}

namespace dal
{
	void readProperty(const std::string& line, size_t& start, size_t& end, std::string& field);

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
	DailySummary getDailySummaryByUserIdToday(std::string id, int days = 0);

	std::vector<Goal> getGoalsByUserId(std::string id);
	std::vector<Meal> getMealsByUserId(std::string id, bool forToday = false, int days = 0);
	std::vector<Workout> getWorkoutsByUserId(std::string id, bool forToday = false, int days = 0);
	std::vector<DailySummary> getDailySummariesByUserId(std::string id);
	std::vector<MacronutrientRatio> getMacronutrientRatioByUserId(std::string id);

	
}

namespace tools
{
	void to_upper(std::string& data);
	std::string passwordHash(const std::string& password);
	std::string getDatetime(const char* format, int days = 0);
	std::string generateGUID();

	void setConsoleSize();
	void clearConsole();
	void colorCyan();
	void colorBlue();
	void colorYellow();
	void colorGreen();
	void colorRed();
	void resetColor();
	void hideCursor();
	void showCursor();
	void clearLine();
	void toLower(std::string& data);
	std::string getInput();
}