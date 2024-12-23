#include "include.h"

namespace mfp::dal
{
#pragma region Users

    std::vector<std::vector<User>> readDataFromUsersFile(std::string fileName)
    {
        std::vector<std::vector<User>> allData;
        std::ifstream file(fileName);
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
                        if (line[i] == ',' && counter < 8)
                        {
                            counter++;
                            line.erase(i, 0);
                        }
                        else if (line[i] == '"')
                        {
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
                    std::vector<User> temp;
					temp.push_back(data);
					allData.push_back(temp);
                }
                counter++;
            }
            file.close();
        }
        return allData;
    }

	void writeDataToUsersFile(std::string fileName, User data)
	{
        std::ofstream out(fileName, std::ios_base::app);
		if (out.is_open())
		{
			out << data.id << ","
				<< data.first_name << ","
				<< data.last_name << ","
				<< data.age << ","
				<< data.gender << ","
				<< data.height << ","
				<< data.weight << ","
				<< data.activity_level << ","
				<< data.goal_id << ","
				<< data.username << ","
				<< data.password << ","
				<< data.type << ","
				<< data.created_on << "\n";

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + fileName);
		}
	}

#pragma endregion

#pragma region Goals

	std::vector<std::vector<Goal>> readDataFromGoalsFile(std::string fileName)
	{
		std::vector<std::vector<Goal>> allData;
		std::ifstream file(fileName);
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
						if (line[i] == ',' && counter < 2)
						{
							counter++;
							line.erase(i, 0);
						}
						else if (line[i] == '"')
						{
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
							data.weekly_change += line[i];
						}
						else if (counter == 3)
						{
							data.calorie_adjustment += line[i];
						}
					}
					std::vector<Goal> temp;
					temp.push_back(data);
					allData.push_back(temp);
				}
				counter++;
			}
			file.close();
		}
		return allData;
	}

	void writeDataToGoalsFile(std::string fileName, std::vector<Goal> data)
	{
		std::ofstream out(fileName, std::ios_base::app);
		if (out.is_open())
		{
			for (Goal goal : data) 
			{
				out << goal.id << ","
					<< goal.name << ","
					<< goal.weekly_change << ","
					<< goal.calorie_adjustment << "\n";
			}

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + fileName);
		}
	}

#pragma endregion

#pragma region Meals

	std::vector<std::vector<Meal>> readDataFromMealsFile(std::string fileName)
	{
		std::vector<std::vector<Meal>> allData;
		std::ifstream file(fileName);
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
						if (line[i] == ',' && counter < 3)
						{
							counter++;
							line.erase(i, 0);
						}
						else if (line[i] == '"')
						{
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
							data.created_by += line[i];
						}
						else if (counter == 4)
						{
							data.created_on += line[i];
						}
					}
					std::vector<Meal> temp;
					temp.push_back(data);
					allData.push_back(temp);
				}
				counter++;
			}
			file.close();
		}
		return allData;
	}

	void writeDataToMealsFile(std::string fileName, std::vector<Meal> data)
	{
		std::ofstream out(fileName, std::ios_base::app);
		if (out.is_open())
		{
			for (Meal meal : data) 
			{
				out << meal.id << ","
					<< meal.name << ","
					<< meal.calories << ","
					<< meal.created_by << ","
					<< meal.created_on << "\n";
			}

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + fileName);
		}
	}

#pragma endregion

#pragma region Workouts

	std::vector<std::vector<Workout>> readDataFromWorkoutsFile(std::string fileName)
	{
		std::vector<std::vector<Workout>> allData;
		std::ifstream file(fileName);
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
						if (line[i] == ',' && counter < 3)
						{
							counter++;
							line.erase(i, 0);
						}
						else if (line[i] == '"')
						{
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
					std::vector<Workout> temp;
					temp.push_back(data);
					allData.push_back(temp);
				}
				counter++;
			}
			file.close();
		}
		return allData;
	}

	void writeDataToWorkoutsFile(std::string fileName, std::vector<Workout> data)
	{
		std::ofstream out(fileName, std::ios_base::app);
		if (out.is_open())
		{
			for (Workout workout : data) 
			{
				out << workout.id << ","
					<< workout.name << ","
					<< workout.calories_burned << ","
					<< workout.created_by << ","
					<< workout.created_on << "\n";
			}

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + fileName);
		}
	}

#pragma endregion

#pragma region DailySummaries

	std::vector<std::vector<DailySummary>> readDataFromDailySummariesFile(std::string fileName)
	{
		std::vector<std::vector<DailySummary>> allData;
		std::ifstream file(fileName);
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
						if (line[i] == ',' && counter < 5)
						{
							counter++;
							line.erase(i, 0);
						}
						else if (line[i] == '"')
						{
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
					}
					std::vector<DailySummary> temp;
					temp.push_back(data);
					allData.push_back(temp);
				}
				counter++;
			}
			file.close();
		}
		return allData;
	}

	void writeDataToDailySummariesFile(std::string fileName, std::vector<DailySummary> data)
	{
		std::ofstream out(fileName, std::ios_base::app);
		if (out.is_open())
		{
			for (DailySummary dailySummary : data) 
			{
				out << dailySummary.id << ","
					<< dailySummary.user_id << ","
					<< dailySummary.date << ","
					<< dailySummary.calories_consumed << ","
					<< dailySummary.calories_burned << ","
					<< dailySummary.recommended_calories << ","
					<< dailySummary.calorie_balance << "\n";
			}

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + fileName);
		}
	}

#pragma endregion

#pragma region MacronutrientRatios

	std::vector<std::vector<MacronutrientRatio>> readDataFromMacronutrientRatioFile(std::string fileName)
	{
		std::vector<std::vector<MacronutrientRatio>> allData;
		std::ifstream file(fileName);
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
						else if (line[i] == '"')
						{
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
					std::vector<MacronutrientRatio> temp;
					temp.push_back(data);
					allData.push_back(temp);
				}
				counter++;
			}
			file.close();
		}
		return allData;
	}

	void writeDataToMacronutrientRatioFile(std::string fileName, std::vector<MacronutrientRatio> data)
	{
		std::ofstream out(fileName, std::ios_base::app);
		if (out.is_open())
		{
			for (MacronutrientRatio macronutrientRatio : data) 
			{
				out << macronutrientRatio.id << ","
					<< macronutrientRatio.goal_id << ","
					<< macronutrientRatio.protein_ratio << "\n";
			}

			out.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file: " + fileName);
		}
	}

#pragma endregion
}
