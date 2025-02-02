#pragma once

// BMR Constants
const float BMR_CONSTANT_MEN = 88.362;
const float BMR_WEIGHT_MULTIPLIER_MEN = 13.397;
const float BMR_HEIGHT_MULTIPLIER_MEN = 4.799;
const float BMR_AGE_MULTIPLIER_MEN = 5.677;

const float BMR_CONSTANT_WOMEN = 447.593;
const float BMR_WEIGHT_MULTIPLIER_WOMEN = 9.247;
const float BMR_HEIGHT_MULTIPLIER_WOMEN = 3.098;
const float BMR_AGE_MULTIPLIER_WOMEN = 4.330;

// Activity Coefficients
const float ACTIVITY_VERY_ACTIVE = 1.9;
const float ACTIVITY_ACTIVE = 1.725;
const float ACTIVITY_MODERATE = 1.55;
const float ACTIVITY_LIGHT = 1.375;
const float ACTIVITY_SEDENTARY = 1.2;

// Weight Loss and Gain Constants
const int CALORIES_PER_KG = 7700;
const int DAILY_DEFICIT_OR_SURPLUS_025KG = 275;
const int DAILY_DEFICIT_OR_SURPLUS_050KG = 550;
const int DAILY_DEFICIT_OR_SURPLUS_075KG = 825;
const int DAILY_DEFICIT_OR_SURPLUS_100KG = 1100;

// Macronutrient Constants
const float PROTEIN_CALORIES_PER_GRAM = 4.0;
const float FAT_CALORIES_PER_GRAM = 9.0;
const float CARBOHYDRATE_CALORIES_PER_GRAM = 4.0;

// Macronutrient Ratios (in percentages)
const float MACRO_RATIO_LOSS_PROTEIN = 0.35;
const float MACRO_RATIO_LOSS_FAT = 0.35;
const float MACRO_RATIO_LOSS_CARBOHYDRATES = 0.30;

const float MACRO_RATIO_MAINTAIN_PROTEIN = 0.25;
const float MACRO_RATIO_MAINTAIN_FAT = 0.30;
const float MACRO_RATIO_MAINTAIN_CARBOHYDRATES = 0.45;

const float MACRO_RATIO_GAIN_PROTEIN = 0.40;
const float MACRO_RATIO_GAIN_FAT = 0.25;
const float MACRO_RATIO_GAIN_CARBOHYDRATES = 0.35;

// File Names
const std::string USERS_FILE_NAME = "data/users.csv";
const std::string GOALS_FILE_NAME = "data/goals.csv";
const std::string MEALS_FILE_NAME = "data/meals.csv";
const std::string WORKOUTS_FILE_NAME = "data/workouts.csv";
const std::string DAILY_SUMMARIES_FILE_NAME = "data/dailySummaries.csv";

// File Headers
const std::string USERS_FILE_HEADER = "id,first_name,last_name,age,gender,height,weight,activity_level,goal_id,username,password,type,created_on";
const std::string GOALS_FILE_HEADER = "id,type,weekly_change,calorie_adjustment";
const std::string MEALS_FILE_HEADER = "id,name,calories,protein,fat,carbohydrates,created_by,created_on,date";
const std::string WORKOUTS_FILE_HEADER = "id,name,calories_burned,created_by,created_on,date";
const std::string DAILY_SUMMARIES_FILE_HEADER = "id,user_id,date,calories_consumed,calories_burned,recommended_calories,calorie_balance,protein,fat,carbohydrates,created_on";

const std::string GENDER_TYPES[] = { "M", "F" };
const std::string ACTIVITY_LEVEL_TYPES[] = { "1", "2", "3", "4", "5" };
const std::string GOAL_TYPES[] = { "1", "2", "3" };
const std::string GOAL_WEEKLY_CHANGES[] = { "0.25", "0.5", "0.75", "1" };
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

const std::string INVALID_MSG = "Invalid input. Please try again!";

// Constants for min and mas width and height
const unsigned MIN_MEASUREMENTS = 1;
const unsigned MAX_MEASUREMENTS = 300;

// Constants for min and max age
const unsigned MIN_AGE = 1;
const unsigned MAX_AGE = 120;

// Constants for min and max kalories and grams
const unsigned MIN_CALORIES_GRAMS = 0;
const unsigned MAX_CALORIES_GRAMS = 10000;

const char DATE_FORMAT[] = "%d.%m.%Y";
const char DATETIME_FORMAT[] = "%d.%m.%Y %T";