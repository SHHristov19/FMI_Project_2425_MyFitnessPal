#include "include.h"

namespace bll
{
	void signUp()
	{
		User user;
		Goal goal;
		
		pl::printSignUpTitle(); 

        enterUserData(user, goal);

		mainPanel();
	}

	void enterGoalData(Goal& goal, bool isUpdate)
	{
		Goal newGoal;
		tools::printGoalTypes();
		tools::enterValidType(GOAL_TYPES, 3, "Invalid input. Please enter a valid goal type [1-3]: ", newGoal.type, "Enter your goal type [1-3]: ", isUpdate);


		if (newGoal.type != "2")
		{
			tools::enterValidType(GOAL_WEEKLY_CHANGES, 4, "Invalid input. Please enter a valid weekly change [0.25, 0.5, 0.75, 1]: ", newGoal.weeklyChange, "Enter your weekly change [0.25, 0.5, 0.75, 1] in kg: ", isUpdate);

			if (newGoal.weeklyChange == "0.25")
			{
				newGoal.calorieAdjustment = std::to_string(DAILY_DEFICIT_OR_SURPLUS_025KG);
			}
			else if (newGoal.weeklyChange == "0.5")
			{
				newGoal.calorieAdjustment = std::to_string(DAILY_DEFICIT_OR_SURPLUS_050KG);
			}
			else if (newGoal.weeklyChange == "0.75")
			{
				newGoal.calorieAdjustment = std::to_string(DAILY_DEFICIT_OR_SURPLUS_075KG);
			}
			else if (newGoal.weeklyChange == "1")
			{
				newGoal.calorieAdjustment = std::to_string(DAILY_DEFICIT_OR_SURPLUS_100KG);
			}
		}
		else
		{
			newGoal.weeklyChange = "0";
			newGoal.calorieAdjustment = "0";
		}

		goal.type = (newGoal.type.empty()) ? goal.type : newGoal.type;
		goal.weeklyChange = (newGoal.weeklyChange.empty()) ? goal.weeklyChange : newGoal.weeklyChange;
		goal.calorieAdjustment = (newGoal.calorieAdjustment.empty()) ? goal.calorieAdjustment : newGoal.calorieAdjustment;

		if (isUpdate)
		{
			dal::updateOrDeleteGoal(goal, true);
		}
		else
		{
			goal.id = tools::generateGUID();
			dal::writeDataToGoalsFile(goal);
		}
	}

	void enterUserData(User& user, Goal& goal, bool isUpdate)
	{
		User newUser;

		tools::enterValidString(newUser.firstName, "Enter your first name: ", isUpdate);
		tools::enterValidString(newUser.lastName, "Enter your last name: ", isUpdate);
		tools::enterValidAge(newUser.age, "Enter your age: ", isUpdate);
		tools::enterValidType(GENDER_TYPES, 2, "Invalid input. Please enter a valid gender [M/F]: ", newUser.gender, "Enter your gender [M/F]: ", isUpdate);
		tools::enterValidMeasurements(newUser.height, "Enter your height (in cm): ", isUpdate);
		tools::enterValidMeasurements(newUser.weight, "Enter your weight (in kg): ", isUpdate);
		tools::printActivityLevels();
		tools::enterValidType(ACTIVITY_LEVEL_TYPES, 5, "Invalid input. Please enter a valid activity level [1-5]: ", newUser.activityLevel, "Enter your activity level [1-5]: ", isUpdate);
		tools::enterValidType(USER_ACCOUNT_TYPE, 2, "Invalid input. Please enter a valid type [Standard/Premium]: ", newUser.type, "Enter your type [Standard/Premium]: ", isUpdate);
		tools::enterValidString(newUser.username, "Enter your username: ", isUpdate);
		tools::enterValidPassword(newUser.password, isUpdate);

		user.firstName = (newUser.firstName.empty()) ? user.firstName : newUser.firstName;
		user.lastName = (newUser.lastName.empty()) ? user.lastName : newUser.lastName;
        user.age = (newUser.age.empty()) ? user.age : newUser.age;
        user.gender = (newUser.gender.empty()) ? user.gender : newUser.gender;
        user.height = (newUser.height.empty()) ? user.height : newUser.height;
        user.weight = (newUser.weight.empty()) ? user.weight : newUser.weight;
        user.activityLevel = (newUser.activityLevel.empty()) ? user.activityLevel : newUser.activityLevel;
        user.type = (newUser.type.empty()) ? user.type : newUser.type;
        user.username = (newUser.username.empty()) ? user.username : newUser.username;
        user.password = (newUser.password.empty()) ? user.password : tools::passwordHash(newUser.password);

		enterGoalData(goal, isUpdate);

		if (isUpdate)
		{
			dal::updateOrDeleteUser(user, true);
			updateDailySummary(user, goal);
		}
		else
		{
			user.id = tools::generateGUID();
			user.createdOn = tools::getDatetime(DATETIME_FORMAT);
			user.goalId = goal.id;

			dal::writeDataToUsersFile(user);

			createDailySummary(user, goal);
		}
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
				std::cout << TABULATION << "Invalid username or password! Try Again!\n";
				tools::resetColor();
			}
			 
