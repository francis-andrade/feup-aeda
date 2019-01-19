/**
  @file Club.h
  @author Francisco Andrade
  @author João Almeida

  Contains the declaration of the class Club and struct hashFuncs
*/

#ifndef CLUB_H
#define CLUB_H

#include "utilities.h"
#include "exceptions.h"
#include "Player.h"
#include "Date.h"
#include "Minis.h"
#include "Juveniles.h"
#include "Juniors.h"
#include "Seniors.h"
#include "Event.h"
#include "Tournament.h"
#include "Training.h"

#include <algorithm>
#include <list>
#include <stdlib.h>
#include <iomanip>
#include <unordered_set>
//#include <tr1/unordered_set>

class Level;

/**
  @struct hashFuncs
  @brief Functions used in Club member variable future_birthdays Chained Hash-Table
*/
struct hashFuncs{
  /**
    @brief Computates the difference in days between the birthday date and current date
    @param p1
    Used has hash function
    @return If birthday > current date returns number of days, else returns -1
  */
  size_t operator()(const Player *p1) const{
    return p1->getBirth().diffDays();
  }
  /**
    @brief Compares two pointer to players to see if the Players they are pointing is the same (needed for hash table)
    @param p1 Pointer to Player 1
    @param p2 Pointer to Player 2
    Used as compare function for hash table used.
    We are only interested if the day and month are equal, the year may be different
    @return 1 if Players are the same , 0 if not
  */
  bool operator()(const Player *p1 ,const Player *p2) const{
    return ( (p1->getBirth().getDay() == p2->getBirth().getDay()) && (p1->getBirth().getMonth() == p2->getBirth().getMonth()) );
  }
};


//typedef tr1::unordered_multiset<Player *,hashFuncs , hashFuncs> un_mtset;
typedef unordered_multiset<Player *,hashFuncs , hashFuncs> un_mtset;


/**
  @class Club

  @brief Holds all the information about the Club
  @var name The name of the Club
  @var minis Pointer to object of class Minis, representing level Minis
  @var juveniles Pointer to object of class Juveniles, representing level Juveniles
  @var juniors Pointer to object of class Juniors, representing level Juniors
  @var seniors Pointer to object of class Seniors, representing level Seniors
  @var leaveprogram Bool used to know when to exit the program
  @var singleton_instance Pointer to an object of class Club (there shall only be one object of the class Club)
  @var filename_players Path to the text file that holds information about the players
  @var filename_trainings Path to the text file that holds information about the trainigs
  @var filename_tournaments Path to the text file that holds information about the tournaments
  @var ECG_queue Queue with the players that havent yet delivered the ECG
  @var future_birthdays Chained Hash-Table that holds information about old players of the Club (has a minimum of 367 buckets)

  @details The I/O operations on the text files are handled here as well as the information about the old players and the ECG's
*/
class Club{
	string name;
	Level *  minis;
	Level *  juveniles;
	Level *  juniors ;
	Level *  seniors;
	bool leaveprogram;
	static Club * singleton_instance;
	string filename_players;
	string filename_trainings;
	string filename_tournaments;
	priority_queue<Player_queue> ECG_queue;
  un_mtset future_birthdays = un_mtset(367);

