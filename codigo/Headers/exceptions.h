/**
  @file exceptions.h
  @author Francisco Andrade
  @author João Almeida

	Contains the declaration of all the exceptions used in the program
*/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include<iostream>
#include<string>
#include"Date.h"

using namespace std;

/**
	@class InvalidDate

	@brief Represents an Invalid Date
	@var day Day of the Date
	@var month Month of the Date
	@var year Year of the Date
	@details A Date is considered Invalid if the month does not exist or if it has too many days
*/
class InvalidDate {
	int day;
	int month;
	int year;
public:
	/**
		@brief Full-Constructor
		@param day Day of the Date
		@param month Month of the Date
		@param year Year of the Date
	*/
	InvalidDate(unsigned int day, unsigned int month, unsigned int year) { this->day = day; this->month = month; this->year = year; }
	/**
		@brief Prints the date on the screen
	*/
	void show() const { cout << year << "/" << month << "/" << day; };
};

/**
	@class InvalidPlayer

	@brief Represents an Invalid Players
	@var name Name of the Player
	@var birth Birthday of the Player
	@details A Players is considered invalid if it does not have the minimum age to be on the Club (4 year old)
*/
class InvalidPlayer {
	string name;
	Date birth;
public:
	/**
		@brief Full-Constructor
		@param name Name of Player
		@param birth Birthday of Player
	*/
	InvalidPlayer(string name, Date birth);
	/**
		@brief Prints the Player on the screen
	*/
	void show() const;
};

/**
	@class DuplicateName

	@brief Represents an Invalid Players
	@var name The name which is duplicate
	@details A name is duplicate if there is already a Player on the Club with the same name
*/
class DuplicateName{
	string name;
public:
	/**
		@brief Full-Constructor
		@param n Duplicate n
	*/
	DuplicateName(const string &n) : name(n) {};
	/**
		@brief Prints the name on the screen
	*/
	void show() const {cout << this->name << " already exists! " << endl; }
};

#endif