			tools::enterValidString(username, "Enter your username: ");
			tools::enterValidString(password, "Enter your password: ");

			password = tools::passwordHash(password);
			User findUser = dal::findUserByUsernameAndPassword(username, password);
			if (!findUser.id.empty())
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

	DailySummary printDailySymmary(User user, int days)
	{
		DailySummary dailySummary = dal::getDailySummaryByUserIdToday(user.id, days);
		Goal goal = dal::getGoalById(user.goalId);

		if (dailySummary.id.empty())
		{
			if (!goal.id.empty())
			{
				dailySummary = createDailySummary(user, goal, days);
			}
		}
		if (!dailySummary.id.empty())
		{
			tools::colorCyan();

			MacronutrientRatio macronutrientRatio;
			calculateMacronutrients(user, goal, std::stoi(dailySummary.recommendedCalories), macronutrientRatio);

			std::cout << "\t\t" << "Calories Consumed: " << dailySummary.caloriesConsumed << "\t\t\t" << "Protein: " + dailySummary.protein
				<< ((user.type == "Premium") ? ("\t\t\tProtein-Ration: " + macronutrientRatio.protein + "g.\n") : "\n");

			std::cout << "\t\t" << "Calories Burned: " << dailySummary.caloriesBurned << "\t\t\t" << "Fat: " + dailySummary.fat
				<< ((user.type == "Premium") ? ("\t\t\t\tFat-Ratio: " + macronutrientRatio.fat + "g.\n") : "\n");

			std::cout << "\t\t" << "Recommended Calories: " << dailySummary.recommendedCalories << "\t\t" << "Carbohydrates: " + dailySummary.carbohydrates
				<< ((user.type == "Premium") ? ("\t\tCarbohydrates-Ratio: " + macronutrientRatio.carbohydrates + "g.\n") : "\n");

			std::cout << "\t\t" << "Calorie Balance: " << dailySummary.calorieBalance << "\n\n";

			tools::resetColor();
		}

		return dailySummary;
	}

