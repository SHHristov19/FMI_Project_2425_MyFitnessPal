#pragma once
#include <string>
#include <ctime>

struct User
{
    std::string id;
    std::string first_name;
    std::string last_name;
    unsigned int age;
    char gender;
    float height; // in cm
    float weight; // in kg
	char activity_level; // e.g., 1-5 scale from ActivityLevel struct
    std::string goal_id; // foreign key to Goals
    std::string username;
    std::string password;
    std::string type; // e.g., "Standart", "Premium"
    std::string created_on;
};

// Struct for Goals
struct Goal
{
    std::string id;
    char type;
	float weekly_change; // e.g., in kg per week = 0.25, 0.50, 0.75, 1.00
    unsigned int calorie_adjustment; // in kcal
};

struct Meal 
{
    std::string id;
    std::string name;
    std::string calories; // in kcal
	std::string protein; // in grams
	std::string fat; // in grams
	std::string carbohydrates; // in grams
    std::string created_by; // foreign key to Users
    std::string created_on;
};

struct Workout 
{
    std::string id;
    std::string name;
    std::string calories_burned; // in kcal
    std::string created_by; // foreign key to Users
    std::string created_on;
};

struct DailySummary 
{
    std::string id;
    std::string user_id; // foreign key to Users
    std::string date; // represents the day
    unsigned int calories_consumed; // in kcal
    unsigned int calories_burned; // in kcal
    unsigned int recommended_calories; // in kcal
    unsigned int calorie_balance; // (calories_consumed - calories_burned)
	unsigned int protein; // in grams
	unsigned int fat; // in grams
	unsigned int carbohydrates; // in grams
	std::string created_on;
};

struct MacronutrientRatio 
{
    std::string id;
    std::string goal_id; // foreign key to Goals
    float protein_ratio; // as percentage (0-100)
    float fat_ratio; // as percentage (0-100)
    float carbohydrate_ratio; // as percentage (0-100)
	std::string created_on;
};
