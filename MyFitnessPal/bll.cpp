#include "include.h"

namespace bll
{
	void signUp()
	{
		User user;
		user.id = tools::generateGUID();
		ActivityLevel activityLevel;
		Goal goal;
		GoalType goalType;
		goal.id = tools::generateGUID();
		user.goal_id = goal.id;

		std::cout << "Enter your first name: ";
		std::getline(std::cin, user.first_name);
		std::cout << "Enter your last name: ";
		std::getline(std::cin, user.last_name);

		std::cout << "Enter your age: ";
		std::cin >> user.age;

		std::cout << "Enter your gender [M/F]: ";
		user.gender = enterValidType(GENTER_TYPES, 2, "Invalid input. Please enter a valid gender [M/F]: ");

		std::cout << "Enter your height (in cm): ";
		std::cin >> user.height;
		std::cout << "Enter your weight (in kg): ";
		std::cin >> user.weight;
		std::cout << std::endl;

		std::cout << "1. VeryActive" << std::endl;
		std::cout << "2. ActiveJob" << std::endl;
		std::cout << "3. ModerateActivity" << std::endl;
		std::cout << "4. LightActivity" << std::endl;
		std::cout << "5. SedentaryJob" << std::endl;
		std::cout << "Enter your activity level [1-5]: ";
		user.activity_level = enterValidType(ACTIVITY_LEVEL_TYPES, 5, "Invalid input. Please enter a valid activity level [1-5]: ");

		std::cout << "1. LoseWeight" << std::endl;
		std::cout << "2. MaintainWeight" << std::endl;
		std::cout << "3. GainWeight" << std::endl;
		std::cout << "Enter your goal type [1-3]: ";
		goal.type = enterValidType(GOAL_TYPES, 3, "Invalid input. Please enter a valid goal type [1-3]: ");
		
		if (goal.type != '2')
		{
			std::cout << "Enter your weekly change [0.25, 0.5, 0.75, 1] in kg: ";
			goal.weekly_change = enterValidType(GOAL_WEEKLY_CHANGES, 4, "Invalid input. Please enter a valid weekly change [0.25, 0.5, 0.75, 1]: ");
		
			if (goal.weekly_change == 0.25f)
			{
				goal.calorie_adjustment = DAILY_DEFICIT_OR_SURPLUS_025KG;
			}
			else if (goal.weekly_change == 0.50f)
			{
				goal.calorie_adjustment = DAILY_DEFICIT_OR_SURPLUS_050KG;
			}
			else if (goal.weekly_change == 0.75f)
			{
				goal.calorie_adjustment = DAILY_DEFICIT_OR_SURPLUS_075KG;
			}
			else if (goal.weekly_change == 1.00f)
			{
				goal.calorie_adjustment = DAILY_DEFICIT_OR_SURPLUS_100KG;
			}
		}
		std::cout << "Enter your type [Standard/Premium]: ";
		user.type = enterValidType(USER_ACCOUNT_TYPE, 2, "Invalid input. Please enter a valid type [Standard/Premium]: ");

        std::cin.ignore();
        std::cout << "Enter your username: ";
        std::getline(std::cin, user.username);

        std::cout << "Enter your password: ";
        std::getline(std::cin, user.password);

		user.password = tools::passwordHash(user.password);
		user.created_on = tools::getDatetime(); 
		dal::writeDataToGoalsFile(goal);
		dal::writeDataToUsersFile(user);
	}

	void signIn()
	{
		std::string username;
		std::string password;
		std::cout << "Enter your username: ";
		std::getline(std::cin, username);
		std::cout << "Enter your password: ";
		std::getline(std::cin, password);
		password = tools::passwordHash(password);
		User findUser = dal::findUserByUsernameAndPassword(username, password);
        if (findUser.id != "")
        {
			std::cout << "You have successfully logged in!" << std::endl;
			std::cout << "Welcome, " << findUser.first_name << " " << findUser.last_name << "!" << std::endl;
			std::cout << "To add a meal press 1" << std::endl;
			std::cout << "To add a workout press 2" << std::endl;
			std::cout << "To exit press E" << std::endl;

			char input;
			while (true) 
			{
				input = std::cin.get(); // Read a single character

				if (input == '1')
				{
					addMealForUser(findUser);
				}
				else if (input == '2')
				{
					addWorkoutForUser(findUser);
				}

				if (input == 'E' || input == 'e') 
				{
					break;
				}
			}
		}
		else
		{
			std::cout << "Invalid username or password!" << std::endl;
		}
	}