	void printHelp(User user)
	{
		pl::printHelpTitle();
		std::cout << std::endl;

		std::cout << TABULATION << "aw or wa: Add a workout to the list.\n";
		std::cout << TABULATION << "ma or am: Add a meal to the list.\n";
		std::cout << TABULATION << "um<number>: Update a meal by specifying the meal number.\n";
		std::cout << TABULATION << "uw<number>: Update a workout by specifying the workout number.\n";
		std::cout << TABULATION << "uu: Update user details.\n";
		std::cout << TABULATION << "dm<number>: Delete a specific meal by specifying the meal number.\n";
		std::cout << TABULATION << "dw<number>: Delete a specific workout by specifying the workout number.\n";
		std::cout << TABULATION << "delete: Delete all data for the current day.\n";
		std::cout << TABULATION << "<: Move to the previous day.\n";
		std::cout << TABULATION << ">: Move to the next day.\n";
		std::cout << TABULATION << "e: Exit the application.\n\n";

		while (true)
		{
			std::cout << TABULATION << "To go back press b: ";
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
			printDateAndWelcome(user.firstName, user.lastName, days);

			DailySummary dailySummary = printDailySymmary(user, days);
			Goal goal = dal::getGoalById(user.goalId);

			std::cout << std::endl;
			getGoalForUser(user.goalId, goal);
			std::vector<Meal> dailyMeals = getAllMealsForUser(user.id, days);
			std::vector<Workout> dailyWorkouts = getAllWorkoutsForUser(user.id, days);

			std::string input = tools::getInput();
			if (input == "h")
			{
				tools::clearConsole();
				printHelp(user);
			}
			else if (!input.empty() && input[0] == 'u')
			{
				if (input[1] == 'm')
				{ 
					size_t mealId = tools::getDigits(input) - 1;
                    if (mealId >= 0 && mealId <= dailyMeals.size() - 1)
					{ 
						tools::clearConsole();
						pl::printUpdateMealTitle();
						updateMealForUser(user, dailyMeals[mealId], dailySummary);
					}
				}
				else if (input[1] == 'w')
				{
					size_t workoutId = tools::getDigits(input) - 1;
					if (workoutId >= 0 && workoutId <= dailyWorkouts.size() - 1)
					{
						tools::clearConsole();
						pl::printUpdateWorkoutTitle();
						updateWorkoutForUser(user, dailyWorkouts[workoutId], dailySummary);
					}
				}
				else if (input[1] == 'u')
				{
					tools::clearConsole();
					pl::printUpdateUserTitle();
					updateUser(user, goal);
				}
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
			else if (input == "delete")
			{
				tools::clearConsole();
				deleteAllDataForTheDay(user, dailyMeals, dailyWorkouts, dailySummary);
			}
			else if (input[0] == 'd')
			{
				if (input[1] == 'm')
				{
					size_t mealId = tools::getDigits(input) - 1;
					if (mealId >= 0 && mealId <= dailyMeals.size() - 1)
					{
						tools::clearConsole();
						pl::printDeleteMealTitle();
						deleteMealForUser(user, dailyMeals[mealId], dailySummary);
					}
				}
				else if (input[1] == 'w')
				{
					size_t workoutId = tools::getDigits(input) - 1;
					if (workoutId >= 0 && workoutId <= dailyWorkouts.size() - 1)
					{
						tools::clearConsole();
						pl::printDeleteWorkoutTitle();
						deleteWorkoutForUser(user, dailyWorkouts[workoutId], dailySummary);
					}
				}
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

	void updateDailySummaryMeal(Meal meal, User user, int days)
	{
		DailySummary dailySummary = dal::getDailySummaryByUserIdToday(user.id, days);

		if (dailySummary.id.empty())
		{
			dailySummary = createDailySummary(user, dal::getGoalById(user.goalId));
		}
		if (!dailySummary.id.empty())
		{
			int consumedCalories = std::stoi(dailySummary.caloriesConsumed);
			consumedCalories += std::stoi(meal.calories);
			dailySummary.caloriesConsumed = std::to_string(consumedCalories);

			int consumedProtein = std::stoi(dailySummary.protein);
			consumedProtein += std::stoi(meal.protein);
			dailySummary.protein = std::to_string(consumedProtein);

			int consumedFat = std::stoi(dailySummary.fat);
			consumedFat += std::stoi(meal.fat);
			dailySummary.fat = std::to_string(consumedFat);

			int consumedCarbohydrates = std::stoi(dailySummary.carbohydrates);
			consumedCarbohydrates += std::stoi(meal.carbohydrates);
			dailySummary.carbohydrates = std::to_string(consumedCarbohydrates);

			int balance = std::stoi(dailySummary.caloriesConsumed) - std::stoi(dailySummary.caloriesBurned);
			dailySummary.calorieBalance = std::to_string(balance);

			dal::updateOrDeleteDailySummary(dailySummary, true);
		}
	}

	void addMealForUser(User user, int days)
	{
		Meal meal;
		meal.id = tools::generateGUID();
		meal.createdBy = user.id;

		tools::enterValidString(meal.name, "Enter the name of the meal: ");
		tools::enterValidCaloriesAndGrams(meal.calories, "Enter the calories of the meal: ");
		tools::enterValidCaloriesAndGrams(meal.protein, "Enter the protein content of the meal: ");
		tools::enterValidCaloriesAndGrams(meal.fat, "Enter the fat content of the meal: ");
		tools::enterValidCaloriesAndGrams(meal.carbohydrates, "Enter the carbohydrates content of the meal: ");
		 
		meal.createdOn = tools::getDatetime(DATETIME_FORMAT);
		meal.date = tools::getDatetime(DATE_FORMAT, days);
		dal::writeDataToMealsFile(meal);

		updateDailySummaryMeal(meal, user, days);
	}

	void updateDailySummaryWorkout(Workout workout, User user, int days)
	{
		DailySummary dailySummary = dal::getDailySummaryByUserIdToday(user.id, days);

		if (dailySummary.id.empty())
		{
			dailySummary = createDailySummary(user, dal::getGoalById(user.goalId));
		}
		if (!dailySummary.id.empty())
		{
			int burnedCalories = std::stoi(dailySummary.caloriesBurned);
			burnedCalories += std::stoi(workout.caloriesBurned);
			dailySummary.caloriesBurned = std::to_string(burnedCalories);

			int balance = std::stoi(dailySummary.caloriesConsumed) - std::stoi(dailySummary.caloriesBurned);
			dailySummary.calorieBalance = std::to_string(balance);

			dal::updateOrDeleteDailySummary(dailySummary, true);
		}
	}

	void addWorkoutForUser(User user, int days)
	{
		Workout workout;
		workout.id = tools::generateGUID();
		workout.createdBy = user.id;

		tools::enterValidString(workout.name, "Enter the name of the workout: ");
		tools::enterValidCaloriesAndGrams(workout.caloriesBurned, "Enter the calories burned during the workout: ");

		workout.createdOn = tools::getDatetime(DATETIME_FORMAT);
		workout.date = tools::getDatetime(DATE_FORMAT, days);
		dal::writeDataToWorkoutsFile(workout);

		updateDailySummaryWorkout(workout, user, days);
	}

	void getGoalForUser(std::string goalId, Goal& goal)
	{
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

		std::cout << goal.weeklyChange;
		spaces = CELL_WIDTH - goal.weeklyChange.length();
		for (int i = 0; i < spaces; ++i) std::cout << ' ';

		std::cout << goal.calorieAdjustment;
		spaces = CELL_WIDTH - goal.calorieAdjustment.length();
		for (int i = 0; i < spaces; ++i) std::cout << ' ';

		std::cout << "\n" << TABULATION << std::string(CELL_WIDTH * 3, '-') << "\n";
		tools::resetColor();
	}

	std::vector<Meal> getAllMealsForUser(std::string userId, int days)
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

			std::cout << meal.createdOn;
			spaces = CELL_WIDTH - meal.createdOn.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << '\n';
		}

		std::cout << "\t" << std::string(CELL_WIDTH * 7 - NUMBER_DIGITS, '-') << "\n";

		return meals;
	}

	void getWorkoutForUser(std::string userId, std::string workoutId)
	{
		Workout workout = dal::getWorkoutById(workoutId);
		if (workout.createdBy == userId)
		{
			std::cout << TABULATION << "Name: " << workout.name << std::endl;
			std::cout << TABULATION << "Calories Burned: " << workout.caloriesBurned << std::endl;
		}
	}

	std::vector<Workout> getAllWorkoutsForUser(std::string userId, int days)
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

			std::cout << workout.caloriesBurned << " kcal";
			spaces = CELL_WIDTH - workout.caloriesBurned.length() - 5;
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << workout.createdOn;
			spaces = CELL_WIDTH - workout.createdOn.length();
			for (int i = 0; i < spaces; ++i) std::cout << ' ';

			std::cout << '\n';
        }

        std::cout << TABULATION << std::string(CELL_WIDTH * 4 - NUMBER_DIGITS, '-') << "\n";

		return workouts;
	}

