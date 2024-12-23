#pragma once

// Struct-like representation for Activity Level
struct ActivityLevel 
{
    const int VeryActive = 0; // Много активен
    const int ActiveJob = 1; // Активна работа
    const int ModerateActivity = 2; // Умерена активност
    const int LightActivity = 3; // Лека активност
    const int SedentaryJob = 4; // Седяща работа
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
const double ACTIVITY_SEDENTARY = 1.2;
const double ACTIVITY_LIGHT = 1.375;
const double ACTIVITY_MODERATE = 1.55;
const double ACTIVITY_ACTIVE = 1.725;
const double ACTIVITY_VERY_ACTIVE = 1.9;

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
const std::string MEALS_FILE_NAME = "../data/meals.csv";
const std::string WORKOUTS_FILE_NAME = "../data/workouts.csv";
const std::string DAILY_SUMMARIES_FILE_NAME = "../data/daily_summaries.csv";
const std::string MACRONUTRIENT_RATIO_FILE_NAME = "../data/macronutrient_ratios.csv";