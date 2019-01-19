/**@class Date
  @file Player.h
  @author Francisco Andrade
  @author João Almeida

  Contains the declaration of the class Player and the Struct Player_node and Player_queue to be used in the BST and Priority Queue
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "Date.h"
#include <string>
#include <fstream>


/**
  @class Player

  @brief Holds all the information about a given Player
  @var name The name of the Player
  @var birth Birthday of the Player
  @var ecg Vector of dates when the Player had an ecg
  @var got_present Bool that represents if the Player got a present or not (only applies to old Players)
  @var height Height of the Player
  @var assiduity Assiduity of the Player in the Trainings
  @var presences_games Assoduity of the Player in Training games
  @var presences_stournaments Assiduity of the Player in small Tournaments
  @var assiduity_curr_month Assiduity of a Player in a Training on current month
  @var games_won Number of games won in which the Player participated
*/
class Player{
  string name;
  Date birth;
	vector<Date> ecg;
  bool got_present = false;
  unsigned int height;
  unsigned int assiduity;
  unsigned int presences_games;
	unsigned int presences_stournaments;
	unsigned int assiduity_curr_month;
	unsigned int games_won;
public:
  /**
    @brief Default constructor
    @details Initializes the Date with all 0
  */
	Player():birth(Date(0,0,0)){};
  /**
    @brief Partial Constructor
    @param birth_date The birthday of the Player
    @details Initializes the Date with the parameter given, the rest is either blank or 0
  */
  Player(Date birth_date) : name("") , birth(birth_date) , got_present(false) , height(0) , assiduity(0) , presences_games(0) , presences_stournaments(0) , assiduity_curr_month(0) , games_won(0) {};
  /**
    @brief Full Constructor
    @param name Name of the Player
    @param birth_date The birthday of the Player
    @param height The height of the Player
    @details All the other member variables are initialized to 0
  */
  Player(string name, Date birth_date, unsigned int height) :birth(birth_date) { this->name = name; this->height = height; this->assiduity = 0; this->presences_games = 0; this->presences_stournaments = 0; };//constructor with parameters