	void printMealData(Meal meal)
	{
		std::cout << TABULATION << "Name: " << meal.name << std::endl;
		std::cout << TABULATION << "Calories: " << meal.calories << std::endl;
		std::cout << TABULATION << "Protein: " << meal.protein << std::endl;
		std::cout << TABULATION << "Fat: " << meal.fat << std::endl;
		std::cout << TABULATION << "Carbohydrates: " << meal.carbohydrates << std::endl;
	}

	void printWorkoutData(Workout workout)
	{
		std::cout << TABULATION << "Name: " << workout.name << std::endl;
		std::cout << TABULATION << "Calories Burned: " << workout.caloriesBurned << std::endl;
	}

	void printGoalData(Goal goal)
	{
		std::cout << TABULATION << "Type: " << goal.type << std::endl;
		std::cout << TABULATION << "Weekly Change: " << goal.weeklyChange << std::endl;
		std::cout << TABULATION << "Calorie Adjustment: " << goal.calorieAdjustment << std::endl;
	}

	void printUserData(User user)
	{
		std::cout << TABULATION << "First Name: " << user.firstName << std::endl;
		std::cout << TABULATION << "Last Name: " << user.lastName << std::endl;
		std::cout << TABULATION << "Age: " << user.age << std::endl;
		std::cout << TABULATION << "Gender: " << user.gender << std::endl;
		std::cout << TABULATION << "Height: " << user.height << std::endl;
		std::cout << TABULATION << "Weight: " << user.weight << std::endl;
		std::cout << TABULATION << "Activity Level: " << user.activityLevel << tools::getActivityLevel(user.activityLevel) << std::endl;
		std::cout << TABULATION << "Type: " << user.type << std::endl;
		std::cout << TABULATION << "Username: " << user.username << std::endl << std::endl;
		std::cout << TABULATION << "GOAL" << std::endl;

		printGoalData(dal::getGoalById(user.goalId));
	}

