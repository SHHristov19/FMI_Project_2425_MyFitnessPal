# 💪 MyFitnessPal

**MyFitnessPal** is a console-based fitness tracking application written in C++ that saves data in `.csv` files. This project provides an efficient way to manage your fitness journey, including tracking meals, workouts, and user metrics.

---

## 📄 Table of contents

1. [Features](#features)
2. [How It Works](#how-it-works)
3. [Contacts](#contacts)
---

## 💻 Features <a name = "features"></a>

- **Console-Based UI**: Utilizes ANSI escape codes for colorful and dynamic interaction.
- **ASCII Art**: Displays stylish ASCII titles for enhanced user experience.
- **User Management**: 
  - **Sign In**: Create a user profile by providing details such as username, password, body measurements, activity level, and goals.
  - **Log In**: Access your profile to view and manage fitness data.
  - Passwords are securely hashed to protect user information.
- **Daily Overview**:
  - Displays the current date, goal, activity level, and macronutrient information (for Premium users).
  - Lists meals and workouts for the day.
  - Allows navigation to view data for previous and next days.
- **Data Persistence**:
  - Saves all user data in `.csv` files for easy storage and retrieval.
  - Each entry in the `.csv` files is identified by a unique GUID.
- **File Relationships**:
  - `users.csv`: Stores user information.
  - `meals.csv`: Stores meal data.
  - `goals.csv`: Stores user fitness goals.
  - `workouts.csv`: Stores workout data.
  - `dailySummaries.csv`: Stores daily summaries of meals, workouts, and progress.
  - Relationships between these files are established using IDs (GUIDs), allowing efficient cross-referencing of data.
- **Data Manipulation Commands**: Intuitive commands to add, update, delete, and navigate fitness data.

---

## ⚙ How It Works <a name = "how-it-works"></a>

The application runs directly in the console. Here's an overview of its functionality:

1. **Main Menu**:
   - **Log In**: Enter your username and password to access your profile.
   - **Sign In**: Create a new profile by inputting the following:
     - Username
     - Password
     - Body measurements (weight, height, etc.)
     - Activity level
     - Fitness goal (e.g., weight loss, muscle gain).
   - **Exit**: Quit the application.

2. **User Dashboard** (after login):
   - Displays the date, goal, activity level, and macronutrient breakdown (if Premium).
   - Lists all meals and workouts for the current day.

3. **Commands**:

   - Add Data:
     - `aw` or `wa`: Add a workout to the list.
     - `am` or `ma`: Add a meal to the list.
   
   - Update Data:
     - `um<number>`: Update a specific meal by providing the meal number.
     - `uw<number>`: Update a specific workout by providing the workout number.
     - `uu`: Update user details (e.g., weight, activity level).

   - Delete Data:
     - `dm<number>`: Delete a specific meal by providing the meal number.
     - `dw<number>`: Delete a specific workout by providing the workout number.
     - `delete`: Delete all data for the current day.

   - Navigation:
     - `<`: Move to the previous day.
     - `>`: Move to the next day.

   - Exit:
     - `e`: Exit the application.

---


## 🙋‍♂️ Contacts <a name = "contacts"></a>
## I'm [Stefan Hristov!](https://github.com/SHHristov19/)

- 📫 How to reach me: **SHHristov19@gmail.com**
- 👨🏻‍💻 Most of my projects are available on [Github](https://github.com/SHHristov19?tab=repositories)
- 📫 [Connect with me on LinkedIn](https://www.linkedin.com/in/shhristov19/)

<h1 align = "center">😎‍ Enjoy </h1>