#pragma once

// Struct-like representation for Activity Level
struct ActivityLevel 
{
    const int VeryActive = 1; // Много активен
    const int ActiveJob = 2; // Активна работа
    const int ModerateActivity = 3; // Умерена активност
    const int LightActivity = 4; // Лека активност
    const int SedentaryJob = 5; // Седяща работа
};

// Struct - like representation for Goals
struct GoalType 
{
    const int LoseWeight = 1; // Lose weight
    const int MaintainWeight = 2; // Maintain weight
    const int GainWeight = 3; // Gain weight
};

// BMR Constants
const double BMR_CONSTANT_MEN = 88.362;
const double BMR_WEIGHT_MULTIPLIER_MEN = 13.397;
const double BMR_HEIGHT_MULTIPLIER_MEN = 4.799;
const double BMR_AGE_MULTIPLIER_MEN = 5.677;

const double BMR_CONSTANT_WOMEN = 447.593;
const double BMR_WEIGHT_MULTIPLIER_WOMEN = 9.247;
const double BMR_HEIGHT_MULTIPLIER_WOMEN = 3.098;
const double BMR_AGE_MULTIPLIER_WOMEN = 4.330;

// Activity Coefficients
const double ACTIVITY_VERY_ACTIVE = 1.9;
const double ACTIVITY_ACTIVE = 1.725;
const double ACTIVITY_MODERATE = 1.55;
const double ACTIVITY_LIGHT = 1.375;
const double ACTIVITY_SEDENTARY = 1.2;

// Weight Loss and Gain Constants
const int CALORIES_PER_KG = 7700;
const int DAILY_DEFICIT_OR_SURPLUS_025KG = 275;
const int DAILY_DEFICIT_OR_SURPLUS_050KG = 550;
const int DAILY_DEFICIT_OR_SURPLUS_075KG = 825;
const int DAILY_DEFICIT_OR_SURPLUS_100KG = 1100;

// Macronutrient Constants
const double PROTEIN_CALORIES_PER_GRAM = 4.0;
const double FAT_CALORIES_PER_GRAM = 9.0;
const double CARBOHYDRATE_CALORIES_PER_GRAM = 4.0;

// Macronutrient Ratios (in percentages)
const double MACRO_RATIO_LOSS_PROTEIN = 0.35;
const double MACRO_RATIO_LOSS_FAT = 0.35;
const double MACRO_RATIO_LOSS_CARBOHYDRATES = 0.30;

const double MACRO_RATIO_MAINTAIN_PROTEIN = 0.25;
const double MACRO_RATIO_MAINTAIN_FAT = 0.30;
const double MACRO_RATIO_MAINTAIN_CARBOHYDRATES = 0.45;

const double MACRO_RATIO_GAIN_PROTEIN = 0.40;
const double MACRO_RATIO_GAIN_FAT = 0.25;
const double MACRO_RATIO_GAIN_CARBOHYDRATES = 0.35;

// File Names
const std::string USERS_FILE_NAME = "data/users.csv";
const std::string GOALS_FILE_NAME = "data/goals.csv";
const std::string MEALS_FILE_NAME = "data/meals.csv";
const std::string WORKOUTS_FILE_NAME = "data/workouts.csv";
const std::string DAILY_SUMMARIES_FILE_NAME = "data/dailySummaries.csv";
const std::string MACRONUTRIENT_RATIO_FILE_NAME = "data/macronutrientRatios.csv";

// File Headers
const std::string USERS_FILE_HEADER = "id,first_name,last_name,age,gender,height,weight,activity_level,goal_id,username,password,type,created_on";
const std::string GOALS_FILE_HEADER = "id,type,weekly_change,calorie_adjustment";
const std::string MEALS_FILE_HEADER = "id,name,calories,protein,fat,carbohydrates,created_by,created_on,date";
const std::string WORKOUTS_FILE_HEADER = "id,name,calories_burned,created_by,created_on,date";
const std::string DAILY_SUMMARIES_FILE_HEADER = "id,user_id,date,calories_consumed,calories_burned,recommended_calories,calorie_balance,protein,fat,carbohydrates,created_on";
const std::string MACRONUTRIENT_RATIO_FILE_HEADER = "id,goal_id,protein_ratio,fat_ratio,carbohydrate_ratio";

const char GENTER_TYPES[] = { 'M', 'F' };
const char ACTIVITY_LEVEL_TYPES[] = { '1', '2', '3', '4', '5' };
const char GOAL_TYPES[] = { '1', '2', '3' };
const std::string GOAL_WEEKLY_CHANGES[] = { "0.25", "0.50", "0.75", "1" };
const std::string USER_ACCOUNT_TYPE[] = { "Standard", "Premium" };


// ASCII Art for digits 0-9
const std::string ASCII_DIGITS[10][6] = {
{  // 0
    "  ___  ",
    " / _ \\ ",
    "| | | |",
    "| | | |",
    "| |_| |",
    " \\___/ "
},
{  // 1
    " __ ",
    "/_ |",
    " | |",
    " | |",
    " | |",
    " |_|"
},
{  // 2
    " ___  ",
    "|__ \\ ",
    "   ) |",
    "  / / ",
    " / /_ ",
    "|____|"
},
{  // 3
    " ____  ",
    "|___ \\ ",
    "  __) |",
    " |__ < ",
    " ___) |",
    "|____/ "
},
{  // 4
    " _  _   ",
    "| || |  ",
    "| || |_ ",
    "|__   _|",
    "   | |  ",
    "   |_|  "
},
{  // 5
    " _____ ",
    "| ____|",
    "| |__  ",
    "|___ \\ ",
    " ___) |",
    "|____/ "
},
{  // 6
    "   __  ",
    "  / /  ",
    " / /_  ",
    "| '_ \\ ",
    "| (_) |",
    " \\___/ "
},
{  // 7
    " ______ ",
    "|____  |",
    "    / / ",
    "   / /  ",
    "  / /   ",
    " /_/    "
},
{  // 8
    "  ___  ",
    " / _ \\ ",
    "| (_) |",
    " > _ < ",
    "| (_) |",
    " \\___/ "
},
{  // 9
    "  ___  ",
    " / _ \\ ",
    "| (_) |",
    " \\__, |",
    "   / / ",
    "  /_/  "
}
};

// ASCII Art for separator (comma)
const std::string ASCII_SEPARATOR[6] = {
    "   ",
    "   ",
    "   ",
    "   ",
    " _ ",
    "(_)"
};

const std::string TABULATION = "\t\t\t\t\t";

const int NUMBER_DIGITS = 10;

const int CELL_WIDTH = 20;