	void updateMealForUser(User user, Meal meal, DailySummary dailySummary)
	{
		printMealData(meal);
		Meal newMeal;

		tools::colorRed();
		std::cout << std::endl;
		std::cout << TABULATION << "If ypu want to update data type new data, otherwise leve the input empty!\n";
		tools::resetColor();

		tools::enterValidString(newMeal.name, "Enter the name of the meal: ", true);
		tools::enterValidCaloriesAndGrams(newMeal.calories, "Enter the calories of the meal: ", true);
		tools::enterValidCaloriesAndGrams(newMeal.protein, "Enter the protein content of the meal: ", true);
		tools::enterValidCaloriesAndGrams(newMeal.fat, "Enter the fat content of the meal: ", true);
		tools::enterValidCaloriesAndGrams(newMeal.carbohydrates, "Enter the carbohydrates content of the meal: ", true);

		dailySummary.caloriesConsumed = std::to_string(std::stoi(dailySummary.caloriesConsumed) - std::stoi(meal.calories));
		dailySummary.protein = std::to_string(std::stoi(dailySummary.protein) - std::stoi(meal.protein));
		dailySummary.fat = std::to_string(std::stoi(dailySummary.fat) - std::stoi(meal.fat));
		dailySummary.carbohydrates = std::to_string(std::stoi(dailySummary.carbohydrates) - std::stoi(meal.carbohydrates));

        meal.name = (newMeal.name.empty()) ? meal.name : newMeal.name;
        meal.calories = (newMeal.calories.empty()) ? meal.calories : newMeal.calories;
        meal.protein = (newMeal.protein.empty()) ? meal.protein : newMeal.protein;
        meal.fat = (newMeal.fat.empty()) ? meal.fat : newMeal.fat;
        meal.carbohydrates = (newMeal.carbohydrates.empty()) ? meal.carbohydrates : newMeal.carbohydrates;

		dailySummary.caloriesConsumed = std::to_string(std::stoi(dailySummary.caloriesConsumed) + std::stoi(meal.calories));
		dailySummary.protein = std::to_string(std::stoi(dailySummary.protein) + std::stoi(meal.protein));
		dailySummary.fat = std::to_string(std::stoi(dailySummary.fat) + std::stoi(meal.fat));
		dailySummary.carbohydrates = std::to_string(std::stoi(dailySummary.carbohydrates) + std::stoi(meal.carbohydrates));
		dailySummary.calorieBalance = std::to_string(std::stoi(dailySummary.caloriesConsumed) - std::stoi(dailySummary.caloriesBurned));

		dal::updateOrDeleteMeal(meal, true);
		dal::updateOrDeleteDailySummary(dailySummary, true);
	}

