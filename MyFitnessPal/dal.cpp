#include "include.h"

namespace dal
{
#pragma region Users

    std::vector<User> readDataFromUsersFile()
    {
        std::vector<User> allData;
        std::ifstream file(USERS_FILE_NAME);
        std::string line;
        int counter = -1;
        if (file.is_open())
        {
            while (std::getline(file, line))
            {
                if (counter > -1)
                {
                    counter = 0;
                    User data;
                    for (size_t i = 0; i < line.size(); i++)
                    {
                        if (line[i] == ',' && counter < 12)
                        {
                            counter++;
                            line.erase(i, 0);
                        }
						else if (counter == 0)
						{
							data.id += line[i];
						}
                        else if (counter == 1)
                        {
							data.first_name += line[i];
						}
						else if (counter == 2)
						{
							data.last_name += line[i];
						}
                        else if (counter == 3)
                        {
							data.age += line[i];
                        }
                        else if (counter == 4)
                        {
							data.gender += line[i];
                        }
						else if (counter == 5)
						{
							data.height += line[i];
                        }
						else if (counter == 6)
						{
							data.weight += line[i];
						}
						else if (counter == 7)
						{
							data.activity_level += line[i];
						}
						else if (counter == 8)
						{
							data.goal_id += line[i];
						}
						else if (counter == 9)
						{
							data.username += line[i];
						}
						else if (counter == 10)
						{
							data.password += line[i];
						}
						else if (counter == 11)
						{
							data.type += line[i];
						}
						else if (counter == 12)
						{
							data.created_on += line[i];
						}
                    } 
					allData.push_back(data);
                }
                counter++;
            }
            file.close();
        }
        return allData;
    }

	void writeDataToUsersFile(User user)
	{
        std::ofstream out(USERS_FILE_NAME, std::ios_base::app);
		if (out.is_open())
		{
			out << user.id << ","
				<< user.first_name << ","
				<< user.last_name << ","
				<< user.age << ","
				<< user.gender << ","
				<< user.height << ","
				<< user.weight << ","
				<< user.activity_level << ","
				<< user.goal_id << ","
				<< user.username << ","
				<< user.password << ","
				<< user.type << ","
				<< user.created_on << "\n";

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + USERS_FILE_NAME);
		}
	}

	User findUserByUsernameAndPassword(std::string username, std::string password)
	{
		std::vector<User> allUsers = readDataFromUsersFile();
		for (User user : allUsers)
		{
			if (user.username == username && user.password == password)
			{
				return user;
			}
		}
	}

	User getUserById(std::string id)
	{
		std::vector<User> allUsers = readDataFromUsersFile();
		for (User user : allUsers)
		{
			if (user.id == id)
			{
				return user;
			}
		}
	}

	void updateOrDeleteUser(User user, bool isUpdate)
	{
		std::vector<User> allUsers = readDataFromUsersFile();

		std::ofstream out(USERS_FILE_NAME, std::ios_base::trunc);
		if (out.is_open())
		{
			out << USERS_FILE_HEADER << "\n";
			for (const User& updatedUser : allUsers)
			{
				if (updatedUser.id == user.id)
				{
					if (isUpdate)
					{
						out << user.id << ","
							<< user.first_name << ","
							<< user.last_name << ","
							<< user.age << ","
							<< user.gender << ","
							<< user.height << ","
							<< user.weight << ","
							<< user.activity_level << ","
							<< user.goal_id << ","
							<< user.username << ","
							<< user.password << ","
							<< user.type << ","
							<< user.created_on << "\n";
					}
				}
				else
				{
					out << updatedUser.id << ","
						<< updatedUser.first_name << ","
						<< updatedUser.last_name << ","
						<< updatedUser.age << ","
						<< updatedUser.gender << ","
						<< updatedUser.height << ","
						<< updatedUser.weight << ","
						<< updatedUser.activity_level << ","
						<< updatedUser.goal_id << ","
						<< updatedUser.username << ","
						<< updatedUser.password << ","
						<< updatedUser.type << ","
						<< updatedUser.created_on << "\n";
				}
			}
		}
	}

