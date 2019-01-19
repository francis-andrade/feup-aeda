/**
	@file Event.h
	@author Francisco Andrade
	@author João Almeida

	Contains the declaration of the Event class
*/
#ifndef EVENT_H
#define EVENT_H

#include "Player.h"

#include <vector>

/**
	@class Event

	@brief Class to hold information about an event
	@var day Date of the event
	@var presences Names of the players that participated in the Event
	@details Base class of Tournament and Training
*/
class Event{
	Date day;
	vector<string> presences;
public:
	/**
		@brief Default Constructor
	*/
	Event(){};
	/**
		@brief Destructor
	*/
	virtual ~Event() {};
	/**
		@brief Copy Constructor
		@param ev Object of class Event to be copied
	*/
	Event(const Event & ev) { day = ev.day; presences = ev.presences; };
	/**
		@brief Contructor
		@param day Date of the Event
	*/
	Event(Date day): day(day){};
	/**
		@brief operator= Used to copy contents of one Event to other
		@param ev Object of Event to be copied
		@return Object of Event into which parameter ev was copied
		@details Copies all of the member variables
	*/
	Event & operator=(const Event & ev) { day = ev.day; presences = ev.presences; return *this; };
	/**
		@brief Gets the member variable presences
		@return presences (member variable)
	*/
	vector<string> getPresences() const { return presences; };
	/**
		@brief Gets the member variable day
		@return day (member variable)
	*/
	inline Date getDay() const { return this->day; };//gets day
	/**
		@brief Changes the value of member variable day
	*/
	void setDay(Date day) { this->day = day;};//sets day
	/**
		@brief Changes the value of member variable presences
	*/
	void setPresences(vector<string> presences) { this->presences = presences; };//sets new vector of presences
	/**
		@brief Adds a name of Player to member variable presences
	*/
	void addPresence(string presence) { presences.push_back(presence); };//adds the name of a player to presences

	/**
		@brief Used to check if this Event is a Trainings
		@return true if Event is Trainings, false if not
		@details Pure virtual, to be implemented by derived classes
	*/
	virtual bool Istraining() const = 0;
	/**
		@brief Used to check if this Event is a game (only possible in Training)
		@return true if Event is a game, false if not or if not a Training
		@details Pure virtual, to be implemented by derived classes
	*/
	virtual bool isGame() const = 0;
	/**
		@brief Used get rank of team in Tournament
		@return Tournament member variable rank or 0 if object is not a Tournament
		@details Pure virtual, to be implemented by derived classes
	*/
	virtual unsigned int getRank() const = 0;
	/**
		@brief Used to check if this Event is a major Tournament (only possible in Tournament)
		@return true if Event is a major Tournament, false if not or if not a Training
		@details Pure virtual, to be implemented by derived classes
	*/
	virtual bool isMajor() const = 0;
	/**
		@brief Get the results of the Level in a Tournament (only possible in Tournament)
		@return Vector with results of games and the Clubs played against, or empty if object is not Tournament
		@details Pure virtual, to be implemented by derived classes
	*/
	virtual vector<pair<pair<unsigned int, unsigned int>, string >> getResults() const = 0;
	/**
		@brief Changes the results of the Level in a Tournament (only possible in Tournament)
		@param results The results of the Level
		@details Pure virtual, to be implemented by derived classes
	*/
	virtual void setResults(vector<pair<pair<unsigned int, unsigned int>, string >> results)=0;
	/**
		@brief Changes the rank of the Level in a Tournament (only possible in Tournament)
		@param rank The rank of the Level
		@details Pure virtual, to be implemented by derived classes
	*/
	virtual void setRank(unsigned int rank)=0;
	/**
		@brief Printf the Event in the screen, output of Trainings different from Tournaments
		@details Pure virtual, to be implemented by derived classes
	*/
	virtual void show() const = 0;
	/**
		@brief Writes information about the Evento to an output stream
		@param out Output Stream to write to
		@details Used to output Event information on a text file
	*/
	virtual void writetofile(ostream & out) const = 0;//writes event information to file
	/**
		@brief Operator < compares two events
		@param ev1 Event to be used for comparison
		@return True if *this is sooner than parameter ev1
		@details The Events are compared by Date such that an Event is bigger than another if it happened later
	*/
	bool operator< (const Event & ev1) const { return day < ev1.day; };

};

#endif
