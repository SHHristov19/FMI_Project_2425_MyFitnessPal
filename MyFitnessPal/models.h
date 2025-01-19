#pragma once

struct User
{
    std::string id;
    std::string firstName;
    std::string lastName;
    std::string age; 
	std::string gender; // e.g., "M", "F"
    std::string height; // in cm
    std::string weight; // in kg
    std::string activityLevel; // e.g., 1-5 scale from ActivityLevel struct
    std::string goalId; // foreign key to Goals
    std::string username;
    std::string password;
    std::string type; // e.g., "Standart", "Premium"
    std::string createdOn;
};

struct Goal
{
    std::string id;
    std::string type;
    std::string weeklyChange; // e.g., in kg per week = 0.25, 0.50, 0.75, 1.00
    std::string calorieAdjustment; // in kcal
};

struct Meal 
{
    std::string id;
    std::string name;
    std::string calories; // in kcal
	std::string protein; // in grams
	std::string fat; // in grams
	std::string carbohydrates; // in grams
    std::string createdBy; // foreign key to Users
    std::string createdOn;
    std::string date;
};

struct Workout 
{
    std::string id;
    std::string name;
    std::string caloriesBurned; // in kcal
    std::string createdBy; // foreign key to Users
    std::string createdOn;
	std::string date;
};

struct DailySummary 
{
    std::string id;
    std::string userId; // foreign key to Users
    std::string date; // represents the day
    std::string caloriesConsumed; // in kcal
    std::string caloriesBurned; // in kcal
    std::string recommendedCalories; // in kcal
    std::string calorieBalance; // (calories_consumed - calories_burned)
	std::string protein; // in grams
	std::string fat; // in grams
	std::string carbohydrates; // in grams
	std::string createdOn;
};

struct MacronutrientRatio 
{
    std::string protein; // as percentage (0-100)
    std::string fat; // as percentage (0-100)
    std::string carbohydrates; // as percentage (0-100)
};