#pragma endregion

#pragma region Goals

	std::vector<Goal> readDataFromGoalsFile()
	{
		std::vector<Goal> allData;
		std::ifstream file(GOALS_FILE_NAME);
		std::string line;
		int counter = -1;
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				if (counter > -1)
				{
					counter = 0;
					Goal data;
					for (size_t i = 0; i < line.size(); i++)
					{
						if (line[i] == ',' && counter < 3)
						{
							counter++;
							line.erase(i, 0);
						}
						else if (counter == 0)
						{
							data.id += line[i];
						}
						else if (counter == 1)
						{
							data.type += line[i];
						}
						else if (counter == 2)
						{
							data.weekly_change += line[i];
						}
						else if (counter == 3)
						{
							data.calorie_adjustment += line[i];
						}
					}
					allData.push_back(data);
				}
				counter++;
			}
			file.close();
		}
		return allData;
	}

	void writeDataToGoalsFile(Goal goal)
	{
		std::ofstream out(GOALS_FILE_NAME, std::ios_base::app);
		if (out.is_open())
		{
			out << goal.id << ","
				<< goal.type << ","
				<< goal.weekly_change << ","
				<< goal.calorie_adjustment << "\n";

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + GOALS_FILE_NAME);
		}
	}

	Goal getGoalById(std::string id)
	{
		User user = getUserById(id);
		std::vector<Goal> goals = readDataFromGoalsFile();
		for (Goal goal : goals)
		{
			if (goal.id == user.goal_id)
			{
				return goal;
			}
		}
	}

	std::vector<Goal> getGoalsByUserId(std::string id)
	{
		User user = getUserById(id);
		std::vector<Goal> goals = readDataFromGoalsFile(), result;

		for (Goal goal : goals)
		{
			if (goal.id == user.goal_id)
			{
				result.push_back(goal);
			}
		}

		return result;
	}

	void updateOrDeleteGoal(Goal goal, bool isUpdate)
	{
		std::vector<Goal> allGoals = readDataFromGoalsFile();

		std::ofstream out(GOALS_FILE_NAME, std::ios_base::trunc);
		if (out.is_open())
		{
			out << GOALS_FILE_HEADER << "\n";
			for (const Goal& updatedGoal : allGoals)
			{
				if (updatedGoal.id == goal.id)
				{
					if (isUpdate)
					{
						out << goal.id << ","
							<< goal.type << ","
							<< goal.weekly_change << ","
							<< goal.calorie_adjustment << "\n";
					}
				}
				else
				{
					out << updatedGoal.id << ","
						<< updatedGoal.type << ","
						<< updatedGoal.weekly_change << ","
						<< updatedGoal.calorie_adjustment << "\n";
				}
			}
		}

	}

#pragma endregion

