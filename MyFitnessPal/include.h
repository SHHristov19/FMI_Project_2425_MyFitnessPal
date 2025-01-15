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
	// Function to print the title
	void printTitle();

	// Function to print as ASCII art the date
	void printAsciiDate(int days = 0);

	// Function to print the menu options
	void printMenuOptions();

	// Function to print the login title
	void printLoginTitle();

	// Function to print the sign up title
	void printSignUpTitle();

	// Function to print the help title
	void printHelpTitle();

	// Function to print the CRUD menu options
	void printCRUDMenuOptions();

	// Function to print the add meal title
	void printAddMealTitle();

	// Function to print the add workout title
	void printAddWorkoutTitle();

	// Function to print the update meal title
	void printUpdateMealTitle();

	// Function to print the update workout title
	void printUpdateWorkoutTitle();

	// Function to print the update user title
	void printUpdateUserTitle();

	// Function to print the delete meal title
	void printDeleteMealTitle();

	// Function to print the delete workout title
	void printDeleteWorkoutTitle();
}

namespace bll
{
	// Function for the main panel
	void mainPanel();

	// Function for the sign up process
	void signUp();

	// Function for the sign in process
	void signIn();

	// Function for the home panel
	void homePanel(User user);

	// Function to print the help information
	void printHelp(User user);

	// Function to print the date and welcome message
	void printDateAndWelcome(std::string firstName, std::string lastName, int days = 0);

	// Function to print the daily summary
	DailySummary printDailySymmary(User user, int days = 0);

	

	// Function to enter user data
	void enterUserData(User& user, Goal& goal, bool isPasswordChange = false);
	

	void updateDailySummaryMeal(Meal meal, User user, int days = 0);

	// Function to add a meal for a user
	void addMealForUser(User user, int days = 0);

	// Function to update the daily summary for a workout
	void updateDailySummaryWorkout(Workout workout, User user, int days = 0);

	// Function to add a workout for a user
	void addWorkoutForUser(User user, int days = 0);

	// Function to update the daily summary
	void updateDailySummary(User user, Goal goal);

	// Function to get the goal for a user
	void getGoalForUser(std::string goalId, Goal& goal);

	// Function to get all meals for a user
	std::vector<Meal> getAllMealsForUser(std::string userId, int days);

	// Function to get all workouts for a user
	std::vector<Workout> getAllWorkoutsForUser(std::string userId, int days);

	// Function to calculate the BMR (Basal Metabolic Rate) for a user
	double calculateBMR(User user);

	// Function to calculate the goal calories for a user
	int calculateGoalCalories(User user, std::string goalType, unsigned calorieAdjustment);

	// Function to calculate the macronutrient ratio for a user
	void calculateMacronutrients(User user, Goal goal, int calories, MacronutrientRatio& ratio);

	// Function to create the daily summary for a user
	DailySummary createDailySummary(User user, Goal goal, int days = 0);

	// Function to print the meal data
	void printMealData(Meal meal);

	// Function to print the workout data
	void printWorkoutData(Workout workout);

	// Function to print the goal data
	void printGoalData(Goal goal);

	// Function to print the user data
	void printUserData(User user);

	// Function to update a meal for a user
	void updateMealForUser(User user, Meal meal, DailySummary dailySummary);

	// Function to update a workout for a user
	void updateWorkoutForUser(User user, Workout workout, DailySummary dailySummary);

	// Function to update a user
	void updateUser(User& user, Goal& goal);

	// Function to delete a meal for a user
	void deleteMealForUser(User user, Meal meal, DailySummary dailySummary);

	// Function to delete a workout for a user
	void deleteWorkoutForUser(User user, Workout workout, DailySummary dailySummary);

	// Function to delete all data for the day
	void deleteAllDataForTheDay(User user, std::vector<Meal> meals, std::vector<Workout> workouts, DailySummary dailySummary);
}

namespace dal
{
	// Function to read a property from a line in the file
	void readProperty(const std::string& line, size_t& start, size_t& end, std::string& field);

	// Functions to read data from file
	std::vector<User> readDataFromUsersFile();
	std::vector<Goal> readDataFromGoalsFile();
	std::vector<Meal> readDataFromMealsFile();
	std::vector<Workout> readDataFromWorkoutsFile();
	std::vector<DailySummary> readDataFromDailySummariesFile();

	// Functions to write data to file
	void writeDataToUsersFile(User user);
	void writeDataToGoalsFile(Goal goal);
	void writeDataToMealsFile(Meal meal);
	void writeDataToWorkoutsFile(Workout workout);
	void writeDataToDailySummariesFile(DailySummary dailySummary);

	// Functions to update or delete data from file
	void updateOrDeleteUser(User user, bool isUpdate);
	void updateOrDeleteGoal(Goal goal, bool isUpdate);
	void updateOrDeleteMeal(Meal meal, bool isUpdate);
	void updateOrDeleteWorkout(Workout workout, bool isUpdate);
	void updateOrDeleteDailySummary(DailySummary dailySummary, bool isUpdate);
	void updateOrDeleteMacronutrientRatio(MacronutrientRatio macronutrientRatio, bool isUpdate);

	// Functions to retrieve data from file
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
	// Function to convert a string to uppercase
	void to_upper(std::string& data);

	// Function to hash a password
	std::string passwordHash(const std::string& password);

	// Function to get the current date and time
	std::string getDatetime(const char* format, int days = 0);

	// Function to generate a GUID (Globally Unique Identifier)
	std::string generateGUID();

	// Function to check if a character is a digit
	bool isDigit(char ch);

	// Function to get the number of digits in a string
	size_t getDigits(std::string input);

	// Function to get the activity level based on a level string
	std::string getActivityLevel(std::string level);

	// Function to set the console size
	void setConsoleSize();

	// Function to clear the console
	void clearConsole();

	// Function to set the console text color to cyan
	void colorCyan();

	// Function to set the console text color to blue
	void colorBlue();

	// Function to set the console text color to yellow
	void colorYellow();

	// Function to set the console text color to green
	void colorGreen();

	// Function to set the console text color to red
	void colorRed();

	// Function to reset the console text color
	void resetColor();

	// Function to hide the console cursor
	void hideCursor();

	// Function to show the console cursor
	void showCursor();

	// Function to clear the current line in the console
	void clearLine();

	// Function to convert a string to lowercase
	void toLower(std::string& data);

	// Function to get user input
	std::string getInput();

	void enterValidPassword(std::string& password, bool isUpdate = false);
	std::string validatePassword(std::string password, bool isChangePassword);
	void enterValidType(const std::string types[], size_t typeSize, std::string errorMsg, std::string& type, std::string msg, bool isUpdate = false);
	void enterValidString(std::string& data, std::string msg, bool isUpdate = false);
	void enterValidAge(std::string& age, std::string msg, bool isUpdate = false);
	void enterValidMeasurements(std::string& measurements, std::string msg, bool isUpdate = false);
	void enterValidCaloriesAndGrams(std::string& data, std::string msg, bool isUpdate = false);
	void displayErrorAndClearLine();
	void printActivityLevels();
	void printGoalTypes();
	bool isStringOnlyDigits(std::string data);
}