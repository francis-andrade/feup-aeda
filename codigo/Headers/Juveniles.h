/**
  @file Juveniles.h
  @author Francisco Andrade
  @author João Almeida

  Contains the declaration of the derived class Juniors
*/
#ifndef JUVENILES_H
#define JUVENILES_H

#include "Level.h"

/**
  @class Juveniles

  @brief Holds all the information about the Level Juveniles
  @var age_min Minimum age to be on this Level
  @var age_max Maximum age to be on this Level
  @details Most of the functions are virtual and inhereted from the base class Level
*/
class Juveniles : public Level{
    const unsigned int age_min = 9 , age_max = 13;//minimum and maximum age to be on the team
public:
  /**
    @brief Default Constructor
  */
  Juveniles(){};
  /**
    @brief Destructor
  */
  ~Juveniles(){};
  /**
    @brief Copy Constructor
    @param juveniles Object of class to be copied
  */
	Juveniles(const Juveniles & juveniles) :Level(juveniles) {};
  /**
    @brief Copy Operator
    @param juveniles Object of class to be copied
    @details Calls the base class Level::operator=
  */
  Juveniles & operator=(const Juveniles & juveniles) { Level::operator=(juveniles); };
  /**
    @brief Gets the member variable age_max
    @return age_max (member variable)
  */
  virtual unsigned int getMaxAge() {return this->age_max;}
  /**
    @brief Gets the member variable age_min
    @return age_min (member variable)
  */
  virtual unsigned int getMinAge() {return this->age_min;}
  /**
    @brief Adds a new Player to this Level
    @param player Pointer to Player to be added
    @return true if it was added successfuly, false if not
  */
  virtual bool addPlayer(Player * player);
  /**
    @brief Outputs the Players of this Level on the screen
  */
  virtual void showplayers() const;
  /**
    @brief Outputs the Trainings of this Level on the screen
  */
  virtual void showtrainings() const;
  /**
    @brief Outputs the Tournaments of this Level on the screen
  */
  virtual void showtournaments() const;
  /**
    @brief Gets names of players to be called to a Tournament
    @param size How many players to be called
    @return Vector with names of Players to be called
  */
  virtual vector<string> getCall(unsigned int size) ;//returns vector of string with the names of the players called for a tournament

};

#endif
