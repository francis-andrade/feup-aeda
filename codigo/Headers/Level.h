/**
  @file Level.h
  @author Francisco Andrade
  @author João Almeida

  Contains the declaration of the class Club and struct hashFuncs
*/

#ifndef LEVEL_H
#define LEVEL_H
#include "Player.h"
#include "Date.h"
#include "Tournament.h"
#include "Training.h"
#include "BST.h"


#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>

class Event;

/**
	@class Level

  @brief Holds all the information about the Club
  @var name The name of the Club
  @var players Vector with players of the Level
	@var event Vector with the events of the Level
	@var players_tree BST with players that will receive the monthly prizes
  @details Base class for Minis , Juniors, Juveniles and Seniors, lots of virtual methods to be inherited
*/
class Level {
	vector <Player *> players;
    vector <Event *> events;
	BST<Player_node> players_tree;
	string coach;
public:
	/**
		@brief Default constructor
		@details Initializes the BST
	*/
	Level():players_tree(Player_node()){};
	/**
    @brief Destructor
  */
	virtual ~Level();
	/**
    @brief Copy constructor
		@param level Object of Level to be copied
  */
	Level(const Level & level);
	/**
    @brief Copy Operator
		@param level Object of Level to be copied
  */
	Level & operator=(const Level & level);
	/**
		@brief Get the maximum age to be on this Level
		@details Pure Virtual, to be inherited by derived classes
	*/
	virtual unsigned int getMaxAge()  = 0;
	/**
		@brief Get the minimum age to be on this Level
		@details Pure Virtual, to be inherited by derived classes
	*/
	virtual unsigned int getMinAge()  = 0;
	/**
		@brief Gets all of the Players on this Level
		@return players (member variable)
	*/
	inline vector<Player *> getPlayers() const{return this->players;};
	/**
		@brief Gets all of the Events on this Level
		@return events (member variable)
	*/
	inline vector<Event *> getEvents() const{return this->events;};
	/**
		@brief Gets the coach of this Level
		@return coach (member variable)
	*/
	inline string getCoach() const { return this->coach; };
	/**
		@brief Gets the BST of players on this Level
		@return players_tree (member variable)
	*/
	inline BST<Player_node> getPlayers_tree() const { return this->players_tree; };
	/**
		@brief Gets all of the Trainings of this Level
		@return Vector only with Trainings
	*/
	vector<Event *> getTrainings() const;
	/**
		@brief Gets all of the Tournaments of this Level
		@return Vector only with Tournaments
	*/
	vector<Event *> getTournaments() const;
	/**
		@brief Adds a new Player to this Level
		@param player New Player to be added
		@return True if the Player was inserted successfuly, false if not
		@details The Player can not be added to the Level if his age is not within the range of admitted ages
	*/
	virtual bool addPlayer(Player * player);
	/**
		@brief Adds a new Event to this Level
		@param event New Event to be added
	*/
	void addEvent(Event * event);
	/**
		@brief Changes coach name
		@param coach Name of the coach
	*/
	void setCoach(std::string coach){this->coach=coach;};
	/**
		@brief Outputs the Players of this Level to the screen
		@details Pure Virtual, to be inherited by derived classes
	*/
	virtual void showplayers() const;
	/**
		@brief Outputs the Trainings of this Level to the screen
		@details Pure Virtual, to be inherited by derived classes
	*/
	virtual void showtrainings() const;
	/**
		@brief Outputs the Tournaments of this Level to the screen
		@details Pure Virtual, to be inherited by derived classes
	*/
	virtual void showtournaments() const;
	/**
		@brief Outputs the next events to happen
		@details Includes both Trainings and Tournaments
	*/
	virtual void showevents() const;
	/**
		@brief Removes a Player from this Level
		@param id Position in the member variable players
	*/
	void removeplayer(unsigned int id);
	/**
		@brief Removes an Event from this Level
		@param id Position in the member variable events
	*/
	void removeEvent(unsigned int id);
	/**
		@brief Gets Events that will happen in the future
		@return Vector of the Events to happen
	*/
	vector<Event*>getFutureEvents();
	/**
		@brief Raises the assiduity of the Players
		@param players Vector of players to raise the assiduity (member varible in Player)
	*/
	void raiseassiduity(vector<string> players);
	/**
		@brief Lowers the assiduity of the Players
		@param players Vector of players to lower the assiduity (member varible in Player)
	*/
	void lowerassiduity(vector<string> players);
	/**
		@brief Raises the presences in games of the Players
		@param players Vector of players to raise the pgames (member variable in Player)
	*/
	void raisepgames(vector<string> players);
	/**
		@brief Lowers the presences in games of the Players
		@param players Vector of players to lower the pgames (member varible in Player)
	*/
	void lowerpgames(vector<string> players);
	/**
		@brief Raises the presences in tournaments of the Players
		@param players Vector of players to raise the ptournaments (member variable in Player)
	*/
	void raiseptournaments(vector<string> players);
	/**
		@brief Lowers the presences in tournaments of the Players
		@param players Vector of players to lower the ptournaments (member varible in Player)
	*/
	void lowerptournaments(vector<string> players);
	/**
		@brief Raises the number of games in which this Level won that the Players participated
		@param players Players to be raised
		@param value Amount to be raised
		@param results Results achieved by the Level
		@details Computes how many games where won from the parameter results then multiplies it by value and adds to each player
	*/
	void raisegames_won(vector<string> players, int value, vector<pair<pair<unsigned int, unsigned int>, string >> results);
	/**
	 @brief Increases the value of assiduity of Players
 	 @param player Vector of names of Player to be increased
	 @param value Number of points to be increased
	*/
	void raiseassiduity_curr(vector<string> player, int value);
	/**
		@brief Makes a call for an Event
		@param size How many Players to call
		@return Vector with the players called to the Event
		@details Pure Virtual, to be implemented by derived classes
	*/
	virtual vector<string> getCall(unsigned int size)=0;
	/**
		@brief Re-computes the assiduities of all the Players in this Level
	*/
	void actualize_curr_parameters();
	/**
		@brief Constructs the member variable players_tree with the current Players
	*/
	void makeTree();
	/**
		@brief Removes a Player from the member variable players_tree
		@param pl Player to be removed from players_tree
	*/
	void remove_Tree(Player_node pl) { players_tree.remove(pl);};
};

#endif