#pragma region Meals

	std::vector<Meal> readDataFromMealsFile()
	{
		std::vector<Meal> allData;
		std::ifstream file(MEALS_FILE_NAME);
		std::string line;
		int counter = -1;
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				if (counter > -1)
				{
					counter = 0;
					Meal data;
					for (size_t i = 0; i < line.size(); i++)
					{
						if (line[i] == ',' && counter < 7)
						{
							counter++;
							line.erase(i, 0);
						}
						else if (counter == 0)
						{
							data.id += line[i];
						}
						else if (counter == 1)
						{
							data.name += line[i];
						}
						else if (counter == 2)
						{
							data.calories += line[i];
						}
						else if (counter == 3)
						{
							data.protein += line[i];
						}
						else if (counter == 4)
						{
							data.fat += line[i];
						}
						else if (counter == 5)
						{
							data.carbohydrates += line[i];
						}
						else if (counter == 6)
						{
							data.created_by += line[i];
						}
						else if (counter == 7)
						{
							data.created_on += line[i];
						}
					}
					allData.push_back(data);
				}
				counter++;
			}
			file.close();
		}
		return allData;
	}

	void writeDataToMealsFile(Meal meal)
	{
		std::ofstream out(MEALS_FILE_NAME, std::ios_base::app);
		if (out.is_open())
		{
			out << meal.id << ","
				<< meal.name << ","
				<< meal.calories << ","
				<< meal.protein << ","
				<< meal.fat << ","
				<< meal.carbohydrates << ","
				<< meal.created_by << ","
				<< meal.created_on << "\n";

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + MEALS_FILE_NAME);
		}
	}

	Meal getMealById(std::string id)
	{
		std::vector<Meal> allMeals = readDataFromMealsFile();
		for (Meal meal : allMeals)
		{
			if (meal.id == id)
			{
				return meal;
			}
		}
	}	

	std::vector<Meal> getMealsByUserId(std::string id)
	{
		std::vector<Meal> meals = readDataFromMealsFile(), result;

		for (Meal meal : meals)
		{
			if (meal.created_by == id)
			{
				result.push_back(meal);
			}
		}

		return result;
	}

	void updateOrDeleteMeal(Meal meal, bool isUpdate)
	{
		std::vector<Meal> allMeals = readDataFromMealsFile();

		std::ofstream out(MEALS_FILE_NAME, std::ios_base::trunc);
		if (out.is_open())
		{
			out << MEALS_FILE_HEADER << "\n";
			for (const Meal& updatedMeal : allMeals)
			{
				if (updatedMeal.id == meal.id)
				{
					if (isUpdate)
					{
						out << meal.id << ","
							<< meal.name << ","
							<< meal.calories << ","
							<< meal.protein << ","
							<< meal.fat << ","
							<< meal.carbohydrates << ","
							<< meal.created_by << ","
							<< meal.created_on << "\n";
					}
				}
				else
				{
					out << updatedMeal.id << ","
						<< updatedMeal.name << ","
						<< updatedMeal.calories << ","
						<< updatedMeal.protein << ","
						<< updatedMeal.fat << ","
						<< updatedMeal.carbohydrates << ","
						<< updatedMeal.created_by << ","
						<< updatedMeal.created_on << "\n";
				}
			}
		}
	
	}

#pragma endregion

#pragma region Workouts

	std::vector<Workout> readDataFromWorkoutsFile()
	{
		std::vector<Workout> allData;
		std::ifstream file(WORKOUTS_FILE_NAME);
		std::string line;
		int counter = -1;
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				if (counter > -1)
				{
					counter = 0;
					Workout data;
					for (size_t i = 0; i < line.size(); i++)
					{
						if (line[i] == ',' && counter < 4)
						{
							counter++;
							line.erase(i, 0);
						}
						else if (counter == 0)
						{
							data.id += line[i];
						}
						else if (counter == 1)
						{
							data.name += line[i];
						}
						else if (counter == 2)
						{
							data.calories_burned += line[i];
						}
						else if (counter == 3)
						{
							data.created_by += line[i];
						}
						else if (counter == 4)
						{
							data.created_on += line[i];
						}
					}
					allData.push_back(data);
				}
				counter++;
			}
			file.close();
		}
		return allData;
	}

	void writeDataToWorkoutsFile(Workout workout)
	{
		std::ofstream out(WORKOUTS_FILE_NAME, std::ios_base::app);
		if (out.is_open())
		{ 
			out << workout.id << ","
				<< workout.name << ","
				<< workout.calories_burned << ","
				<< workout.created_by << ","
				<< workout.created_on << "\n"; 

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + WORKOUTS_FILE_NAME);
		}
	}

	Workout getWorkoutById(std::string id)
	{
		std::vector<Workout> allWorkouts = readDataFromWorkoutsFile();
		for (Workout workout : allWorkouts)
		{
			if (workout.id == id)
			{
				return workout;
			}
		}
	}

	std::vector<Workout> getWorkoutsByUserId(std::string id)
	{
		std::vector<Workout> workouts = readDataFromWorkoutsFile(), result;

		for (Workout workout : workouts)
		{
			if (workout.created_by == id)
			{
				result.push_back(workout);
			}
		}

		return result;
	}

	void updateOrDeleteWorkout(Workout workout, bool isUpdate)
	{
		std::vector<Workout> allWorkouts = readDataFromWorkoutsFile();

		std::ofstream out(WORKOUTS_FILE_NAME, std::ios_base::trunc);
		if (out.is_open())
		{
			out << WORKOUTS_FILE_HEADER << "\n";
			for (const Workout& updatedWorkout : allWorkouts)
			{
				if (updatedWorkout.id == workout.id)
				{
					if (isUpdate)
					{
						out << workout.id << ","
							<< workout.name << ","
							<< workout.calories_burned << ","
							<< workout.created_by << ","
							<< workout.created_on << "\n";
					}
				}
				else
				{
					out << updatedWorkout.id << ","
						<< updatedWorkout.name << ","
						<< updatedWorkout.calories_burned << ","
						<< updatedWorkout.created_by << ","
						<< updatedWorkout.created_on << "\n";
				}
			}
		}
	}	

