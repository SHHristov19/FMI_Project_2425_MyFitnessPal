#include "include.h"

namespace bll
{
	void signUp()
	{
		User user;
		ActivityLevel activityLevel;
		Goal goal;
		GoalType goalType; 
		user.id = tools::generateGUID();
		goal.id = tools::generateGUID(); 
		user.goal_id = goal.id;

		pl::printSignUpTitle();
		std::cin.ignore();
		std::cout << TABULATION << "Enter your first name: ";
		std::getline(std::cin, user.first_name);
		std::cout << TABULATION << "Enter your last name: ";
		std::getline(std::cin, user.last_name);

		std::cout << TABULATION << "Enter your age: ";
		std::getline(std::cin, user.age);
		while (true)
		{
			if (std::cin.fail() || std::stoi(user.age) < 0 || std::stoi(user.age) > 100)
			{
				std::cin.clear();
				tools::clearLine();
				tools::colorRed();
				std::cout << TABULATION << "Invalid input. Please enter a valid age." << std::endl;
				tools::resetColor();
				std::cin.ignore(); // Clear the input buffer
				std::cout << TABULATION << "Enter your age: ";
				std::getline(std::cin, user.age);
			}
			else
			{
				break;
			}
		}

		std::cout << TABULATION << "Enter your gender [M/F]: ";
		user.gender = enterValidType(GENTER_TYPES, 2, "Invalid input. Please enter a valid gender [M/F]: ");

		std::cout << TABULATION << "Enter your height (in cm): ";
		std::cin >> user.height;
		std::cout << TABULATION << "Enter your weight (in kg): ";
		std::cin >> user.weight;
		std::cout << std::endl;

		std::cout << TABULATION << "1. VeryActive" << std::endl;
		std::cout << TABULATION << "2. ActiveJob" << std::endl;
		std::cout << TABULATION << "3. ModerateActivity" << std::endl;
		std::cout << TABULATION << "4. LightActivity" << std::endl;
		std::cout << TABULATION << "5. SedentaryJob" << std::endl;
		std::cout << TABULATION << "Enter your activity level [1-5]: ";
		user.activity_level = enterValidType(ACTIVITY_LEVEL_TYPES, 5, "Invalid input. Please enter a valid activity level [1-5]: ");

		std::cout << TABULATION << "1. LoseWeight" << std::endl;
		std::cout << TABULATION << "2. MaintainWeight" << std::endl;
		std::cout << TABULATION << "3. GainWeight" << std::endl;
		std::cout << TABULATION << "Enter your goal type [1-3]: ";
		goal.type = enterValidType(GOAL_TYPES, 3, "Invalid input. Please enter a valid goal type [1-3]: ");
		
		if (goal.type != "2")
		{
			std::cout << TABULATION << "Enter your weekly change [0.25, 0.5, 0.75, 1] in kg: ";
			goal.weekly_change = enterValidType(GOAL_WEEKLY_CHANGES, 4, "Invalid input. Please enter a valid weekly change [0.25, 0.5, 0.75, 1]: ");
		
			if (goal.weekly_change == "0.25")
			{
				goal.calorie_adjustment = DAILY_DEFICIT_OR_SURPLUS_025KG;
			}
			else if (goal.weekly_change == "0.50")
			{
				goal.calorie_adjustment = DAILY_DEFICIT_OR_SURPLUS_050KG;
			}
			else if (goal.weekly_change == "0.75")
			{
				goal.calorie_adjustment = DAILY_DEFICIT_OR_SURPLUS_075KG;
			}
			else if (goal.weekly_change == "1.00")
			{
				goal.calorie_adjustment = DAILY_DEFICIT_OR_SURPLUS_100KG;
			}
		}
		else
		{
			goal.weekly_change = "0";
			goal.calorie_adjustment = "0";
		}

		std::cout << TABULATION << "Enter your type [Standard/Premium]: ";
		user.type = enterValidType(USER_ACCOUNT_TYPE, 2, "Invalid input. Please enter a valid type [Standard/Premium]: ");

        std::cin.ignore();
        std::cout << TABULATION << "Enter your username: ";
        std::getline(std::cin, user.username);

		user.password = enterValidPassword(user.password);

		user.password = tools::passwordHash(user.password);
		user.created_on = tools::getDatetime("%d.%m.%Y %T");

		createDailySummary(user, goal);

		dal::writeDataToGoalsFile(goal);
		dal::writeDataToUsersFile(user);
		

		mainPanel();
	}