	void updateWorkoutForUser(User user, Workout workout, DailySummary dailySummary)
	{
		printWorkoutData(workout);
		Workout newWorkout;

		tools::colorRed();
		std::cout << std::endl;
		std::cout << TABULATION << "If ypu want to update data type new data, otherwise leve the input empty!\n";
		tools::resetColor();

		dailySummary.caloriesBurned = std::to_string(std::stoi(dailySummary.caloriesBurned) - std::stoi(workout.caloriesBurned));

		tools::enterValidString(newWorkout.name, "Enter the name of the workout: ", true);
		tools::enterValidCaloriesAndGrams(newWorkout.caloriesBurned, "Enter the calories burned during the workout: ", true);

		workout.name = (newWorkout.name.empty()) ? workout.name : newWorkout.name;
		workout.caloriesBurned = (newWorkout.caloriesBurned.empty()) ? workout.caloriesBurned : newWorkout.caloriesBurned;

		dailySummary.caloriesBurned = std::to_string(std::stoi(dailySummary.caloriesBurned) + std::stoi(workout.caloriesBurned));
		dailySummary.calorieBalance = std::to_string(std::stoi(dailySummary.caloriesConsumed) - std::stoi(dailySummary.caloriesBurned));

		dal::updateOrDeleteWorkout(workout, true);
		dal::updateOrDeleteDailySummary(dailySummary, true);
	}

	void updateUser(User& user, Goal& goal)
	{
		printUserData(user);

		tools::colorRed();
		std::cout << std::endl;
		std::cout << TABULATION << "If ypu want to update data type new data, otherwise leve the input empty!\n";
		tools::resetColor();

		enterUserData(user, goal, true);
	}

	void deleteMealForUser(User user, Meal meal, DailySummary dailySummary)
	{
		printMealData(meal);

		tools::colorRed();
		std::cout << std::endl;
		std::cout << TABULATION << "Are you sure you want to delete this meal? (Y/N): ";
		tools::resetColor();

		while (true)
		{
			std::string input = tools::getInput();
			tools::clearLine();
			if (input == "y" || input == "yes")
			{
				break;
			}
			else if (input == "n" || input == "no")
			{
				return;
			}
		}

		dailySummary.caloriesConsumed = std::to_string(std::stoi(dailySummary.caloriesConsumed) - std::stoi(meal.calories));
		dailySummary.protein = std::to_string(std::stoi(dailySummary.protein) - std::stoi(meal.protein));
		dailySummary.fat = std::to_string(std::stoi(dailySummary.fat) - std::stoi(meal.fat));
		dailySummary.carbohydrates = std::to_string(std::stoi(dailySummary.carbohydrates) - std::stoi(meal.carbohydrates));
		dailySummary.calorieBalance = std::to_string(std::stoi(dailySummary.caloriesConsumed) - std::stoi(dailySummary.caloriesBurned));

		dal::updateOrDeleteMeal(meal, false);
		dal::updateOrDeleteDailySummary(dailySummary, true);
	}

	void deleteWorkoutForUser(User user, Workout workout, DailySummary dailySummary)
	{
		printWorkoutData(workout);

		tools::colorRed();
		std::cout << std::endl;
		std::cout << TABULATION << "Are you sure you want to delete this workout? (Y/N): ";
		tools::resetColor();

		while (true)
		{
			std::string input = tools::getInput();
			tools::clearLine();
			if (input == "y" || input == "yes")
			{
				break;
			}
			else if (input == "n" || input == "no")
			{
				return;
			}
		}

		dailySummary.caloriesBurned = std::to_string(std::stoi(dailySummary.caloriesBurned) - std::stoi(workout.caloriesBurned));
		dailySummary.calorieBalance = std::to_string(std::stoi(dailySummary.caloriesConsumed) - std::stoi(dailySummary.caloriesBurned));

		dal::updateOrDeleteWorkout(workout, false);
		dal::updateOrDeleteDailySummary(dailySummary, true);
	}	

