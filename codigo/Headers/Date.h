/**
	@file Date.h
	@author Francisco Andrade
	@author João Almeida

	Contains the declaration of the class Date
*/

#ifndef DATE_H
#define DATE_H

#include<iostream>
#include<vector>

using namespace std;

/**
	@class Date

	@brief Class that represents a Date of the calendar
	@var day Day of the Date
	@var month Month of the Date
	@var year Year of the Date

	@details Allows operations on dates such as adding and subtracting days and comparing two Dates

*/
class Date {
	unsigned int day;
	unsigned int month;
	unsigned int year;
public:
	/**
		@brief Default Constructor
		@details Sets date to current time on the system
	*/
	Date();
	/**
		@brief Contructor with day, month and year
		@param day Day of the Date
		@param month Month of the Date
		@param year Year of the Date

		@details Checks the parameters to see if all is correct, including Leap years
	*/
	Date(unsigned int day ,unsigned int month, unsigned int year);
	/**
		@brief Gets the day of the Date
		@return day (member varible)
	*/
	inline int getDay() const {return this->day;}
	/**
		@brief Gets the month of the Date
		@return month (member varible)
	*/
	inline int getMonth() const {return this->month;}
	/**
		@brief Gets the year of the Date
		@return year (member varible)
	*/
	inline int getYear() const {return this->year;}
	/**
		@brief Operator > compares two dates
		@details A date is bigger than another if it is later
	*/
	bool operator>(const Date &d1) const;
	/**
		@brief Operator >= compares two dates
		@details A date is bigger or equal than another if it is later or the same
	*/
	bool operator>=(const Date &d1) const;
	/**
		@brief Operator < compares two dates
		@details A date is smaller than another if it is sooner
	*/
	bool operator<(const Date &d1) const;
	/**
		@brief Operator <= compares two dates
		@details A date is smaller or equal than another if it is sooner or the same
	*/
	bool operator<=(const Date &d1) const;
	/**
		@brief Operator == compares two dates
		@details A date is equal to another if the day, month and year are the same
	*/
	bool operator==(const Date &d1) const;
	/**
		@brief Sums n days to the date in the object
		@param n Number of days to sum
		@details Used only on hash table , takes into consideration leap years

		@return New object with correct date
	*/
	Date addDays(unsigned int n) const;
	/**
		@brief Subtracts n days to the date in the object
		@param n Number of days to subtract
		@details Used only on hash table , takes into consideration leap years

		@return New object with correct date
	*/
	Date subtractDays(unsigned int n) const;
	/**
		@brief Computates the difference in days between the date of the object and the current date
		@return If object date > current date returns number of days
	*/
	unsigned int diffDays();
	/**
		@brief Changes the year of the date
		@param year Year to change the date into
		@return A new date with same day and month as original but year equal to param year
	*/
	Date year_date(unsigned int year) const;
	/**
		@brief Computes the time between the two date
		@param d1 Date to use to compute the time
		@return vector with days passed at 0 , months passed at 1, years passed at 2
	*/
	vector<int> operator-(const Date &d1) const;
	/**
		@brief Prints the date on the screen
	*/
	void show() const;
};

/**
	@brief Prints the date on the desired output stream
	@param out Output stream to print the date
	@param date Date to be outputted to screen
	@return out (parameter)
*/
ostream& operator<<(ostream& out, const Date & date);//writes date in ostream out
/**
	@brief Reads the date from the desired input stream
	@param in Input stream to read the date
	@param date Date to be read from the screen
	@return in (parameter)
*/
istream& operator>>(istream& in, Date & date);//gets date from instream in


#endif
