/**
  @file menus.h
  @author Francisco Andrade
  @author João Almeida

  Contains the declaration of the class Club and struct hashFuncs
*/

#ifndef MENUS_H
#define MENUS_H
#include "Date.h"
#include "Event.h"
#include "Club.h"
#include "exceptions.h"
#include "utilities.h"

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <climits>

/**
  @brief Asks the user for the players text file
  @return 1 if something went wrong, 0 if all went well
*/
int readplayers();
/**
  @brief Asks the user for the trainings text file
  @return 1 if something went wrong, 0 if all went well
*/
int readtrainings();
/**
  @brief Asks the user for the tournaments text file
  @return 1 if something went wrong, 0 if all went well
*/
int readtournaments();
/**
  @brief Asks the user to input a Date
  @return Date inputted by user
*/
Date askfordate();
/**
  @brief Prints the desired level in a user friendly way
  @param level Level to print, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
*/
void printlevel(unsigned int level);
/**
  @brief Displays the initial menu
*/
void initialmenu();
/**
  @brief Prints in an user-friendly way the Name of Player and how many days to birthday
  @param p Vector of Players to print the birthdays
  @details The players are printed in order, from the soonest birthday to come to the latest
*/
void printBirthdays(const vector<Player *> &p);
/**
  @brief Displays the menu of birthday cards
  @details It asks how many days in advance does the user want to know the birthdays
*/
void birthdaycards();
/**
  @brief Displays menu that allows user to notify Players with delayed ECG
*/
void notifyECG();
/**
  @brief Displays main menu for a given Level
  @param level Level to print main manu, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
*/
void levelmenu(unsigned int level);
/**
  @brief Displays the monthly prizes for a given Level
  @param level Level to print monthly prizes, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
*/
void monthlyprizes(unsigned int level);
/**
  @brief Displays the menu to change the coach of a given Level
  @param level Level to change coach, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
*/
void changecoachmenu(unsigned level);
/**
  @brief Displays the menu of the Players of the Level in a user-friendly way
  @param level Level of Players, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @details The Players shown are alphabetically ordered
*/
void playersmenu(unsigned int level);
/**
  @brief Displays , in a user-friendly way, a menu with more detailed information about the player
  @param level Level of Player, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param id Position of the Player in the players vector
*/
void individualplayermenu(unsigned int level, unsigned int id);
/**
  @brief Menu that allows to update the ECG of a given Player
  @param level Level of Player, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param id Position of the Player in the players vector
*/
void actualizeECG(unsigned int level, unsigned int id);
/**
  @brief Menu that allows to update the height of a given Player
  @param level Level of Player, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param id Position of the Player in the players vector
*/
void actualizeheight(unsigned int level, unsigned int id);
/**
  @brief Menu to remove a given Player
  @param level Level of Player, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param id Position of the Player in the players vector
*/
void removeplayer(unsigned int level, unsigned int id);
/**
  @brief Menu that allows the user to register a new Player on the Club
*/
void regnewplayermenu();
/**
  @brief Menu that shows, in a user-friendly way, information about the Trainings of the Level
  @param level Level to be displayed, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
*/
void trainingsmenu(unsigned int level);
/**
  @brief Menu that shows, in a user-friendly way, information about the Tournaments of the Level
  @param level Level to be displayed, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
*/
void tournamentsmenu(unsigned int level);
/**
  @brief Menu that shows, in a user-friendly way, information about a specific Training of the Level
  @param level Level to be displayed, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param id Position of the Training in the events vector
*/
void individualtrainingmenu(unsigned int level, unsigned int id);
/**
  @brief Menu that asks user to select Players that participated in a given Training
  @param level Level to be changed, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param ev Event to change the participating Players
*/
void editplayerstraining(unsigned int level, Event * ev);
/**
  @brief Menu that shows, in a user-friendly way, information about a specific Tournament of the Level
  @param level Level to be displayed, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param id Position of the Tournament in the events vector
*/
void individualtournamentmenu(unsigned int level, unsigned int id);
/**
  @brief Changes the rank the Level achieved in the Tournament
  @param level Level to be changed, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param tournament Event to change the rank
*/
void editranktournament(unsigned int level, Event * tournament);
/**
  @brief Menu that asks user to select Players that participated in a given Tournament
  @param level Level to be changed, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param tournament Event to change the participating Players
*/
void editplayerstournament(unsigned int level, Event * tournament);
/**
  @brief Changes the results of the Level in the Tournament
  @param level Level to be changed, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param tournament Event to change the results
*/
void editresultstournament(unsigned int level, Event * tournament);
/**
  @brief Displays the menu of next events to take place
  @param level Level to be shown, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
*/
void calendarmenu(unsigned int level);
/**
  @brief Displays a specific Event to take place
  @param level Level to be shown, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param id Position of the Event in the events vector
*/
void individualeventmenu(unsigned int level, unsigned int id);
/**
  @brief Interface to remove a given Event
  @param level Level to be changed, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param id Position of the Event in the events vector
*/
void removeevent(unsigned int level, unsigned int id);
/**
  @brief Displays the menu that allows the user to schedule an Event
  @param level Level to be changed, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
*/
void scheduleeventmenu(unsigned int level);
/**
  @brief Asks the user for the Date of an Event
  @param level Level to be changed, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param event Position of the Event in the events vector
*/
void askeventdate(unsigned int level, unsigned int event);
/**
  @brief Asks the user the number of Players to be called for a Tournament
  @param level Level to be called, 0 for Minis, 1 Juniors , 2 Juniors , 3 Seniors
  @param tournament Tournament to which the Players are being called

*/
void makecall(unsigned int level, Event * tournament);



#endif