	char enterValidType(const char types[], size_t typeSize, std::string errorMsg)
	{
		char type;
		while (true)
		{
			std::cin >> type;

			for (size_t i = 0; i < typeSize; i++)
			{
				if (type == types[i])
				{
					return type;
				}
			}

			std::cout << errorMsg;
		}
	}

	float enterValidType(const float types[], size_t typeSize, std::string errorMsg)
	{
		float type;
		while (true)
		{
			std::cin >> type;

			for (size_t i = 0; i < typeSize; i++)
			{
				if (type == types[i])
				{
					return type;
				}
			}

			std::cout << errorMsg;
		}
	}

	std::string enterValidType(const std::string types[], size_t typeSize, std::string errorMsg)
	{
		std::string type;
		while (true)
		{
			std::cin >> type;

			for (size_t i = 0; i < typeSize; i++)
			{
				if (type == types[i])
				{
					return type;
				}
			}

			std::cout << errorMsg;
		}
	}

	void addMealForUser(User user)
	{
		Meal meal;
		meal.id = tools::generateGUID();
		meal.created_by = user.id;
		std::cout << "Enter the name of the meal: ";
		std::getline(std::cin, meal.name);
		std::cout << "Enter the calories of the meal: ";
		std::cin >> meal.calories;
		std::cout << "Enter the protein content of the meal: ";
		std::cin >> meal.protein;
		std::cout << "Enter the fat content of the meal: ";
		std::cin >> meal.fat;
		std::cout << "Enter the carbohydrates content of the meal: ";
		std::cin >> meal.carbohydrates;
		meal.created_on = tools::getDatetime();
		dal::writeDataToMealsFile(meal);
	}

	void addWorkoutForUser(User user)
	{
		Workout workout;
		workout.id = tools::generateGUID();
		workout.created_by = user.id;
		std::cout << "Enter the name of the workout: ";
		std::getline(std::cin, workout.name);
		std::cout << "Enter the calories burned during the workout: ";
		std::cin >> workout.calories_burned;
		workout.created_on = tools::getDatetime();
		dal::writeDataToWorkoutsFile(workout);
	}

	double calculateBMR(User user)
	{
		double bmr = 0;
		if (user.gender == 'M')
		{
			bmr = BMR_CONSTANT_MEN + (BMR_WEIGHT_MULTIPLIER_MEN * user.weight) + (BMR_HEIGHT_MULTIPLIER_MEN * user.height) - (BMR_AGE_MULTIPLIER_MEN * user.age);
		}
		else if (user.gender == 'F')
		{
			bmr = BMR_CONSTANT_WOMEN + (BMR_WEIGHT_MULTIPLIER_WOMEN * user.weight) + (BMR_HEIGHT_MULTIPLIER_WOMEN * user.height) - (BMR_AGE_MULTIPLIER_WOMEN * user.age);
		}

		if (user.activity_level == '1')
		{
			bmr *= ACTIVITY_VERY_ACTIVE;
		}
		else if (user.activity_level == '2')
		{
			bmr *= ACTIVITY_ACTIVE;
		}
		else if (user.activity_level == '3')
		{
			bmr *= ACTIVITY_MODERATE;
		}
		else if (user.activity_level == '4')
		{
			bmr *= ACTIVITY_LIGHT;
		}
		else if (user.activity_level == '5')
		{
			bmr *= ACTIVITY_SEDENTARY;
		}

		return bmr;
	}

	double calculateGoalCalories(User user)
	{
		Goal goal = dal::getGoalById(user.goal_id);
		double bmr = calculateBMR(user);
		double goalCalories = 0;
		if (goal.type == '1')
		{
			goalCalories = bmr - goal.calorie_adjustment;
		}
		else if (goal.type == '2')
		{
			goalCalories = bmr;
		}
		else if (goal.type == '3')
		{
			goalCalories = bmr + goal.calorie_adjustment;
		}

		return goalCalories;
	}
}
