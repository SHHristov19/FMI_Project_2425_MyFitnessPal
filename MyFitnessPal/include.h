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
	void printUpdateMealTitle();
	void printUpdateWorkoutTitle();
	void printUpdateUserTitle();
	void printDeleteMealTitle();
	void printDeleteWorkoutTitle();
}

namespace bll
{
	
	void mainPanel();
	void signUp();
	void signIn();
	void homePanel(User user);

	void printHelp(User user);
	void printDateAndWelcome(std::string firstName, std::string lastName, int days = 0);
	DailySummary printDailySymmary(User user, int days = 0);

	void enterValidPassword(std::string& password, bool isUpdate = false);
	std::string validatePassword(std::string password, bool isChangePassword);
	void enterUserData(User& user, Goal& goal, bool isPasswordChange = false);
	void enterValidType(const std::string types[], size_t typeSize, std::string errorMsg, std::string& type, bool isUpdate = false);

	void updateDailySummaryMeal(Meal meal, User user, int days = 0);
	void addMealForUser(User user, int days = 0);
	void updateDailySummaryWorkout(Workout workout, User user, int days = 0);
	void addWorkoutForUser(User user, int days = 0);
	void updateDailySummary(User user, Goal goal);

	void getGoalForUser(std::string goalId, Goal& goal);

	std::vector<Meal> getAllMealsForUser(std::string userId, int days);
	std::vector<Workout> getAllWorkoutsForUser(std::string userId, int days);

	double calculateBMR(User user);
	int calculateGoalCalories(User user, std::string goalType, unsigned calorieAdjustment);
	void calculateMacronutrients(User user, Goal goal, int calories, MacronutrientRatio& ratio);

	DailySummary createDailySummary(User user, Goal goal, int days = 0);

	void printMealData(Meal meal);
	void printWorkoutData(Workout workout);
	void printGoalData(Goal goal);
	void printUserData(User user);
	void updateMealForUser(User user, Meal meal, DailySummary dailySummary);
	void updateWorkoutForUser(User user, Workout workout, DailySummary dailySummary);
	void updateUser(User& user, Goal& goal);
	void deleteMealForUser(User user, Meal meal, DailySummary dailySummary);
	void deleteWorkoutForUser(User user, Workout workout, DailySummary dailySummary);
	void deleteAllDataForTheDay(User user, std::vector<Meal> meals, std::vector<Workout> workouts, DailySummary dailySummary);
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

	// Write data to files
	void writeDataToUsersFile(User user);
	void writeDataToGoalsFile(Goal goal);
	void writeDataToMealsFile(Meal meal);
	void writeDataToWorkoutsFile(Workout workout);
	void writeDataToDailySummariesFile(DailySummary dailySummary);

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
}

namespace tools
{
	void to_upper(std::string& data);
	std::string passwordHash(const std::string& password);
	std::string getDatetime(const char* format, int days = 0);
	std::string generateGUID();
	bool isDigit(char ch);
	size_t getDigits(std::string input);
	std::string getActivityLevel(std::string level);

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