  /**
    @brief Gets the name of the Player
    @return name (member variable)
  */
  inline string getName() const {return this->name;}//gets name
  /**
    @brief Gets the birthday of the Player
    @return birth_date (member variable)
  */
  inline Date getBirth() const {return this->birth;}//gets birth
  /**
    @brief Gets the ECG history of the Player
    @return ecg (member variable)
  */
  inline vector<Date> getECG() const {return this->ecg;}//gets ecg
  /**
    @brief Checks if the Player got a present
    @return got_present (member variable)
  */
  inline bool getPresent() const {return this->got_present;}
  /**
    @brief Gets the height of the Player
    @return height (member variable)
  */
  inline unsigned int getHeight() const {return this->height;}//gets height
  /**
    @brief Gets the assiduity in Trainings of the Player
    @return assiduity (member variable)
  */
  inline unsigned int getAssiduity() const { return this->assiduity; };//gets assiduity
  /**
    @brief Gets the assiduity in Training games of the Player
    @return presences_games (member variable)
  */
  inline unsigned int getPresences_games() const { return this->presences_games; };//gets presences in games
  /**
    @brief Gets the assiduity in small Tournaments of the Player
    @return presences_stournaments (member variable)
  */
  inline unsigned int getPresences_stournaments() const { return this->presences_stournaments;};//gets presences in s_tournaments
  /**
    @brief Gets the assiduity this month of the Player
    @return assiduity_curr_month (member variable)
  */
  inline unsigned int getAssiduity_Curr_Month() const { return assiduity_curr_month;};//gets assiduity in the current month
  /**
    @brief Gets the number of games won in which the Player participated
    @return games_won (member variable)
  */
  inline unsigned int getGames_Won() const { return this->games_won; };//gets games won by the player in the current month
  /**
    @brief Changes the value of get_presents (member variable)
    @param b Value to change the member value into
  */
  inline void setPresent(bool b) {this->got_present = b;}
  /**
    @brief Changes the value of assiduity (member variable)
    @param assiduity Value to change the member value into
  */
  inline void setAssiduity(unsigned int assiduity) { this->assiduity = assiduity; };//sets assiduity
  /**
    @brief Changes the value of presences_games (member variable)
    @param presences_games Value to change the member value into
  */
  inline void setPresences_games(unsigned int presences_games) { this->presences_games = presences_games; };//sets presences in games
  /**
    @brief Changes the value of presences_stournaments (member variable)
    @param presences_stournaments Value to change the member value into
  */
  inline void setPresences_stournaments(unsigned int presences_stournaments) { this->presences_stournaments = presences_stournaments; };//sets presences in small tournaments
  /**
    @brief Changes the value of assiduity_curr_month (member variable)
    @param assiduity Value to change the member value into
  */
  inline void setAssiduity_Curr_Month(unsigned int assiduity) { this->assiduity_curr_month = assiduity;};//sets the assiduity of the player in the current month
  /**
    @brief Changes the value of games_won (member variable)
    @param games Value to change the member value into
  */
  inline void setGames_Won(unsigned int games) { this->games_won = games; };//sets the number of games won by the player
  /**
    @brief Changes the value of height (member variable)
    @param height Value to change the member value into
  */
  inline void setHeight(unsigned int height) { this->height = height; };//sets height
  /**
    @brief Adds a new ECG date to member varible ecg
    @param last_eletro Date to be added
  */
  void addECG(Date last_eletro);//adds ecg to the list
  /**
    @brief Prints the Player on the screen
  */
	void show() const;//prints the player on the screen
  /**
    @brief Gets the last ECG date
    @return Last ECG date
  */
	Date getLast_Eletro() const;//gets the date when the player had his last ecg
  /**
    @brief Checks if Player has ECG in order in the given Date
    @param d Date to use
  */
	bool checkECG(const Date & d) const;//checks if the player had his ecg in order on the date d
  /**
    @brief Operator< Used to compare Players
    @param p1 Player with which to compare
    @return True if this Player is smaller than p1
    @details A Player is considered smaller than another if its name is first alphabetically than the other
  */
  bool operator<(const Player & p1) const { return name < p1.name; };//compares players
  /**
    @brief Operator== Used to compare Players
    @param p1 Player with which to compare
    @return True if this Player is equal to p1
    @details A Player is considered equal to another if their names are the same
  */
  bool operator== (const Player &p1) const {return this->name == p1.name;}
  /**
    @brief Used to write the Player in an Output Stream
    @param out Output Stream to write the Player to
    @param player Player to write in the Output Stream
    @return out (parameter)
    @details Friend function
  */
  friend ostream& operator<<(ostream& out, const Player & player);//writes date in ostream out
  /**
    @brief Used to read the Player from an Input Stream
    @param in Input Stream to read the Player from
    @param player Player to be read from the Input Stream
    @return in (parameter)
    @details Friend function
  */
  friend istream& operator>>(istream& in, Player & player);//gets date from instream in
};

/**
  @struct Player_node
  @brief Struct to store the Player in a BST
  @var player Player to be stored
*/
struct Player_node {
	Player * player;
};

bool operator<(const Player_node & pl_left, const Player_node & p_right);//compares players nodes

/**
  @struct Player_queue
  @brief Struct to store the Player in a priority queue
  @var player Player to be stored
*/
struct Player_queue {
	Player * player;
};

/**
  @brief Compares two Player nodes
  @param pl_left Player to be compared
  @param pl_right Player to be compared
  @return True if pl_left if younger than pl_right
  @details If pl_left and pl_right were born in the same name it compares their names
*/
bool operator<(const Player_queue & pl_left, const Player_queue & pl_right);//compares players nodes
#endif
