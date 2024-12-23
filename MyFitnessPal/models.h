#pragma once
#include <string>
#include <ctime>

struct User
{
    unsigned int id;
    std::string first_name;
    std::string last_name;
    unsigned int age;
    std::string gender;
    float height; // in cm
    float weight; // in kg
	int activity_level; // e.g., 1-5 scale from ActivityLevel struct
    int goal_id; // foreign key to Goals
    std::string username;
    std::string password;
    std::string type; // e.g., "Standart", "Premium"
    std::time_t created_on;
};

// Struct for Goals
struct Goal
{
    int id;
    std::string name;
    float weekly_change; // e.g., in kg
    unsigned int calorie_adjustment; // in kcal
};

struct Meal 
{
    int id;
    std::string name;
    unsigned int calories; // in kcal
    int created_by; // foreign key to Users
    std::time_t created_on;
};

struct Workout {
    int id;
    std::string name;
    unsigned int calories_burned; // in kcal
    int created_by; // foreign key to Users
    std::time_t created_on;
};

struct DailySummary 
{
    int id;
    int user_id; // foreign key to Users
    std::time_t date; // represents the day
    unsigned int calories_consumed; // in kcal
    unsigned int calories_burned; // in kcal
    unsigned int recommended_calories; // in kcal
    unsigned int calorie_balance; // (calories_consumed - calories_burned)
};

struct MacronutrientRatio 
{
    int id;
    int goal_id; // foreign key to Goals
    float protein_ratio; // as percentage (0-100)
    float fat_ratio; // as percentage (0-100)
    float carbohydrate_ratio; // as percentage (0-100)
};
