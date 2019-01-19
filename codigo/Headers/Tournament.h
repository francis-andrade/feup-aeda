/**
  @file Tournament.h
  @author Francisco Andrade
  @author João Almeida

  Contains the declaration of the class Training
*/

#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "Date.h"
#include "Event.h"

#include <vector>

/**
	@class Tournament

	@brief Used to host information about a single Tournament
	@var major Boolean that if true means it is a Major Tournament, false if it was regular Tournament
	@var rank Rank achieved by the Level
	@var results Results of the Level in this Tournament and Clubs played against
*/
class Tournament:public Event{
	bool major;
	unsigned int rank;
  vector< pair<pair<unsigned int, unsigned int>, string >> results;

public:
	/**
		@brief Default Constructor
	*/
	Tournament(){};//default constructor
	/**
		@brief Destructor
	*/
	virtual ~Tournament(){};
	/**
		@brief Copy Constructor
		@param tournament Tournament object to be copied
	*/
	Tournament(const Tournament & tournament);
	/**
		@brief Copy Operator
		@param tournament Tournament object to be copied
	*/
	Tournament & operator=(const Tournament & tournament);//copy assignment
	/**
		@brief Pointer Copy Constructor
		@param ev Pointer to Training object to be copied
	*/
	Tournament(Event * ev);//constructor with pointer
	/**
		@brief Partial Constructor
		@param day Date of the Event
		@param major Whether it was a Major Tournament or not
	*/
	Tournament(Date day, bool major) : Event(day) { this->major = major; };//constructor with day and major parameter
	/**
		@brief Checks if this Event is a Training
		@return False since all objects of this class are Tournaments
	*/
	virtual bool Istraining() const{return false;};//returns false as the event is not a training
	/**
		@brief Used to print the Tournament on the screen
	*/
	virtual void show() const;
	/**
		@brief Checks if the Training was a game
		@return False since all objects of this class have no game parameter
	*/
	virtual bool isGame() const { return false; };//gets game
	/**
		@brief Gets the rank achieved by the Level at a Tournament
		@return rank (member variable)
	*/
	virtual unsigned int getRank() const { return rank;}//gets rank
	/**
		@brief Checks if Tournament was a major Tournament
		@return major (member variable)
	*/
	virtual bool isMajor() const { return major; };//gets major
	/**
		@brief Gets the results of the Level in the Tournament
		@return results (member variable)
	*/
	virtual vector<pair<pair<unsigned int, unsigned int>, string >> getResults() const{ return results;};//gets results
	/**
		@brief Changes the results obtained on the Tournament
		@param results Value to be changed into
	*/
	virtual void setResults(vector<pair<pair<unsigned int, unsigned int>, string >> results) { this->results = results; };//sets results
	/**
		@brief Changes the rank achieved on the Tournament
		@param rank Value to be changed into
	*/
	virtual void setRank(unsigned int rank) { this->rank = rank; };//sets rank
	/**
		@brief Used to write the Tournament to an Output Stream
		@param out Output Stream to write the Tournament to
		@param tournament Tournament to be written on the Output Stream
		@return out (parameter)
	*/
	friend ostream& operator<<(ostream& out, const Tournament & tournament);//writes tournament in ostream out
	/**
		@brief Used to read the Tournament from an Input Stream
		@param in Input Stream from which to read the Tournament
		@param tournament Tournament to be read from the Input Stream
		@return in (parameter)
	*/
	friend istream& operator>>(istream& in, Tournament & tournament);//gets tournament from instream in
	/**
		@brief Writes the Tournament to a file using operator<<
		@param out File to write to
	*/
	virtual void writetofile(ostream & out) const {out<<*this;};//writes tournament to file

};

#endif
