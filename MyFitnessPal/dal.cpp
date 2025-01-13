#include "include.h"

namespace dal
{
	void readProperty(const std::string& line, size_t& start, size_t& end, std::string& field) 
	{
		end = line.find(',', start);
		field = (end == std::string::npos) ? line.substr(start) : line.substr(start, end - start);
		start = (end == std::string::npos) ? std::string::npos : end + 1;
	}

#pragma region Users

	std::vector<User> readDataFromUsersFile()
	{
		std::vector<User> users;
		std::ifstream file(USERS_FILE_NAME);

		if (!file.is_open())
		{
			std::cerr << "Error: Could not open file " << USERS_FILE_NAME << std::endl;
			return users;
		}

		std::string line;
		// Skip the header line 
		std::getline(file, line);

		while (std::getline(file, line))
		{
			size_t start = 0;
			size_t end = 0;
			User user;

			// Parse each field separated by a comma
			readProperty(line, start, end, user.id);
			readProperty(line, start, end, user.firstName);
			readProperty(line, start, end, user.lastName);
			readProperty(line, start, end, user.age);
			readProperty(line, start, end, user.gender);
			readProperty(line, start, end, user.height);
			readProperty(line, start, end, user.weight);
			readProperty(line, start, end, user.activityLevel);
			readProperty(line, start, end, user.goalId);
			readProperty(line, start, end, user.username);
			readProperty(line, start, end, user.password);
			readProperty(line, start, end, user.type);
			readProperty(line, start, end, user.createdOn);

			// Add the user to the vector
			users.push_back(user);
		}

		file.close();
		return users;
	}

	void writeDataToUsersFile(User user)
	{
        std::ofstream out(USERS_FILE_NAME, std::ios_base::app);
		if (out.is_open())
		{
			out << user.id << ","
				<< user.firstName << ","
				<< user.lastName << ","
				<< user.age << ","
				<< user.gender << ","
				<< user.height << ","
				<< user.weight << ","
				<< user.activityLevel << ","
				<< user.goalId << ","
				<< user.username << ","
				<< user.password << ","
				<< user.type << ","
				<< user.createdOn << "\n";

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
							<< user.firstName << ","
							<< user.lastName << ","
							<< user.age << ","
							<< user.gender << ","
							<< user.height << ","
							<< user.weight << ","
							<< user.activityLevel << ","
							<< user.goalId << ","
							<< user.username << ","
							<< user.password << ","
							<< user.type << ","
							<< user.createdOn << "\n";
					}
				}
				else
				{
					out << updatedUser.id << ","
						<< updatedUser.firstName << ","
						<< updatedUser.lastName << ","
						<< updatedUser.age << ","
						<< updatedUser.gender << ","
						<< updatedUser.height << ","
						<< updatedUser.weight << ","
						<< updatedUser.activityLevel << ","
						<< updatedUser.goalId << ","
						<< updatedUser.username << ","
						<< updatedUser.password << ","
						<< updatedUser.type << ","
						<< updatedUser.createdOn << "\n";
				}
			}
		}
	}

#pragma endregion

#pragma region Goals

	std::vector<Goal> readDataFromGoalsFile()
	{
		std::vector<Goal> goals;
		std::ifstream file(GOALS_FILE_NAME);

		if (!file.is_open())
		{
			std::cerr << "Error: Could not open file " << GOALS_FILE_NAME << std::endl;
			return goals;
		}

		std::string line;
		// Skip the header line 
		std::getline(file, line);

		while (std::getline(file, line))
		{
			size_t start = 0;
			size_t end = 0;
			Goal goal;

			// Parse each field separated by a comma
			readProperty(line, start, end, goal.id);
			readProperty(line, start, end, goal.type);
			readProperty(line, start, end, goal.weeklyChange);
			readProperty(line, start, end, goal.calorieAdjustment);

			// Add the goal to the vector
			goals.push_back(goal);
		}


		file.close();
		return goals;
	}

	void writeDataToGoalsFile(Goal goal)
	{
		std::ofstream out(GOALS_FILE_NAME, std::ios_base::app);
		if (out.is_open())
		{
			out << goal.id << ","
				<< goal.type << ","
				<< goal.weeklyChange << ","
				<< goal.calorieAdjustment << "\n";

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + GOALS_FILE_NAME);
		}
	}

	Goal getGoalById(std::string id)
	{ 
		std::vector<Goal> goals = readDataFromGoalsFile();
		for (Goal goal : goals)
		{
			if (goal.id == id)
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
			if (goal.id == user.goalId)
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
							<< goal.weeklyChange << ","
							<< goal.calorieAdjustment << "\n";
					}
				}
				else
				{
					out << updatedGoal.id << ","
						<< updatedGoal.type << ","
						<< updatedGoal.weeklyChange << ","
						<< updatedGoal.calorieAdjustment << "\n";
				}
			}
		}

	}

