#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <conio.h>

// This is to allow the use of ctime without constant error.
#pragma warning (disable : 4996)

using namespace std;

// Clears out console screen.
void clearScreen() {
	system("CLS");
}

void printOutMenu() {
	// Creates and displays menu.
	// Menu allows tells user to add one hour, minute, or second based on numeric input 1-3.
	// The fourth option ends the program.
	cout << std::string(26, '*') << endl;
	cout << "* 1 - Add One Hour" << std::string(7, ' ') << "*" << endl;
	cout << "* 2 - Add One Minute" << std::string(5, ' ') << "*" << endl;
	cout << "* 3 - Add One Second" << std::string(5, ' ') << "*" << endl;
	cout << "* 4 - Exit Program" << std::string(7, ' ') << "*" << endl;
	cout << std::string(26, '*') << endl;
}

void setTime(int& hour, int& minute, int& second) {
	// Estbablishes current time with ctime.
	time_t now = time(0);
	char* dt = ctime(&now);
	tm* ltm = localtime(&now);

	// Sets the function given variables the most current time.
	hour = ltm->tm_hour;
	minute = ltm->tm_min;
	second = ltm->tm_sec;
}

void printOutClocks(int hours, int minutes, int seconds) {
	// Below code outputs the clocks.
	// Outputs top row of stars.
	cout << std::string(26, '*') << std::string(5, ' ') << std::string(26, '*') << endl;

	// Outputs time denotation line.
	cout << "*" << std::string(5, ' ') << "12-Hour Clock" << std::string() << std::string(6, ' ') << "*";
	cout << std::string(5, ' ');
	cout << "*" << std::string(5, ' ') << "24-Hour Clock" << std::string() << std::string(6, ' ') << "*" << endl;

	// Outputs time in 12 hour format
	// This if-else statement is to account for times before midday as so to not get negative time.
	if (hours > 12) {
		cout << "*" << std::string(5, ' ') << std::setw(2) << std::setfill('0') << hours - 12 << ":";
	}
	else {
		// Nested if-else statement to account for midnight so that 12th hour wont show 00 at 12 am.
		if (hours == 0) {
			cout << "*" << std::string(5, ' ') << std::setw(2) << std::setfill('0') << "12" << ":";
		}
		else {
			cout << "*" << std::string(5, ' ') << std::setw(2) << std::setfill('0') << hours << ":";
		}
	}
	// Outputs minutes and seconds.
	cout << std::setw(2) << std::setfill('0') << minutes << ":";
	cout << std::setw(2) << std::setfill('0') << seconds;

	//  Below statements takes into account AM and PM for 12 hour clock.
	if (hours >= 12) {
		cout << " P M" << std::string(7, ' ') << "*";
	}
	else {
		cout << " A M" << std::string(7, ' ') << "*";
	}
	// Outputs space between two clocks.
	cout << std::string(5, ' ');

	// Outputs time in 24 hour format.
	cout << "*" << std::string(7, ' ') << std::setw(2) << std::setfill('0') << hours << ":";
	cout << std::setw(2) << std::setfill('0') << minutes  << ":";
	cout << std::setw(2) << std::setfill('0') << seconds;
	cout << std::string(9, ' ') << "*" << endl;

	// Outputs bottom row of stars.
	cout << std::string(26, '*') << std::string(5, ' ') << std::string(26, '*') << endl;
}

void addHour(int& hour) {
	// Increments hour by one.
	hour += 1;
	// Accounts for when hour reaches maximum then resets to zero.
	if (hour == 24) {
		hour = 0;
	}
}

void addMinute(int& hour, int& minute) {
	// Increment minute by one.
	minute += 1;
	// Accounts for maximum minute at 60 then resets to zero.
	if (minute == 60) {
		minute = 0;
		// Since 60 minutes is one hour also increments hour by one.
		addHour(hour);
	}
}

void addSecond(int& hour, int& minute, int& second) {
	// Increments second by one.
	second += 1;
	// Accounts for maximum seconds at 60 and resets to 0.
	if (second == 60) {
		second = 0;
		// Since 60 seconds in a minute after completing a minute also increments minute by one.
		addMinute(hour, minute);
	}
}

void getUserInput(int hours, int minutes, int seconds) {
	int userInput;

	// Gets initial user input.
	cout << "Enter a command: ";
	cin >> userInput;

	// While loop to continue asking for input until 4 is put which is termination command.
	while (userInput != 4) {
		if (userInput == 1) {
			// When input is 1 it clears screen to prepare for time change.
			clearScreen();
			// Increments hour by one since thats command 1.
			addHour(hours);
			// Then reprints clock with new time.
			printOutClocks(hours, minutes, seconds);
			// Reprints menu for user reference and asks for next command.
			printOutMenu();
			cout << "Enter a command: ";
			cin >> userInput;
		}
		else if (userInput == 2) {
			// When input is 2 clears screen to prepare for time change.
			clearScreen();
			// Increments minutes by one since that is command 2.
			addMinute(hours, minutes);
			// Then displays new time menu and awaits new command.
			printOutClocks(hours, minutes, seconds);
			printOutMenu();
			cout << "Enter a command: ";
			cin >> userInput;
		}
		else if (userInput == 3) {
			// When 3 is put in clears screen for time change.
			clearScreen();
			// Increments seconds by one since that is command 3.
			addSecond(hours, minutes, seconds);
			// Prints out new time, menu, and awaits user input.
			printOutClocks(hours, minutes, seconds); 
			printOutMenu();
			cout << "Enter a command: ";
			cin >> userInput;
		}
		else {
			// If user inputs invalid command reprints time, and menu.
			clearScreen();
			printOutClocks(hours, minutes, seconds);
			printOutMenu();
			// Informs user of invalid input and awaits new command.
			cout << "Invalid Input!" << endl;
			cout << "Enter a command: ";
			cin >> userInput;
		}
	}
}

int main() {
	// Establishes initial hour, minute, and second.
	int hour;
	int minute;
	int second;

	// Initializes time to current computer time.
	setTime(hour, minute, second);
	// Prints out current time and menu.
	printOutClocks(hour, minute, second);
	printOutMenu();
	// Begins to get user input for clock changes.
	getUserInput(hour, minute, second);

	return 0;
}