#pragma endregion

#pragma region DailySummaries

	std::vector<DailySummary> readDataFromDailySummariesFile()
	{
		std::vector<DailySummary> allData;
		std::ifstream file(DAILY_SUMMARIES_FILE_NAME);
		std::string line;
		int counter = -1;
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				if (counter > -1)
				{
					counter = 0;
					DailySummary data;
					for (size_t i = 0; i < line.size(); i++)
					{
						if (line[i] == ',' && counter < 10)
						{
							counter++;
							line.erase(i, 0);
						}
						else if (counter == 0)
						{
							data.id += line[i];
						}
						else if (counter == 1)
						{
							data.user_id += line[i];
						}
						else if (counter == 2)
						{
							data.date += line[i];
						}
						else if (counter == 3)
						{
							data.calories_consumed += line[i];
						}
						else if (counter == 4)
						{
							data.calories_burned += line[i];
						}
						else if (counter == 5)
						{
							data.recommended_calories += line[i];
						}
						else if (counter == 6)
						{
							data.calorie_balance += line[i];
						}
						else if (counter == 7)
						{
							data.protein += line[i];
						}
						else if (counter == 8)
						{
							data.fat += line[i];
						}
						else if (counter == 9)
						{
							data.carbohydrates += line[i];
						}
						else if (counter == 10)
						{
							data.created_on += line[i];
						}
					}
					allData.push_back(data);
				}
				counter++;
			}
			file.close();
		}
		return allData;
	}

	void writeDataToDailySummariesFile(DailySummary dailySummary)
	{
		std::ofstream out(DAILY_SUMMARIES_FILE_NAME, std::ios_base::app);
		if (out.is_open())
		{
			out << dailySummary.id << ","
				<< dailySummary.user_id << ","
				<< dailySummary.date << ","
				<< dailySummary.calories_consumed << ","
				<< dailySummary.calories_burned << ","
				<< dailySummary.recommended_calories << ","
				<< dailySummary.calorie_balance << ","
				<< dailySummary.protein << ","
				<< dailySummary.fat << ","
				<< dailySummary.carbohydrates << ","
				<< dailySummary.created_on << "\n";

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + DAILY_SUMMARIES_FILE_NAME);
		}
	}

	std::vector<DailySummary> getDailySummaryByUserId(std::string id)
	{
		std::vector<DailySummary> dailySummaries = readDataFromDailySummariesFile(), result;

		for (DailySummary dailySummary : dailySummaries)
		{
			if (dailySummary.user_id == id)
			{
				result.push_back(dailySummary);
			}
		}

		return result;
	}

	void updateOrDeleteDailySummary(DailySummary dailySummary, bool isUpdate)
	{
		std::vector<DailySummary> allDailySummaries = readDataFromDailySummariesFile();

		std::ofstream out(DAILY_SUMMARIES_FILE_NAME, std::ios_base::trunc);
		if (out.is_open())
		{
			out << DAILY_SUMMARIES_FILE_HEADER << "\n";
			for (const DailySummary& updatedDailySummary : allDailySummaries)
			{
				if (updatedDailySummary.id == dailySummary.id)
				{
					if (isUpdate)
					{
						out << dailySummary.id << ","
							<< dailySummary.user_id << ","
							<< dailySummary.date << ","
							<< dailySummary.calories_consumed << ","
							<< dailySummary.calories_burned << ","
							<< dailySummary.recommended_calories << ","
							<< dailySummary.calorie_balance << ","
							<< dailySummary.protein << ","
							<< dailySummary.fat << ","
							<< dailySummary.carbohydrates << ","
							<< dailySummary.created_on << "\n";
					}
				}
				else
				{
					out << updatedDailySummary.id << ","
						<< updatedDailySummary.user_id << ","
						<< updatedDailySummary.date << ","
						<< updatedDailySummary.calories_consumed << ","
						<< updatedDailySummary.calories_burned << ","
						<< updatedDailySummary.recommended_calories << ","
						<< updatedDailySummary.calorie_balance << ","
						<< updatedDailySummary.protein << ","
						<< updatedDailySummary.fat << ","
						<< updatedDailySummary.carbohydrates << ","
						<< updatedDailySummary.created_on << "\n";
				}
			}
		}
	}