	void signIn()
	{
		std::string username;
		std::string password;
		bool wrongInput = false;

		while (true)
		{
			pl::printLoginTitle();
			
			if (wrongInput)
			{
				tools::colorRed();
				std::cout << TABULATION << "Invalid username or password! Try Again!";
				tools::resetColor();
			}
			 
			std::cout << std::endl << TABULATION << "Enter your username: ";
			std::getline(std::cin, username);
			std::cout << TABULATION << "Enter your password: ";
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

	void mainPanel()
	{
		tools::clearConsole();
		tools::setConsoleSize();
		pl::printTitle();
		pl::printMenuOptions();

		while (true)
		{
			std::string input = tools::getInput();
			tools::clearLine();
			if (input == "1")
			{
				tools::clearConsole();
				bll::signIn();
			}
			else if (input == "2")
			{
				tools::clearConsole();
				bll::signUp();
			}
			else if (input == "3")
			{
				std::exit(0); // Exit the program
			}
		}
	}

	void printDateAndWelcome(std::string firstName, std::string lastName, int days)
	{
		tools::clearConsole();

		tools::colorGreen();
		std::cout << TABULATION + TABULATION.substr(3) << "You have successfully logged in!" << std::endl;
		std::cout << TABULATION + TABULATION.substr(3) << "Welcome, " << firstName << " " << lastName << "!" << std::endl;
		std::cout << TABULATION + TABULATION.substr(3) << "IF YOU NEED HELP PRESS H" << std::endl;
		tools::resetColor();

		pl::printAsciiDate(days);

		std::cout << "\n\n";
	}

	void printDailySymmary(User user, int days)
	{
		DailySummary dailySummary = dal::getDailySummaryByUserIdToday(user.id, days);

		if (dailySummary.id == "")
		{
			Goal goal = dal::getGoalById(user.goal_id);
			if (goal.id != "")
			{
				dailySummary = createDailySummary(user, goal);
			}
			else
			{
				// TO DO createGoal() GO TO DailySummary dailySummary = dal::getDailySummaryByUserUdToday(user.id);
			}
		}
		if (dailySummary.id != "")
		{
			tools::colorCyan();

			std::cout << TABULATION << "Calories Consumed: " << dailySummary.calories_consumed
				<< ((user.type == "Premium") ? (TABULATION + "Protein: " + dailySummary.protein + "\n") : "\n");

			std::cout << TABULATION << "Calories Burned: " << dailySummary.calories_burned
				<< ((user.type == "Premium") ? (TABULATION + "Fat: " + dailySummary.fat + "\n") : "\n");

			std::cout << TABULATION << "Recommended Calories: " << dailySummary.recommended_calories
				<< ((user.type == "Premium") ? (TABULATION.substr(1) + "Carbohydrates: " + dailySummary.carbohydrates + "\n") : "\n");

			std::cout << TABULATION << "Calorie Balance: " << dailySummary.calorie_balance << "\n\n";

			tools::resetColor();
		}
	}

	void printHelp(User user)
	{
		pl::printHelpTitle();

        std::cout << "\n" << TABULATION << "To manage your meals press 'M' or 'm'" << std::endl;
        std::cout << TABULATION << "To manage your workouts press 'W' or 'w'" << std::endl;
        std::cout << TABULATION << "To manage your goal press 'G' or 'g'" << std::endl;
        std::cout << TABULATION << "To see the report for the previous day press '<'" << std::endl;
        std::cout << TABULATION << "To see the report for the next day press '>'" << std::endl;
        std::cout << TABULATION << "To sign out press 'E' or 'e'" << std::endl;

		std::cout << std::endl;
		std::cout << TABULATION << "To go back press B/b\n";
		while (true)
		{
			std::string input = tools::getInput();
			tools::clearLine();
			if (input == "b")
			{
				break;
			}
		}

		tools::clearConsole();
		homePanel(user);
	}

	void homePanel(User user)
	{
		int days = 0;
		while (true)
		{
			printDateAndWelcome(user.first_name, user.last_name, days);

			printDailySymmary(user, days);

			std::cout << std::endl;
			getGoalForUser(user.goal_id);
			getAllMealsForUser(user.id, days);
			getAllWorkoutsForUser(user.id, days);

			std::string input = tools::getInput();
			if (input == "h")
			{
				tools::clearConsole();
				printHelp(user);
			}
			else if (input == "aw" || input == "wa")
			{
				tools::clearConsole();
				pl::printAddWorkoutTitle();
				addWorkoutForUser(user, days);
			}
			else if (input == "ma" || input == "am")
			{
				tools::clearConsole();
				pl::printAddMealTitle();
				addMealForUser(user, days);
			}
			else if (input == "<")
			{
				days--;
			}
			else if (input == ">")
			{
				days++;
			}
			else if (input == "e")
			{
				break;
			}
		}
		mainPanel();
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
			std::cout << TABULATION << "Enter your password: ";
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

	void updateDailySummaryOnAddingMeal(Meal meal, User user, int days)
	{
		DailySummary dailySummary = dal::getDailySummaryByUserIdToday(user.id, days);

		if (dailySummary.id == "")
		{
			dailySummary = createDailySummary(user, dal::getGoalById(user.goal_id));
		}
		if (dailySummary.id != "")
		{
			int consumedCalories = std::stoi(dailySummary.calories_consumed);
			consumedCalories += std::stoi(meal.calories);
			dailySummary.calories_consumed = std::to_string(consumedCalories);

			int consumedProtein = std::stoi(dailySummary.protein);
			consumedProtein += std::stoi(meal.protein);
			dailySummary.protein = std::to_string(consumedProtein);

			int consumedFat = std::stoi(dailySummary.fat);
			consumedFat += std::stoi(meal.fat);
			dailySummary.fat = std::to_string(consumedFat);

			int consumedCarbohydrates = std::stoi(dailySummary.carbohydrates);
			consumedCarbohydrates += std::stoi(meal.carbohydrates);
			dailySummary.carbohydrates = std::to_string(consumedCarbohydrates);

			int balance = std::stoi(dailySummary.calories_consumed) - std::stoi(dailySummary.calories_burned);
			dailySummary.calorie_balance = std::to_string(balance);

			dal::updateOrDeleteDailySummary(dailySummary, true);
		}
	}

	void addMealForUser(User user, int days)
	{
		Meal meal;
		meal.id = tools::generateGUID();
		meal.created_by = user.id;
		std::cout << TABULATION << "Enter the name of the meal: ";
		std::getline(std::cin, meal.name);
		std::cout << TABULATION << "Enter the calories of the meal: ";
		std::getline(std::cin, meal.calories);
		std::cout << TABULATION << "Enter the protein content of the meal: ";
		std::getline(std::cin, meal.protein);
		std::cout << TABULATION << "Enter the fat content of the meal: ";
		std::getline(std::cin, meal.fat);
		std::cout << TABULATION << "Enter the carbohydrates content of the meal: ";
		std::getline(std::cin, meal.carbohydrates);
		 
		meal.created_on = tools::getDatetime("%d.%m.%Y %T");
		meal.date = tools::getDatetime("%d.%m.%Y", days);
		dal::writeDataToMealsFile(meal);

		updateDailySummaryOnAddingMeal(meal, user, days);
	}

	void updateDailySummaryOnAddingWorkout(Workout workout, User user, int days)
	{
		DailySummary dailySummary = dal::getDailySummaryByUserIdToday(user.id, days);

		if (dailySummary.id == "")
		{
			dailySummary = createDailySummary(user, dal::getGoalById(user.goal_id));
		}
		if (dailySummary.id != "")
		{
			int burnedCalories = std::stoi(dailySummary.calories_burned);
			burnedCalories += std::stoi(workout.calories_burned);
			dailySummary.calories_burned = std::to_string(burnedCalories);

			int balance = std::stoi(dailySummary.calories_consumed) - std::stoi(dailySummary.calories_burned);
			dailySummary.calorie_balance = std::to_string(balance);

			dal::updateOrDeleteDailySummary(dailySummary, true);
		}
	}

	void addWorkoutForUser(User user, int days)
	{
		Workout workout;
		workout.id = tools::generateGUID();
		workout.created_by = user.id;
		std::cout << TABULATION << "Enter the name of the workout: ";
		std::getline(std::cin, workout.name);
		std::cout << TABULATION << "Enter the calories burned during the workout: ";
		std::getline(std::cin, workout.calories_burned);
		workout.created_on = tools::getDatetime("%d.%m.%Y %T");
		workout.date = tools::getDatetime("%d.%m.%Y", days);
		dal::writeDataToWorkoutsFile(workout);

		updateDailySummaryOnAddingWorkout(workout, user, days);
	}

	void getGoalForUser(std::string goalId)
	{
		Goal goal = dal::getGoalById(goalId);

		tools::colorYellow();
		std::cout << std::endl << TABULATION << "GOAL" << std::endl;

		std::cout << TABULATION << std::string(CELL_WIDTH * 3, '-') << "\n";

		std::cout << TABULATION
			<< "Type" << std::string(CELL_WIDTH - 4, ' ')
			<< "Weekly Change" << std::string(CELL_WIDTH - 13, ' ')
			<< "Calorie Adjustment" << std::string(CELL_WIDTH - 17, ' ') << "\n";

		std::cout << TABULATION << std::string(CELL_WIDTH * 3, '-') << "\n";

		std::cout << TABULATION << goal.type;
		int spaces = CELL_WIDTH - goal.type.length();
		for (int i = 0; i < spaces; ++i) std::cout << ' ';

		std::cout << goal.weekly_change;
		spaces = CELL_WIDTH - goal.weekly_change.length();
		for (int i = 0; i < spaces; ++i) std::cout << ' ';

		std::cout << goal.calorie_adjustment;
		spaces = CELL_WIDTH - goal.calorie_adjustment.length();
		for (int i = 0; i < spaces; ++i) std::cout << ' ';

		std::cout << "\n" << TABULATION << std::string(CELL_WIDTH * 3, '-') << "\n";
		tools::resetColor();
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

	void getAllMealsForUser(std::string userId, int days)
	{
		std::vector<Meal> meals = dal::getMealsByUserId(userId, true, days);
		size_t id = 1;

		std::cout << std::endl << "\tMEALS" << std::endl;
		std::cout << "\t" << std::string(CELL_WIDTH * 7 - NUMBER_DIGITS, '-') << "\n";

		std::cout << "\t"
			<< "Id" << std::string(CELL_WIDTH - 2 - NUMBER_DIGITS, ' ')
			<< "Name" << std::string(CELL_WIDTH - 4, ' ')
			<< "Calories" << std::string(CELL_WIDTH - 8, ' ')
			<< "Protein" << std::string(CELL_WIDTH - 7, ' ')
			<< "Fat" << std::string(CELL_WIDTH - 3, ' ')
			<< "Carbohydrates" << std::string(CELL_WIDTH - 13, ' ')
			<< "Created On" << std::string(CELL_WIDTH - 10, ' ') << "\n";

		std::cout << "\t" << std::string(CELL_WIDTH * 7 - NUMBER_DIGITS, '-') << "\n";

		for (Meal meal : meals)
		{
			std::cout << "\t" << id++;
			int spaces = CELL_WIDTH - std::to_string(id).length() - NUMBER_DIGITS;
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << meal.name;
			spaces = CELL_WIDTH - meal.name.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << meal.calories << " kcal";
			spaces = CELL_WIDTH - meal.calories.length() - 5;
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << meal.protein << "g.";
			spaces = CELL_WIDTH - meal.protein.length() - 2;
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << meal.fat << "g.";
			spaces = CELL_WIDTH - meal.fat.length() - 2;
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << meal.carbohydrates << "g.";
			spaces = CELL_WIDTH - meal.carbohydrates.length() - 2;
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << meal.created_on;
			spaces = CELL_WIDTH - meal.created_on.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << '\n';
		}

		std::cout << "\t" << std::string(CELL_WIDTH * 7 - NUMBER_DIGITS, '-') << "\n";
	}

	void getWorkoutForUser(std::string userId, std::string workoutId)
	{
		Workout workout = dal::getWorkoutById(workoutId);
		if (workout.created_by == userId)
		{
			std::cout << TABULATION << "Name: " << workout.name << std::endl;
			std::cout << TABULATION << "Calories Burned: " << workout.calories_burned << std::endl;
		}
	}

	void getAllWorkoutsForUser(std::string userId, int days)
	{
		std::vector<Workout> workouts = dal::getWorkoutsByUserId(userId, true, days);
		size_t id = 1;

        std::cout << std::endl << TABULATION << "WORKOUTS" << std::endl;

        std::cout << TABULATION << std::string(CELL_WIDTH * 4 - NUMBER_DIGITS, '-') << "\n";

        std::cout << TABULATION
        << "Id" << std::string(CELL_WIDTH - 2 - NUMBER_DIGITS, ' ')
        << "Name" << std::string(CELL_WIDTH - 4, ' ')
        << "Calories Burned" << std::string(CELL_WIDTH - 15, ' ')
        << "Created On" << std::string(CELL_WIDTH - 10, ' ') << "\n";

        std::cout << TABULATION << std::string(CELL_WIDTH * 4 - NUMBER_DIGITS, '-') << "\n";

        for (Workout workout : workouts)
        {
			std::cout << TABULATION << id++;
			int spaces = CELL_WIDTH - std::to_string(id).length() - NUMBER_DIGITS;
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << workout.name;
			spaces = CELL_WIDTH - workout.name.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << workout.calories_burned << " kcal";
			spaces = CELL_WIDTH - workout.calories_burned.length() - 5;
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << workout.created_on;
			spaces = CELL_WIDTH - workout.created_on.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << '\n';
        }

        std::cout << TABULATION << std::string(CELL_WIDTH * 4 - NUMBER_DIGITS, '-') << "\n";
	}

	double calculateBMR(User user)
	{
		double bmr = 0;
		if (user.gender == "M")
		{
			bmr = BMR_CONSTANT_MEN + (BMR_WEIGHT_MULTIPLIER_MEN * std::stoi(user.weight)) + (BMR_HEIGHT_MULTIPLIER_MEN * std::stoi(user.height)) - (BMR_AGE_MULTIPLIER_MEN * std::stoi(user.age));
		}
		else if (user.gender == "F")
		{
			bmr = BMR_CONSTANT_WOMEN + (BMR_WEIGHT_MULTIPLIER_WOMEN * std::stoi(user.weight)) + (BMR_HEIGHT_MULTIPLIER_WOMEN * std::stoi(user.height)) - (BMR_AGE_MULTIPLIER_WOMEN * std::stoi(user.age));
		}

		if (user.activity_level == "1")
		{
			bmr *= ACTIVITY_VERY_ACTIVE;
		}
		else if (user.activity_level == "2")
		{
			bmr *= ACTIVITY_ACTIVE;
		}
		else if (user.activity_level == "3")
		{
			bmr *= ACTIVITY_MODERATE;
		}
		else if (user.activity_level == "4")
		{
			bmr *= ACTIVITY_LIGHT;
		}
		else if (user.activity_level == "5")
		{
			bmr *= ACTIVITY_SEDENTARY;
		}

		return bmr;
	}

	int calculateGoalCalories(User user, std::string goalType, unsigned calorieAdjustment)
	{
		Goal goal = dal::getGoalById(user.goal_id);
		double bmr = calculateBMR(user);
		int goalCalories = 0;

		if (goalType == "1")
		{
			goalCalories = bmr - calorieAdjustment;
		}
		else if (goalType == "2")
		{
			goalCalories = bmr;
		}
		else if (goalType == "2")
		{
			goalCalories = bmr + calorieAdjustment;
		}

		return goalCalories;
	}

	DailySummary createDailySummary(User user, Goal goal)
	{
		DailySummary dailySummary;

		dailySummary.id = tools::generateGUID();
		dailySummary.user_id = user.id;
		dailySummary.calories_consumed = "0";
		dailySummary.calories_burned = "0";
		dailySummary.calorie_balance = "0";
		dailySummary.protein = "0";
		dailySummary.fat = "0";
		dailySummary.carbohydrates = "0";
		dailySummary.recommended_calories = std::to_string(calculateGoalCalories(user, goal.type, std::stoi(goal.calorie_adjustment)));
		dailySummary.date = tools::getDatetime("%d.%m.%Y");
		dailySummary.created_on = tools::getDatetime("%d.%m.%Y %T");
		dal::writeDataToDailySummariesFile(dailySummary);

		return dailySummary;
	} 
}