  /**
    @brief Default constructor, private to prevent multiple object of this class
  */
	Club();

public:
  /**
    @brief Destructor
  */
	~Club();
  /**
    @brief Gets an object of class Club
    @return singleton_instance (member variable)
    @details Checks whether member variable singleton_instance already points to an object, if it does
    @details return it, if not then it initializes singleton_instance then returns it
  */
	static Club * getinstance();
  /**
    @brief Gets the name of the Club
    @return name (member variable)
  */
	string getname() const { return name;};
  /**
    @brief Gets member variable leaveprogram
    @return leaveprogram (member variable)
  */
	bool getleaveprogram() const{return leaveprogram;};
  /**
    @brief Change value of member variable setleaveprogram
  */
	void setleaveprogram(bool leaveprogram){this->leaveprogram=leaveprogram;}
  /**
    @brief Gets member variable filename_players
    @return filename_players (member variable)
  */
	string getfilename_players() const{return this->filename_players;}
  /**
    @brief Gets member variable filename_trainings
    @return filename_trainings (member variable)
  */
	string getfilename_trainings() const{return this->filename_trainings;}
  /**
    @brief Gets member variable filename_tournaments
    @return filename_tournaments (member variable)
  */
	string getfilename_tournaments() const{return this->filename_tournaments;}
  /**
    @brief Changes value of member variable filename_players
  */
	void setfilename_players(string filename_players){this->filename_players=filename_players;}
  /**
    @brief Changes value of member variable filename_trainings
  */
	void setfilename_trainings(string filename_trainings){this->filename_trainings=filename_trainings;}
  /**
    @brief Changes value of member variable filename_tournaments
  */
	void setfilename_tournaments(string filename_tournaments){this->filename_tournaments=filename_tournaments;}
  /**
    @brief Input operation to read all Players from a text file
    @param in Istream to read the players from
    @details First it reads the current players of the club, then it reads the old players of the club
  */
	void readplayers(istream &in);
  /**
    @brief Input operation to read all Trainings from a text file
    @param in Istream to read the trainings from
    @details Sistematically reads the Trainings by level
  */
	void readtrainings(istream &in);
  /**
    @brief Input operation to read all Tournaments from a text file
    @param in Istream to read the trainings from
    @details Sistematically reads the Tournaments by level
  */
	void readtournaments(istream & in);
  /**
    @brief Output operation to store all Players in a text file
    @details First it stores the current players of the club, then the old players of the club
  */
	void writeplayers();
  /**
    @brief Output operation to store all Trainings in a text file
    @details Sistematically stores the Trainings by level
  */
	void writetrainings();
  /**
    @brief Output operation to store all Tournaments in a text file
    @details Sistematically stores the Tournaments by level
  */
	void writetournaments();
  /**
    @brief Used to get a vector with all levels
    @return Vector of pointer to levels with Minis* at 0 , Juveniles* at 1 , Juniors* at 2 , Seniors* at 3
  */
	vector<Level *> getLevels() const { return vector<Level *>{minis,juveniles,juniors,seniors}; };//return a vector with minis, juveniles, juniors...
  /**
    @brief Used to get a vector with all current Players
    @return Vector with the names of all the players of the Club, including old Players if they participated in Events
  */
  vector<string> getPlayers() const;//returns a vector with thes name of all the players in the club. It also includes players that participated in certain events and were later removed
  /**
    @brief Constructs the binary Tree for each Level
    @details First it updates the information on all current Players, by resetting their assiduities and computing them again
    @details after updating it adds them to the respective BST.
  */
  void makeTree();//constructs the binary tree
  /**
    @brief Contructs the member variable ECG_queue
    @details The queue contains the current players of the club of all levels
  */
	void makeQueue();//constructs the priority queue
  /**
    @brief Adds a Player to member variable ECG_queue
  */
	void addPlayerQueue(Player * pl);//adds a player to the queue
  /**
    @brief Removes a player from the member variable ECG_queue
    @details If the player is not found the Queue simply remains the same
  */
	void removePlayerQueue(Player * pl);//adds a player to the queue
	/**
		@brief Adds the player to the hash table for future birthdays
		@param p1 Pointer to player to be added
		@details Player can only be inserted if he is older than team maximum age (defined in seniors.h)
		@details if not it cannot be added to the future birthday list

		@return true if insert successful , false if it cannot insert player
	*/
	bool addBirthday(Player *p1);
	/**
		@brief Removes the given Player from the future birthday list
		@param p1 Pointer to player to be removed
		@details Compares the players by name

		@return true if removed successfuly, false if player not found
	*/
	bool removeBirthday(Player *p1);
	/**
		@brief Gets a list of players whose birthday is within parameter days
		@param days Number of days to use

		@details Iterates all possible dates from the current day to (current_day + days) it iterates it from
		@details end day to current day so that list is ordered by the closest birthday to the farthest birthdays
		@return List of pointer to those players
	*/
	vector<Player *> nextBirthdays(int days) const;

	/**
		@brief Tries to find p1 in the future_birthdays hash table
		@param p1 Pointer to player to be found
		@return 1 if player found , 0 if player not found
	*/
	bool findOldPlayer(Player *p1);
  /**
    @brief Sends a notification to the first player in the member variable ECG_queue
  */
	void ECG_notify() { ECG_queue.pop(); };//sends a notification to the first player in the queue
  /**
    @brief Used to print the member variable ECG_queue on the screen
  */
	void showQueue();//prints the ecg queue on the screen
};


#endif