#pragma endregion

#pragma region MacronutrientRatios

	std::vector<MacronutrientRatio> readDataFromMacronutrientRatiosFile()
	{
		std::vector<MacronutrientRatio> allData;
		std::ifstream file(MACRONUTRIENT_RATIO_FILE_NAME);
		std::string line;
		int counter = -1;
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				if (counter > -1)
				{
					counter = 0;
					MacronutrientRatio data;
					for (size_t i = 0; i < line.size(); i++)
					{
						if (line[i] == ',' && counter < 2)
						{
							counter++;
							line.erase(i, 0);
						}
						else if (counter == 0)
						{
							data.id += line[i];
						}
						else if (counter == 1)
						{
							data.goal_id += line[i];
						}
						else if (counter == 2)
						{
							data.protein_ratio += line[i];
						}
					}
					allData.push_back(data);
				}
				counter++;
			}
			file.close();
		}
		return allData;
	}

	void writeDataToMacronutrientRatioFile(MacronutrientRatio macronutrientRatio)
	{
		std::ofstream out(MACRONUTRIENT_RATIO_FILE_NAME, std::ios_base::app);
		if (out.is_open())
		{
			out << macronutrientRatio.id << ","
				<< macronutrientRatio.goal_id << ","
				<< macronutrientRatio.protein_ratio << "\n";

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + MACRONUTRIENT_RATIO_FILE_NAME);
		}
	}

	std::vector<MacronutrientRatio> getMacronutrientRatiosByUserId(std::string id)
	{
		User user = getUserById(id);
		std::vector<MacronutrientRatio> macronutrientRatios = readDataFromMacronutrientRatiosFile(), result;

		for (MacronutrientRatio macronutrientRatio : macronutrientRatios)
		{
			if (macronutrientRatio.goal_id == user.goal_id)
			{
				result.push_back(macronutrientRatio);
			}
		}

		return result;
	}

	void updateOrDeleteMacronutrientRatio(MacronutrientRatio macronutrientRatio, bool isUpdate)
	{
		std::vector<MacronutrientRatio> allMacronutrientRatios = readDataFromMacronutrientRatiosFile();

		std::ofstream out(MACRONUTRIENT_RATIO_FILE_NAME, std::ios_base::trunc);
		if (out.is_open())
		{
			out << MACRONUTRIENT_RATIO_FILE_HEADER << "\n";
			for (const MacronutrientRatio& updatedMacronutrientRatio : allMacronutrientRatios)
			{
				if (updatedMacronutrientRatio.id == macronutrientRatio.id)
				{
					if (isUpdate)
					{
						out << macronutrientRatio.id << ","
							<< macronutrientRatio.goal_id << ","
							<< macronutrientRatio.protein_ratio << "\n";
					}
				}
				else
				{
					out << updatedMacronutrientRatio.id << ","
						<< updatedMacronutrientRatio.goal_id << ","
						<< updatedMacronutrientRatio.protein_ratio << "\n";
				}
			}
		}
	}

#pragma endregion
}
