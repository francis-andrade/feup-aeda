#include "../Headers/Date.h"
#include "../Headers/utilities.h"
#include "../Headers/exceptions.h"
#include <ctime>
using namespace std;


Date::Date(){

	struct tm timeinfo;
	time_t t = time(0);   // gets current time
	localtime_s(&timeinfo, &t);
	year = timeinfo.tm_year + 1900;
	month = timeinfo.tm_mon + 1;
	day = timeinfo.tm_mday;

	//ACHO QUE ASSIM TBM DEVE DAR
/*	struct tm *timeinfo;
	time_t t = time(0);   // gets current time

	//localtime_s(timeinfo, &t);
	timeinfo = localtime(&t);

	year = timeinfo->tm_year + 1900;
	month = timeinfo->tm_mon + 1;
	day = timeinfo->tm_mday;*/

}

//This constructor throws an exception if a date is not valid, although it ignores dates with zero parameters
Date::Date(unsigned int d,unsigned int m , unsigned int y){
	unsigned int months[13] = {0, 31,28 + (unsigned int)Isleap(y),31,30,31,30,31,31,30,31,30,31 };//array with the number of days in each month
	if ((m>12) || (d > months[m])) {
		throw InvalidDate(d, m, y);
	}
	this->day=d; this->month = m; this->year = y;
}

bool Date::operator> (const Date &D1) const{
	if (this->year > D1.year)
		return true;
	else if (this->year == D1.year)
	{
		if (this->month > D1.month)
			return true;
		else if (this->month == D1.month) {
			if (this->day > D1.day)
				return true;
			else
				return false;
		}
	}
	return false;
}

bool Date::operator>= (const Date &D1) const{
	if (this->year > D1.year)
		return true;
	else if (this->year == D1.year)
	{
		if (this->month > D1.month)
			return true;
		else if (this->month == D1.month) {
		if (this->day >= D1.day)
			return true;
		else
			return false;
		}
	}
	return false;
}

bool Date::operator<= (const Date &D1) const{
	return !(*this > D1);
}

bool Date::operator< (const Date &D1) const{
	return !(*this >= D1);
}

bool Date::operator== (const Date &D1) const{
	return ( (this->day == D1.day) && (this->month == D1.month) && (this->year == D1.year) );
}

Date Date::addDays(unsigned int n) const{
	Date temp(this->day , this->month , this->year);
	unsigned int months[13] = { 0, 31,28 + (unsigned int)Isleap(this->getYear()),31,30,31,30,31,31,30,31,30,31 };//array with the number of days in each month


	while(n >= months[temp.month]){
		n-= months[temp.month];
		temp.month++;
		if (temp.month > 12){
			temp.month = 1;
			temp.year++;
			months[2] = 28 + (unsigned int)Isleap(temp.year);
		}
	}
	temp.day += n;
	while (temp.day > months[temp.month]){
		temp.day -= months[temp.month];
		temp.month++;
		if(temp.month > 12){
			temp.month = 1;
			temp.year++;
		}
	}
	return temp;
}

Date Date::subtractDays(unsigned int n) const{
	Date temp(this->day , this->month , this->year);
	unsigned int months[13] = { 0, 31,28 + (unsigned int)Isleap(this->getYear()),31,30,31,30,31,31,30,31,30,31 };//array with the number of days in each month

	while(n > months[temp.month]){
		n-= months[temp.month];

		temp.day = 0;
		temp.month--;
		if (temp.month < 1){
			temp.month = 12;
			temp.year--;
			months[2] = 28 + (unsigned int)Isleap(temp.year);
		}
	}
	temp.day -= n;
	if( temp.day == 0){
		temp.month--;
		if(temp.month == 0){
			temp.year--;
			months[2] = (unsigned int)Isleap(temp.year);
			temp.month = 12;

		}
		temp.day = months[temp.month];
	}
	return temp;
}

unsigned int Date::diffDays(){
	Date current_date, temp_date(this->day,this->month, current_date.year),
			 end_date(this->day , this->month, ( (current_date > temp_date) ? (current_date.year +1) : current_date.year) );

	unsigned int months[13] = { 0, 31,28 + (unsigned int)Isleap(end_date.year),31,30,31,30,31,31,30,31,30,31 };
	//array with the number of days in each month
	unsigned int current_months[13] = { 0, 31,28 + (unsigned int)Isleap(current_date.year),31,30,31,30,31,31,30,31,30,31 };
	int days = 0, m = current_date.month	, y = current_date.year;

	if( current_date == end_date)
		return 0;

	while(m != end_date.month || y < end_date.year){
		days += months[m];

		if (m == 12){
			m = 1;
			y++;
			months[2] = 28 + (unsigned int)Isleap(y); //Update in case now its a leap year
		}
		else
			m++;
	}
		return days + (end_date.day - current_date.day);
}

/*
* Gives the date in the current year. For example if the object is 30/07/1997 and the year in 2016 it returns 30/07/2016
* Return value - Returns the date as described above
*/
Date Date::year_date(unsigned int year) const {
	if ((month == 2) && (day == 29) && !Isleap(year) ) {
		return Date(28, 2, year);
	}
	else {
		return Date(day, month, year);
	}
}

/* Computes the difference between two dates
 * parameter: d1 - Date to be subtracted from the object date
 * Returns the subtraction between the object date and d1
 */
vector<int> Date::operator-(const Date &d1) const{
	if(*this >= d1){
		int d,m,y;
		if(this->day>=d1.day){
			d=this->day-d1.day;
			if(this->month>=d1.month){
				m=this->month-d1.month;
				y=this->year-d1.year;
			}
			else{
				m=this->month+12-d1.month;
				y=this->year-d1.year-1;
			}
		}
		else{
			d=this->day+30-d1.day;
			if(this->month>=d1.month+1){
				m=this->month-d1.month-1;
				y=this->year-d1.year;
			}
			else{
				m=this->month+12-d1.month-1;
				y=this->year-d1.year-1;
			}
		}
		vector<int> v = { y,m,d };
		return v;
	}
	else{
		vector<int> v=d1-*this;
		v[0] = -v[0];
		v[1] = -v[1];
		v[2] = -v[2];
		return v;
	}
}
/*
parameter: ostream & out - ostream where date is going to be written
parameter: const Date & date - date
Writes the date passed as a parameter in out
*/
ostream& operator<<(ostream& out, const Date& date){
	out << date.getDay();
	out << "/";
	if (date.getMonth() < 10){
		out << 0;
	}
	out << date.getMonth();
	out << "/";
	out << date.getYear();
	return out;
}

/*
parameter: istream & in - istream from where date is going to be read
parameter: Date & date - variable where the date extracted from stream is going to be stored
Reads date from istream
*/
istream& operator>>(istream& in, Date& date){
	int d, m, y;//day, month and year of the date that is going to be read
	in >> d;
	in.ignore(1);
	in >> m;
	in.ignore(1);
	in >> y;
	Date date2(d, m, y);
	date = date2;
	return in;
}

/*
Prints the date on the screen
*/
void Date::show() const {
	cout << year;
	cout << "/";
	if (month < 10) {
		std::cout << 0 << month;
	}
	else {
		cout << month;
	}
	cout << "/";
	if (day < 10) {
		cout << 0 << day;
	}
	else {
		cout << day;
	}
}