#pragma endregion

#pragma region Meals

	std::vector<Meal> readDataFromMealsFile()
	{
		std::vector<Meal> meals;
		std::ifstream file(MEALS_FILE_NAME);

		if (!file.is_open())
		{
			std::cerr << "Error: Could not open file " << MEALS_FILE_NAME << std::endl;
			return meals;
		}

		std::string line;
		// Skip the header line 
		std::getline(file, line);

		while (std::getline(file, line))
		{
			size_t start = 0;
			size_t end = 0;
			Meal meal;

			// Parse each field separated by a comma
			readProperty(line, start, end, meal.id);
			readProperty(line, start, end, meal.name);
			readProperty(line, start, end, meal.calories);
			readProperty(line, start, end, meal.protein);
			readProperty(line, start, end, meal.fat);
			readProperty(line, start, end, meal.carbohydrates);
			readProperty(line, start, end, meal.createdBy);
			readProperty(line, start, end, meal.createdOn);
			readProperty(line, start, end, meal.date);

			// Add the meal to the vector
			meals.push_back(meal);
		}

		file.close();
		return meals;
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
				<< meal.createdBy << ","
				<< meal.createdOn << ","
				<< meal.date << "\n";

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

	std::vector<Meal> getMealsByUserId(std::string id, bool forToday, int days)
	{
		std::vector<Meal> meals = readDataFromMealsFile(), result;

		for (Meal meal : meals)
		{
			if (meal.createdBy == id && ((forToday) ? meal.date == tools::getDatetime("%d.%m.%Y", days) : true))
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
							<< meal.createdBy << ","
							<< meal.createdOn << ","
							<< meal.date << "\n";
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
						<< updatedMeal.createdBy << ","
						<< updatedMeal.createdOn << ","
						<< updatedMeal.date << "\n";
				}
			}
		}
	
	}

#pragma endregion

#pragma region Workouts

	std::vector<Workout> readDataFromWorkoutsFile()
	{
		std::vector<Workout> workouts;
		std::ifstream file(WORKOUTS_FILE_NAME);

		if (!file.is_open())
		{
			std::cerr << "Error: Could not open file " << WORKOUTS_FILE_NAME << std::endl;
			return workouts;
		}

		std::string line;
		// Skip the header line 
		std::getline(file, line);

		while (std::getline(file, line))
		{
			size_t start = 0;
			size_t end = 0;
			Workout workout;

			// Parse each field separated by a comma
			readProperty(line, start, end, workout.id);
			readProperty(line, start, end, workout.name);
			readProperty(line, start, end, workout.caloriesBurned);
			readProperty(line, start, end, workout.createdBy);
			readProperty(line, start, end, workout.createdOn);
			readProperty(line, start, end, workout.date);

			// Add the workout to the vector
			workouts.push_back(workout);
		}

		file.close();
		return workouts;
	}

	void writeDataToWorkoutsFile(Workout workout)
	{
		std::ofstream out(WORKOUTS_FILE_NAME, std::ios_base::app);
		if (out.is_open())
		{ 
			out << workout.id << ","
				<< workout.name << ","
				<< workout.caloriesBurned << ","
				<< workout.createdBy << ","
				<< workout.createdOn << ","
				<< workout.date << "\n"; 

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

	std::vector<Workout> getWorkoutsByUserId(std::string id, bool forToday, int days)
	{
		std::vector<Workout> workouts = readDataFromWorkoutsFile(), result;

		for (Workout workout : workouts)
		{
			if (workout.createdBy == id && ((forToday) ? workout.date == tools::getDatetime("%d.%m.%Y", days) : true))
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
							<< workout.caloriesBurned << ","
							<< workout.createdBy << ","
							<< workout.createdOn << ","
							<< workout.date << "\n";
					}
				}
				else
				{
					out << updatedWorkout.id << ","
						<< updatedWorkout.name << ","
						<< updatedWorkout.caloriesBurned << ","
						<< updatedWorkout.createdBy << ","
						<< updatedWorkout.createdOn << "," 
						<< updatedWorkout.date << "\n";
				}
			}
		}
	}	