	void deleteAllDataForTheDay(User user, std::vector<Meal> meals, std::vector<Workout> workouts, DailySummary dailySummary)
	{
		for (Meal meal : meals)
		{
			dailySummary.caloriesConsumed = std::to_string(std::stoi(dailySummary.caloriesConsumed) - std::stoi(meal.calories));
			dailySummary.protein = std::to_string(std::stoi(dailySummary.protein) - std::stoi(meal.protein));
			dailySummary.fat = std::to_string(std::stoi(dailySummary.fat) - std::stoi(meal.fat));
			dailySummary.carbohydrates = std::to_string(std::stoi(dailySummary.carbohydrates) - std::stoi(meal.carbohydrates));

			dal::updateOrDeleteMeal(meal, false);
		}

		for (Workout workout : workouts)
		{
			dailySummary.caloriesBurned = std::to_string(std::stoi(dailySummary.caloriesBurned) - std::stoi(workout.caloriesBurned));

			dal::updateOrDeleteWorkout(workout, false);
		}

		dailySummary.calorieBalance = std::to_string(std::stoi(dailySummary.caloriesConsumed) - std::stoi(dailySummary.caloriesBurned));

		dal::updateOrDeleteDailySummary(dailySummary, true);
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

		if (user.activityLevel == "1")
		{
			bmr *= ACTIVITY_VERY_ACTIVE;
		}
		else if (user.activityLevel == "2")
		{
			bmr *= ACTIVITY_ACTIVE;
		}
		else if (user.activityLevel == "3")
		{
			bmr *= ACTIVITY_MODERATE;
		}
		else if (user.activityLevel == "4")
		{
			bmr *= ACTIVITY_LIGHT;
		}
		else if (user.activityLevel == "5")
		{
			bmr *= ACTIVITY_SEDENTARY;
		}

		return bmr;
	}

	int calculateGoalCalories(User user, std::string goalType, unsigned calorieAdjustment)
	{
		Goal goal = dal::getGoalById(user.goalId);
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

	void calculateMacronutrients(User user, Goal goal, int calories, MacronutrientRatio& ratio)
	{
		if (goal.type == "1")
		{
			ratio.protein = std::to_string((int)(MACRO_RATIO_LOSS_PROTEIN * calories / PROTEIN_CALORIES_PER_GRAM));
			ratio.fat = std::to_string((int)(MACRO_RATIO_LOSS_FAT * calories / FAT_CALORIES_PER_GRAM));
			ratio.carbohydrates = std::to_string((int)(MACRO_RATIO_LOSS_CARBOHYDRATES * calories / CARBOHYDRATE_CALORIES_PER_GRAM));
		}
		else if (goal.type == "2")
		{
			ratio.protein = std::to_string((int)(MACRO_RATIO_MAINTAIN_PROTEIN * calories / PROTEIN_CALORIES_PER_GRAM));
			ratio.fat = std::to_string((int)(MACRO_RATIO_MAINTAIN_FAT * calories / FAT_CALORIES_PER_GRAM));
			ratio.carbohydrates = std::to_string((int)(MACRO_RATIO_MAINTAIN_CARBOHYDRATES * calories / CARBOHYDRATE_CALORIES_PER_GRAM));
		}
		else if (goal.type == "3")
		{
			ratio.protein = std::to_string((int)(MACRO_RATIO_GAIN_PROTEIN * calories / PROTEIN_CALORIES_PER_GRAM));
			ratio.fat = std::to_string((int)(MACRO_RATIO_GAIN_FAT * calories / FAT_CALORIES_PER_GRAM));
			ratio.carbohydrates = std::to_string((int)(MACRO_RATIO_GAIN_CARBOHYDRATES * calories / CARBOHYDRATE_CALORIES_PER_GRAM));
		}
	}

	DailySummary createDailySummary(User user, Goal goal, int days)
	{
		DailySummary dailySummary;

		dailySummary.id = tools::generateGUID();
		dailySummary.userId = user.id;
		dailySummary.caloriesConsumed = "0";
		dailySummary.caloriesBurned = "0";
		dailySummary.calorieBalance = "0";
		dailySummary.protein = "0";
		dailySummary.fat = "0";
		dailySummary.carbohydrates = "0";
		dailySummary.recommendedCalories = std::to_string(calculateGoalCalories(user, goal.type, std::stoi(goal.calorieAdjustment)));
		dailySummary.date = tools::getDatetime(DATE_FORMAT, days);
		dailySummary.createdOn = tools::getDatetime(DATETIME_FORMAT);
		dal::writeDataToDailySummariesFile(dailySummary);

		return dailySummary;
	} 

	void updateDailySummary(User user, Goal goal)
	{
		std::vector<DailySummary> dailySummaries = dal::getDailySummariesByUserId(user.id);
		std::string caloriesAdj = std::to_string(calculateGoalCalories(user, goal.type, std::stoi(goal.calorieAdjustment)));

		for (DailySummary dailySummary : dailySummaries)
		{ 
			dailySummary.recommendedCalories = caloriesAdj;
			dal::updateOrDeleteDailySummary(dailySummary, true);
		}
	}
}
