/**
  @file Training.h
  @author Francisco Andrade
  @author João Almeida

  Contains the declaration of the class Training
*/

#ifndef TRAINING_H
#define TRAINING_H
#include "Event.h"

/**
	@class Training

	@brief Used to host information about a single Training
	@var game Boolean that if true means the Training was a game, false if it was regular Training
*/
class Training: public Event{
	bool game; // True -> jogo-treino , False -> normal training
public:
	/**
		@brief Default Constructor
	*/
	Training(){};
	/**
		@brief Destructor
	*/
	virtual ~Training() {};
	/**
		@brief Copy Constructor
		@param training Training object to be copied
	*/
	Training(const Training & training);
	/**
		@brief Copy Operator
		@param training Training object to be copied
	*/
	Training & operator=(const Training & training);
	/**
		@brief Pointer Copy Constructor
		@param ev Pointer to Training object to be copied
	*/
	Training(Event * ev);
	/**
		@brief Partial Constructor
		@param day Date of the Event
		@param game Whether it was a Training game or not
	*/
	Training(Date day, bool game) : Event(day) { this->game = game; };
	/**
		@brief Checks if the Training was a game
		@return True if it was a Training game
	*/
	virtual bool isGame() const{ return game; };
	/**
		@brief Checks if this Event is a Training
		@return True since all objects of this class are Trainings
	*/
	virtual bool Istraining() const{return true;};
	/**
		@brief Prints the Training on the screen
	*/
	virtual void show() const;
	/**
		@brief Gets the rank achieved by the Level at a Tournament
		@return 0 Since all objects of this class are Trainings not Tournaments
	*/
	virtual unsigned int getRank() const { return 0; };
	/**
		@brief Checks if Tournament was a major Tournament
		@return false Since all objects of this class are Trainings not Tournaments
	*/
	virtual bool isMajor() const { return false; };
	/**
		@brief Gets the results of the Level in the Tournament
		@return Empty vector since all objects of this class are Trainings not Tournaments
	*/
	virtual vector<pair<pair<unsigned int, unsigned int>, string >> getResults() const { return vector<pair<pair<unsigned int, unsigned int>, string >>();};//gets empty vector as this event has no parameter results
	/**
		@brief Does nothing since Trainings have no results
	*/
	virtual void setResults(vector<pair<pair<unsigned int, unsigned int>, string >> results) {};//does nothing has this event has no parameter results
	/**
		@brief Does nothing since Trainings have no rank
	*/
	virtual void setRank(unsigned int rank) {};//does nothing as this event has no parameter rank
	/**
		@brief Used to write the Training to an Output Stream
		@param out Output Stream to write the Training to
		@param training Training to be written on the Output Stream
		@return out (parameter)
	*/
	friend ostream& operator<<(ostream& out, const Training & training);//writes training in ostream out
	/**
		@brief Used to read the Training from an Input Stream
		@param in Input Stream from which to read the Training
		@param training Training to be read from the Input Stream
		@return in (parameter)
	*/
	friend istream& operator>>(istream& in, Training & training);//gets training from instream in
	/**
		@brief Writes the Training to a file using operator<<
		@param out File to write to
	*/
	virtual void writetofile(ostream & out) const {out<<*this;};//writes training data to file

};

#endif