#pragma endregion

#pragma region DailySummaries

	std::vector<DailySummary> readDataFromDailySummariesFile()
	{
		std::vector<DailySummary> dailySummaries;
		std::ifstream file(DAILY_SUMMARIES_FILE_NAME);

		if (!file.is_open())
		{
			std::cerr << "Error: Could not open file " << DAILY_SUMMARIES_FILE_NAME << std::endl;
			return dailySummaries;
		}

		std::string line;
		// Skip the header line 
		std::getline(file, line);

		while (std::getline(file, line))
		{
			size_t start = 0;
			size_t end = 0;
			DailySummary dailySummary;

			// Parse each field separated by a comma
			readProperty(line, start, end, dailySummary.id);
			readProperty(line, start, end, dailySummary.userId);
			readProperty(line, start, end, dailySummary.date);
			readProperty(line, start, end, dailySummary.caloriesConsumed);
			readProperty(line, start, end, dailySummary.caloriesBurned);
			readProperty(line, start, end, dailySummary.recommendedCalories);
			readProperty(line, start, end, dailySummary.calorieBalance);
			readProperty(line, start, end, dailySummary.protein);
			readProperty(line, start, end, dailySummary.fat);
			readProperty(line, start, end, dailySummary.carbohydrates);
			readProperty(line, start, end, dailySummary.createdOn);

			// Add the daily summary to the vector
			dailySummaries.push_back(dailySummary);
		}

		file.close();
		return dailySummaries;
	}

	void writeDataToDailySummariesFile(DailySummary dailySummary)
	{
		std::ofstream out(DAILY_SUMMARIES_FILE_NAME, std::ios_base::app);
		if (out.is_open())
		{
			out << dailySummary.id << ","
				<< dailySummary.userId << ","
				<< dailySummary.date << ","
				<< dailySummary.caloriesConsumed << ","
				<< dailySummary.caloriesBurned << ","
				<< dailySummary.recommendedCalories << ","
				<< dailySummary.calorieBalance << ","
				<< dailySummary.protein << ","
				<< dailySummary.fat << ","
				<< dailySummary.carbohydrates << ","
				<< dailySummary.createdOn << "\n";

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + DAILY_SUMMARIES_FILE_NAME);
		}
	}

	std::vector<DailySummary> getDailySummariesByUserId(std::string id)
	{
		std::vector<DailySummary> dailySummaries = readDataFromDailySummariesFile(), result;

		for (DailySummary dailySummary : dailySummaries)
		{
			if (dailySummary.userId == id)
			{
				result.push_back(dailySummary);
			}
		}

		return result;
	}

	DailySummary getDailySummaryByUserIdToday(std::string id, int days)
	{
		std::vector<DailySummary> dailySummaries = readDataFromDailySummariesFile();

		for (DailySummary dailySummary : dailySummaries)
		{
			if (dailySummary.userId == id && dailySummary.date == tools::getDatetime("%d.%m.%Y", days))
			{
				return dailySummary;
			}
		}
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
							<< dailySummary.userId << ","
							<< dailySummary.date << ","
							<< dailySummary.caloriesConsumed << ","
							<< dailySummary.caloriesBurned << ","
							<< dailySummary.recommendedCalories << ","
							<< dailySummary.calorieBalance << ","
							<< dailySummary.protein << ","
							<< dailySummary.fat << ","
							<< dailySummary.carbohydrates << ","
							<< dailySummary.createdOn << "\n";
					}
				}
				else
				{
					out << updatedDailySummary.id << ","
						<< updatedDailySummary.userId << ","
						<< updatedDailySummary.date << ","
						<< updatedDailySummary.caloriesConsumed << ","
						<< updatedDailySummary.caloriesBurned << ","
						<< updatedDailySummary.recommendedCalories << ","
						<< updatedDailySummary.calorieBalance << ","
						<< updatedDailySummary.protein << ","
						<< updatedDailySummary.fat << ","
						<< updatedDailySummary.carbohydrates << ","
						<< updatedDailySummary.createdOn << "\n";
				}
			}
		}
	}

#pragma endregion
}
