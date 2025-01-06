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

		user.password = enterValidPassword(user.password);

		user.password = tools::passwordHash(user.password);
		user.created_on = tools::getDatetime("%d.%m.%Y %T");
		dal::writeDataToGoalsFile(goal);
		dal::writeDataToUsersFile(user);
	}

	void signIn()
	{
		std::string username;
		std::string password;
		bool wrongInput = false;
		std::cin.ignore();
		while (true)
		{
			pl::printLoginTitle();
			
			if (wrongInput)
			{
				tools::colorRed();
				std::cout << "\t\t\t\t\tInvalid username or password! Try Again!";
				tools::resetColor();
			}
			
			std::cout << "\n\t\t\t\t\tEnter your username: ";
			std::getline(std::cin, username);
			std::cout << "\t\t\t\t\tEnter your password: ";
			std::getline(std::cin, password);
			password = tools::passwordHash(password);
			User findUser = dal::findUserByUsernameAndPassword(username, password);
			if (findUser.id != "")
			{
				homePanel(findUser);
			}
			else
			{
				wrongInput = true;
				tools::clearConsole();
			}
		}
	}

	void homePanel(User user)
	{
		std::cout << "You have successfully logged in!" << std::endl;
		std::cout << "Welcome, " << user.first_name << " " << user.last_name << "!" << std::endl;
		std::cout << "To add a meal press 1" << std::endl;
		std::cout << "To see your meals press 2" << std::endl;
		std::cout << "To add a workout press 3" << std::endl;
		std::cout << "To see your workouts press 4" << std::endl;
		std::cout << "To exit press E" << std::endl;

		char input;
		while (true)
		{
			input = std::cin.get(); // Read a single character

			if (input == '1')
			{
				addMealForUser(user);
			}
			else if (input == '2')
			{
				getAllMealsForUser(user.id);
			}
			else if (input == '3')
			{
				addWorkoutForUser(user);
			}
			else if (input == '4')
			{
				getAllWorkoutsForUser(user.id);
			}

			if (input == 'E' || input == 'e')
			{
				break;
			}
		}
	}

	std::string validatePassword(std::string password)
	{
		if (password.length() < 8)
		{
			return "Password must be at least 8 characters long!";
		}

		bool hasDigit = false;
		bool hasLowercase = false;
		bool hasUppercase = false;
		bool hasSpecialCharacter = false;

		for (size_t i = 0; i < password.length(); i++)
		{
			if (isdigit(password[i]))
			{
				hasDigit = true;
			}
			else if (islower(password[i]))
			{
				hasLowercase = true;
			}
			else if (isupper(password[i]))
			{
				hasUppercase = true;
			}
			else if (ispunct(password[i]))
			{
				hasSpecialCharacter = true;
			}
		}

		if (!hasDigit)
		{
			return "Password must contain at least one digit!";
		}

		if (!hasLowercase)
		{
			return "Password must contain at least one lowercase letter!";
		}

		if (!hasUppercase)
		{
			return "Password must contain at least one uppercase letter!";
		}

		if (!hasSpecialCharacter)
		{
			return "Password must contain at least one special character!";
		}

		return "";
	}

	std::string enterValidPassword(std::string password)
	{
		while (true)
		{
			std::cout << "Enter your password: ";
			std::getline(std::cin, password);

			std::string errorMsg = validatePassword(password);
			if (errorMsg == "")
			{
				return password;
			}
			std::cout << errorMsg << std::endl;
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
		meal.created_on = tools::getDatetime("%d.%m.%Y %T");
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
		workout.created_on = tools::getDatetime("%d.%m.%Y %T");
		dal::writeDataToWorkoutsFile(workout);
	}

	void getMealForUser(std::string userId, std::string mealId)
	{
		Meal meal = dal::getMealById(mealId);
		if (meal.created_by == userId)
		{
			std::cout << "Name: " << meal.name << std::endl;
			std::cout << "Calories: " << meal.calories << std::endl;
			std::cout << "Protein: " << meal.protein << std::endl;
			std::cout << "Fat: " << meal.fat << std::endl;
			std::cout << "Carbohydrates: " << meal.carbohydrates << std::endl;
		}
	}

	void getAllMealsForUser(std::string userId, int cellWidth)
	{
		std::vector<Meal> meals = dal::getMealsByUserId(userId);

		std::cout << std::string(cellWidth * 6, '-') << "\n";
		std::cout << "Name" << std::string(cellWidth - 4, ' ')
			<< "Calories" << std::string(cellWidth - 8, ' ')
			<< "Protein" << std::string(cellWidth - 7, ' ')
			<< "Fat" << std::string(cellWidth - 3, ' ')
			<< "Carbohydrates" << std::string(cellWidth - 13, ' ')
			<< "Created On" << std::string(cellWidth - 10, ' ') << "\n";
		std::cout << std::string(cellWidth * 6, '-') << "\n";

		for (Meal meal : meals)
		{
			std::cout << meal.name;
			int spaces = cellWidth - meal.name.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << meal.calories;
			spaces = cellWidth - meal.calories.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << meal.protein;
			spaces = cellWidth - meal.protein.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << meal.fat;
			spaces = cellWidth - meal.fat.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << meal.carbohydrates;
			spaces = cellWidth - meal.carbohydrates.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << meal.created_on;
			spaces = cellWidth - meal.created_on.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << '\n';
		}

		std::cout << std::string(cellWidth * 6, '-') << "\n";
	}

	void getWorkoutForUser(std::string userId, std::string workoutId)
	{
		Workout workout = dal::getWorkoutById(workoutId);
		if (workout.created_by == userId)
		{
			std::cout << "Name: " << workout.name << std::endl;
			std::cout << "Calories Burned: " << workout.calories_burned << std::endl;
		}
	}

	void getAllWorkoutsForUser(std::string userId, int cellWidth)
	{
		std::vector<Workout> workouts = dal::getWorkoutsByUserId(userId);

		std::cout << std::string(cellWidth * 3, '-') << "\n";
		std::cout << "Name" << std::string(cellWidth - 4, ' ')
			<< "Calories Burned" << std::string(cellWidth - 15, ' ')
			<< "Created On" << std::string(cellWidth - 10, ' ') << "\n";
		std::cout << std::string(cellWidth * 3, '-') << "\n";

		for (Workout workout : workouts)
		{
			std::cout << workout.name;
			int spaces = cellWidth - workout.name.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << workout.calories_burned;
			spaces = cellWidth - workout.calories_burned.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << workout.created_on;
			spaces = cellWidth - workout.created_on.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << '\n';
		}

		std::cout << std::string(cellWidth * 3, '-') << "\n";
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
