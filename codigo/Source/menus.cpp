#include "../Headers/menus.h"

using namespace std;

/*
 This function gets information from the clients file into the vector clients
 */
int readplayers() {
	Club *club = Club::getinstance(); //gets intance of class Club
	ifstream file_players; //players file
	string filename_players; //name of the file with the players
	bool errormessage = false; //if true it will display an error message
	do {
		if (errormessage) {
			cout << "\n\nThe path you introduced is not valid." << endl;
		}
		errormessage = true;
		cout<< "Introduce the path of the file with the players (or press l if you want to leave): ";
		cin.clear();
		getline(cin, filename_players);
		if ((filename_players.size() == 1) && (filename_players[0] == 'l')) {
			club->setleaveprogram(true);
		} else {
			file_players.open(filename_players);
		}
	} while (file_players.fail() && !club->getleaveprogram());

	if (!club->getleaveprogram()) {
		club->setfilename_players(filename_players); //sets a new clients filename
		try {
			club->readplayers(file_players); //reads players
		}
		catch (InvalidDate & d) {
			cout << "This date is not valid: ";
			d.show();
			cout << "\nThe file is corrupted"<<endl;
			cout << "Press any keys to leave: ";
			string keys;
			getline(cin, keys);
			return 1;
		}
		catch (InvalidPlayer & p) {
			p.show();
			cout << "The file is corrupted" << endl;
			cout << "Press any keys to leave: ";
			string keys;
			getline(cin, keys);
			return 1;
		}
		catch (DuplicateName &d){
			d.show();
			cout << "The file is corrupted" << endl;
			cout << "Press any key to leave: ";
			string keys;
			getline(cin,keys);
			return 1;
		}
	}
	return 0;
}

/*
This function gets information from the trainings file into the vector clients
*/
int readtrainings() {
	Club *club = Club::getinstance(); //gets intance of class Club
	ifstream file_trainings; //players file
	string filename_trainings; //name of the file with the trainings
	bool errormessage = false; //if true it will display an error message
	do {
		if (errormessage) {
			cout << "\n\nThe path you introduced is not valid." << endl;
		}
		errormessage = true;
		cout<< "Introduce the path of the file with the trainings (or press l if you want to leave): ";
		cin.clear();
		getline(cin, filename_trainings);
		if ((filename_trainings.size() == 1)
				&& (filename_trainings[0] == 'l')) {
			club->setleaveprogram(true);
		} else {
			file_trainings.open(filename_trainings);
		}
	} while (file_trainings.fail() && !club->getleaveprogram());
	if (!club->getleaveprogram()) {
		club->setfilename_trainings(filename_trainings); //sets a new clients filename
		try {
			club->readtrainings(file_trainings); //reads players
		}
		catch (InvalidDate & d) {
			cout << "This date is not valid: ";
			d.show();
			cout << "\nThe file is corrupted";
			cout << "Press any keys to leave: ";
			string keys;
			getline(cin, keys);
			return 1;
		}
	}
	return 0;
}

/*
This function gets information from the tournaments file into the vector clients
*/
int readtournaments() {
	Club *club = Club::getinstance(); //gets intance of class Club
	ifstream file_tournaments; //tournaments file
	string filename_tournaments; //name of the file with the tournaments
	bool errormessage = false; //if true it will display an error message
	do {
		if (errormessage) {
			cout << "\n\nThe path you introduced is not valid." << endl;
		}
		errormessage = true;
		cout<< "Introduce the path of the file with the tournaments (or press l if you want to leave): ";
		cin.clear();
		getline(cin, filename_tournaments);
		if ((filename_tournaments.size() == 1) && (filename_tournaments[0] == 'l')) {
			club->setleaveprogram(true);
		} else {
			file_tournaments.open(filename_tournaments);
		}
	} while (file_tournaments.fail() && !club->getleaveprogram());
	if (!club->getleaveprogram()) {
		club->setfilename_tournaments(filename_tournaments); //sets a new tournaments filename
		try {
			club->readtournaments(file_tournaments); //reads tournaments
		}
		catch (InvalidDate & d) {
			cout << "This date is not valid: ";
			d.show();
			cout << "\nThe file is corrupted";
			cout << "Press any keys to leave: ";
			string keys;
			getline(cin, keys);
			return 1;
		}
	}
	return 0;
}

/*
* This function asks the user for a date
* Returns the date typed by the user
*/
Date askfordate() {
	unsigned int year_date, month_date, day_date;//year month and day of the date
	bool repeat = true;//this boolean will be set to true when the cycles that ask the user for the elements of the dates should be repeated
	//The following loop asks the user for the year of the date
	while (repeat) {
		cout << "Date year(press c to cancel): ";
		string year;//year that's going to be typed by the user
		cin.clear();
		getline(cin, year);
		if (isInteger(year) && convint(year) >= 0) {
			year_date = convint(year);
			repeat = false;
		}
		else if (year == "c") {
			return Date(0, 0, 0);
		}
		else {
			cout << "That year is not valid" << endl;
		}
	}
	repeat = true;
	//The following loop asks the user for the month of the first date
	while (repeat) {
		cout << "Date month(press c to cancel): ";
		string month;//month that is going to be typed by the user
		cin.clear();
		getline(cin, month);
		if (isInteger(month) && convint(month) >= 1 && convint(month) <= 12) {
			month_date = convint(month);
			repeat = false;
		}
		else if (month == "c") {
			return Date(0, 0, 0);
		}
		else {
			cout << "That month is not valid" << endl;
		}
	}
	repeat = true;
	//The following loop asks the user for the day of the first date
	while (repeat) {
		cout << "Date day(press c to cancel): ";
		string day;//day that is going to be typed by the user
		cin.clear();
		getline(cin, day);
		if (isInteger(day) && convint(day) >= 1 && convint(day) <= 31) {
			day_date = convint(day);
			unsigned int months[13] = { 0, 31,28 + (unsigned int)Isleap(year_date),31,30,31,30,31,31,30,31,30,31 };//array with the number of days in each month
			if ((month_date>12) || (day_date > months[month_date])) {
				cout<< "That day is not valid" << endl;
			}
			else {
				repeat = false;
			}
		}
		else if (day == "c") {
			return Date(0, 0, 0);
		}
		else {
			cout << "That day is not valid" << endl;
		}
	}
	return Date(day_date, month_date, year_date);
}

/*
* This function prints the level that corresponds to the number level
* parameter : level - number that corresponds to the level (0->Minis, 1->Juveniles...)
*/
void printlevel(unsigned int level) {
	switch (level) {
	case 0:
		cout << "Minis" << endl;
		break;
	case 1:
		cout << "Juveniles" << endl;
		break;
	case 2:
		cout << "Juniors" << endl;
		break;
	case 3:
		cout << "Seniors" << endl;
		break;
	}
}

/*
Displays the initial menu on the sceen and asks the user to choose an option
Then, directs the user to the option he chose
*/

void initialmenu() {
	Club *club = Club::getinstance();//gets intance of class Club
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);// clears the screen
			cout << "INITIAL MENU - "<<club->getname()<<"\n" << endl;
			if (errormessage) {
				cout << "The option you introduced is not valid \n" << endl;//tells the user the option he had previously introduced is not valid
			}
			cout << "1: Minis" << endl;
			cout << "2: Juveniles" << endl;
			cout << "3: Juniors" << endl;
			cout << "4: Seniors" << endl;
			cout << "5: Register new player" << endl;
			cout << "6: Notify players with delayed ECG" << endl;
			cout << "7: Send birthday cards to old players" << endl;
			cout << "8: Leave" << endl;
			cout << "Type the option number: ";
			string option;//option to be chosen by the user
			cin.clear();
			getline(cin, option);
			switch (convint(option))
			{
			case 1:
				levelmenu(0);
				repeatmenu = false;
				break;
			case 2:
				levelmenu(1);
				repeatmenu = false;
				break;
			case 3:
				levelmenu(2);
				repeatmenu = false;
				break;
			case 4:
				levelmenu(3);
				repeatmenu = false;
				break;
			case 5:
				regnewplayermenu();
				repeatmenu = false;
				break;
			case 6:
				notifyECG();
				repeatmenu = false;
				break;
			case 7:
				birthdaycards();
				repeatmenu = false;
				break;
			case 8:
				repeatmenu = false;
				club->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
				break;
			default:
				errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
			}
		}
	} while (!club->getleaveprogram());

}


void printBirthdays(const vector<Player *> &players){
	int id = 1;

	cout << setw(4) << right <<  "ID" << " | " << setw(21) << "Name" <<   " | " << setw(10) << "In XXX days" << endl;
	for (Player * p : players){
		int n_days = p->getBirth().diffDays();
		cout << setw(3)  << right << ((id < 10) ? " 0" : "") << id << " | "
				 << setw(21) << right << p->getName() << " | "
			   << setw(3) << ((n_days < 9) ? "   00" : ( (n_days < 100) ? "   0" : "") ) << n_days << endl;
		id++;
	}
}

/*
* This function shows the menu that allows the user to send birthday gifts
*/
void birthdaycards() {
	system(CLEAR);
	string placeholder;
	bool valid = true, delivered = false;
	int option = 0 , id = 1;
	//ASK USER FOR A NUMBER
	while(1){
		cout << "Insert number of days (0 - 366), l to leave : ";
		getline(cin,placeholder);
		placeholder = removespaces(placeholder);
		if ( isInteger(placeholder)){
			option = convint(placeholder);
			if (option >= 0 && option <= 366)
				break;
		}
		if (placeholder == "l")
			return;

		system(CLEAR);
		cout << "Invalid input, please try again " << endl;
	}

	vector<Player *> temp = Club::getinstance()->nextBirthdays(option);
	if (temp.size() != 0){
		do {
			system(CLEAR);
			//PRINTING THE RESULTS
			printBirthdays(temp);
			if (!valid)
				cout << endl << "Invalid input, please try again " << endl;
			if(delivered) { cout << endl << "Present delivered successfuly!" << endl; delivered= false;}
			cout << endl << "Enter ID's of Players to give presents (b to go back) : ";
			getline(cin,placeholder);
			placeholder = removespaces(placeholder);
			if ( isInteger(placeholder))
			option = convint(placeholder);
			else if ( placeholder == "b")
				break;
			else
				valid = false;

			if (option >= 1 && option <= temp.size() ){
				temp.at(option-1)->setPresent(true);
				temp.erase( temp.begin() + option -1);
				valid = true;
				delivered = true;
			}
			else
				valid = false;

		} while(1);
	}
	else{
		cout << "No old players birthday found within " << option << " days." << endl;
		cout << endl << "Press any keys to continue";
		getline(cin,placeholder);
	}
}


/*
* This function displays the menu that allows the user to notify the players with a delayed ECG
*/
void notifyECG() {
	Club *club = Club::getinstance();//gets intance of class Club
	bool backflag = false;//When set to true this boolean stops the main cycle in this function and make the program go back
	bool notifyflag = false;//When a notification is sent with success, this boolean will be set to true
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);// clears the screen
			cout << club->getname()<<endl<<endl;
			cout << "List of players with the ECG delayed: " << endl<<endl;
			club->showQueue();
			cout << "\n";
			if (errormessage) {
				cout << "The option you introduced is not valid \n" << endl;//tells the user the option he had previously introduced is not valid
			}
			if (notifyflag) {
				cout << "The player was notified with success\n" << endl;
			}
			cout << "1: Notify 1st player with delayed ECG" << endl;
			cout << "2: Back" << endl;
			cout << "3: Leave" << endl;
			cout << "Type the option number: ";
			string option;//option to be chosen by the user
			cin.clear();
			getline(cin, option);
			switch (convint(option))
			{
			case 1:
				club->ECG_notify();
				notifyflag = true;
				errormessage=false;
				break;
			case 2:
				backflag = true;
				repeatmenu = false;
				break;
			case 3:
				repeatmenu = false;
				club->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
				break;
			default:
				errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
				notifyflag = false;
			}
		}
	} while (!backflag && !club->getleaveprogram());
}

/*
* This function displays the main menu for each level(minis, juveniles, juniors, seniors). Then directs the user to the option he chose.
* parameter: level (0-> minis, 1->juveniles...)
*
*/
void levelmenu(unsigned int level) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	bool backflag = false;//When set to true this boolean stop the main cycle in this function and make the program go back
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);// clears the screen
			printlevel(level);
			cout <<"Coach: "<<club_levels[level]->getCoach()<<"\n\n";
			if (errormessage) {
				cout << "The option you introduced is not valid \n" << endl;//tells the user the option he had previously introduced is not valid
			}
			cout << "1: Players" << endl;
			cout << "2: Trainings" << endl;
			cout << "3: Tournaments" << endl;
			cout << "4: Calendar" << endl;
			cout << "5: Schedule an Event" << endl;
			cout << "6: Change coach" << endl;
			cout << "7: Monthly prizes" << endl;
			cout << "8: Back" << endl;
			cout << "9: Leave" << endl;
			cout << "Type the option number: ";
			string option;//option to be chosen by the user
			cin.clear();
			getline(cin, option);
			switch (convint(option))
			{
			case 1:
				playersmenu(level);
				repeatmenu = false;
				break;
			case 2:
				trainingsmenu(level);
				repeatmenu = false;
				break;
			case 3:
				tournamentsmenu(level);
				repeatmenu = false;
				break;
			case 4:
				calendarmenu(level);
				repeatmenu = false;
				break;
			case 5:
				scheduleeventmenu(level);
				repeatmenu = false;
				break;
			case 6:
				changecoachmenu(level);
				repeatmenu = false;
				break;
			case 7:
				monthlyprizes(level);
				repeatmenu = false;
				break;
			case 8:
				backflag = true;
				repeatmenu = false;
				break;
			case 9:
				repeatmenu = false;
				club->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
				break;
			default:
				errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
			}
		}
	} while(!backflag && !club->getleaveprogram());
}

/*
* This function shows the list with the monthly prizes for all the players
*/
void monthlyprizes(unsigned int level) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	Date current_date;//current date
	system(CLEAR);// clears the screen
	printlevel(level);//prints level
	cout << "\nMonthly prizes - " << current_date.getMonth() << "/" << current_date.getYear()<<endl<<endl;
	unsigned int months[13] = { 0, 31,28 + (unsigned int)Isleap(current_date.getYear()),31,30,31,30,31,31,30,31,30,31 };//array with the number of days in each month
	cout << "Temporary list (final prizes will be delivered on " << months[current_date.getMonth()] << "/" << current_date.getMonth() << "/" << current_date.getYear()<<" ):"<<endl;
	BST<Player_node> tree = club_levels[level]->getPlayers_tree();//players tree
	BSTItrIn<Player_node> it(tree);//iterator to transverse the tree
	int count = 1;//order of the player in the list
	int rank=1;//rank of the player
	int points=INT_MAX;//points of the player
	cout << "  Rk |                Name |  Assiduity | Number of games won | Points" << endl;
	while (!it.isAtEnd()) {
		Player_node p = it.retrieve();
		if (p.player->getAssiduity_Curr_Month() + p.player->getGames_Won() < points) {
			rank = count;
			points = p.player->getAssiduity_Curr_Month() + p.player->getGames_Won();
		}
		cout <<setw(4)<< rank << " |" << setw(20) << p.player->getName() << " |" <<setw(11)<< p.player->getAssiduity_Curr_Month() <<" |"<< setw(20)<< p.player->getGames_Won() <<" |   "<< p.player->getAssiduity_Curr_Month()+ p.player->getGames_Won()<<endl;
		it.advance();
		count++;
	}
	cout << "\nPress any keys to leave: ";
	string keys;
	getline(cin, keys);
}


/*
* This function allows the user to change the coach name
*/
void changecoachmenu(unsigned level) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	bool cancelflag = false;//if true it is going cancel
	bool errormessage = false;//if true it's going to display an errormessage
	bool successflag = false;//if true it means that the user was able to introduce the input successfully
	string coach_name;//name of the player
	while (!cancelflag && !successflag) {
		system(CLEAR);
		if (errormessage) {
			cout << "The name you introduced is not valid" << endl;
		}
		cout << "Type the name of the new coach. It must be between 4 and 20 characters (or press c to cancel): ";
		string name;
		getline(cin, name);
		if (name == "c") {
			cancelflag = true;
		}
		else if ((name.size() >= 4) && (name.size() <= 20)) {
			successflag = true;
			club_levels[level]->setCoach(name);
		}
		else {
			errormessage = true;
		}
	}
}

/*
* displays the menu with the information of the players
* parameter: level (0-> minis, 1->juveniles...)
*
*/
void playersmenu(unsigned int level) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	bool backflag = false;//When set to true this boolean stop the main cycle in this function and make the program go back
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);// clears the screen
			club_levels[level]->showplayers();
			if (errormessage) {
				cout << "The ID you introduced is not valid " << endl;//tells the user the option he had previously introduced is not valid
			}
			cout << "\nType the ID of the Player you are interested in (or press b to go back): ";
			string id;//id to be typed by the user;
			cin.clear();
			getline(cin, id);
			if (id[0] == 'b' && id.size() == 1) {
				backflag = true;
				repeatmenu = false;
			}
			else {
				vector<Player *> vector_players = club_levels[level]->getPlayers();//gets vector of players of the chosen level
				if (convint(id) <= vector_players.size() && convint(id) >= 1) {
					individualplayermenu(level, convint(id));
					repeatmenu = false;
				}
				else {
					errormessage = true;
				}

			}
		}
	} while (!backflag && !club->getleaveprogram());
}


/*
*displays a menu with the information of an individual player
*/
void individualplayermenu(unsigned int level, unsigned int id) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	vector<Player *> vector_players = club_levels[level]->getPlayers();//gets vector of players of the chosen level
	Player * player = vector_players[id-1];//gets pointer to the chosen player
	bool backflag = false;//When set to true this boolean stop the main cycle in this function and make the program go back
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);
			cout << "Name: " << player->getName() << endl;
			cout << "Level: ";
			printlevel(level);
			cout << "Birthday: " << player->getBirth() << endl;
			cout << "Height: " << player->getHeight() << endl;
			cout << "Assiduity: " << player->getAssiduity() << endl;
			cout << "Presences in Trainings Games: " << player->getPresences_games() << endl;
			cout << "Presences in Small Tournaments: " << player->getPresences_stournaments() << endl;
			cout << "\nECG dates: " << endl;
			vector<Date> ecg_dates = player->getECG();
			for (unsigned int i = 0; i < ecg_dates.size(); i++) {
				ecg_dates[i].show();
				cout << "\n";
			}
			cout << "\n";
			if (errormessage) {
				cout << "The option you introduced is not valid \n" << endl;//tells the user the option he had previously introduced is not valid
			}
			cout << "1: Actualize Last ECG date" << endl;
			cout << "2: Actualize Height" << endl;
			cout << "3: Remove Player" << endl;
			cout << "4: Back" << endl;
			cout << "5: Leave" << endl;
			cout << "Type the option number: ";
			string option;//option to be chosen by the user
			cin.clear();
			getline(cin, option);
			switch (convint(option))
			{
			case 1:
				actualizeECG(level, id);
				repeatmenu = false;
				break;
			case 2:
				actualizeheight(level, id);
				repeatmenu = false;
				break;
			case 3:
				removeplayer(level, id);
				repeatmenu = false;
				backflag = true;
				break;
			case 4:
				backflag = true;
				repeatmenu = false;
				break;
			case 5:
				club->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
				repeatmenu = false;
				break;
			default:
				errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
			}
		}
	} while (!backflag && !club->getleaveprogram());
}

/*
Actualizes ECG date
*/
void actualizeECG(unsigned int level, unsigned int id) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	vector<Player *> vector_players = club_levels[level]->getPlayers();//gets vector of players of the chosen level
	Player * player = vector_players[id-1];//gets pointer to the chosen player
	system(CLEAR);//clears the screen
	cout << "Name: " << player->getName() << endl;
	cout << "Level: ";
	printlevel(level);
	cout << "Actualize ECG date" << endl;
	Date date = askfordate();
	if (date.getDay() != 0) {
		player->addECG(date);
		club->removePlayerQueue(player);
		club->addPlayerQueue(player);
	}
}

/*
Actualizes the height of a player
*/
void actualizeheight(unsigned int level, unsigned int id) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	vector<Player *> vector_players = club_levels[level]->getPlayers();//gets vector of players of the chosen level
	Player * player = vector_players[id-1];//gets pointer to the chosen player
	bool cancelflag = false;//if true it is going cancel
	bool errormessage = false;//if true it's going to display an errormessage
	while (!cancelflag) {
		system(CLEAR);//clears the screen
		cout << "Name: " << player->getName() << endl;
		cout << "Level: ";
		printlevel(level);
		cout << "Actualize Height" << endl;
		if (errormessage) {
			cout << "The height you introduced is not valid" << endl;
		}
		cout << "Introduce the player current height in cm(or press c to cancel): ";
		string height;//height to be typed by the user;
		cin.clear();
		getline(cin, height);
		if (height=="c") {
			cancelflag = true;
		}
		else if (convint(height) > 0) {
			player->setHeight(convint(height));
			cancelflag = true;
		}
		else {
			errormessage = true;
		}
	}
}

/*
Removes a player from the team
*/
void removeplayer(unsigned int level, unsigned int id) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	vector<Player *> vector_players = club_levels[level]->getPlayers();//gets vector of players of the chosen level
	Player * player = vector_players[id-1];//gets pointer to the chosen player
	system(CLEAR);
	cout << "Are you sure you want to remove " << player->getName() << " from the team ?" << endl;
	cout << "Press y for yes and any other key for no: ";
	string key;
	getline(cin, key);
	if (key[0] = 'y') {
		club->removePlayerQueue(player);//removes payer from the ecg queue
		club_levels[level]->removeplayer(id);
		club_levels[level]->makeTree();//constructs a new tree for this level
	}
}

/*
menu that allows the user to register a new player on the team
*/
void regnewplayermenu() {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	bool cancelflag = false;//if true it is going cancel
	bool errormessage = false;//if true it's going to display an errormessage
	bool samename = false;//if true it will display an error message saying there is already a player with the same name
	bool successflag = false;//if true it means that the user was able to introduce the input successfully
	string player_name;//name of the player
	Date player_birth, player_last_eletro;//date of birth and date of last ECG of the player
	unsigned int player_height;
	while (!cancelflag && !successflag) {
		system(CLEAR);
		if (errormessage) {
			cout << "The name you introduced is not valid" << endl;
		}
		else if (samename) {
			cout << "There is already a player on the team with the same name." << endl;
		}
		cout << "Type the name of the new player. It must be between 4 and 20 characters (or press c to cancel): ";
		string name;
		getline(cin, name);
		if (name == "c") {
			cancelflag = true;
		}
		else if ((name.size() >= 4) && (name.size() <= 20)) {
			vector<string> vector_players = club->getPlayers();
			Date temp_d;
			Player temp(removespaces(name) , temp_d , 190);
			if ((find(vector_players.begin(), vector_players.end(), removespaces(name)) == vector_players.end()) && !(club->findOldPlayer(&temp))) {
				player_name = removespaces(name);
				successflag = true;
			}
			else {
				samename = true;
			}
		}
		else {
			errormessage = true;
		}
	}


	if (!cancelflag) {
		cout << "\nIntroduce the date when the player was born" << endl;
		player_birth = askfordate();
		if (player_birth.getDay() == 0) {
			cancelflag = true;
		}
	}

	successflag = false;
	while (!cancelflag && !successflag) {
		cout << "\nIntroduce the date when the player realized is last ECG." << endl;
		cout << "Note: He must have realized at least one exam in order to be admited to the team" << endl;
		player_last_eletro = askfordate();
		Date current_date;
		if (player_last_eletro.getDay() == 0) {
			cancelflag = true;
		}
		else if (player_last_eletro > current_date) {
			cout << "That date is invalid. The date when the player realized his medical exam can't be after today." << endl;
		}
		else {
			successflag = true;
		}
	}
	errormessage = false;
	successflag = false;
	cout << "\n";
	while (!cancelflag && !successflag) {
		if (errormessage) {
			cout << "The height you introduced is not valid" << endl;
		}
		cout << "Type the height of the new player(press c to cancel): ";
		string height;
		getline(cin, height);
		if (convint(height) >= 0) {
			player_height = convint(height);
			successflag = true;
		}
		else if (height == "c") {
			cancelflag = true;
		}
		else {
			errormessage = true;
		}
	}
	if (!cancelflag) {
		Player * p = new Player(player_name, player_birth, player_height);
		p->addECG(player_last_eletro);


		if (club_levels[0]->addPlayer(p)) {
			cout << player_name << " was registered on the team."<<endl;
			cout << "He is now part of the Minis team."<<endl;
			club_levels[0]->makeTree();//constructs a new tree for this level
			club->addPlayerQueue(p);
			cout << "Press any keys to leave: ";
			string keys;
			getline(cin, keys);
		}
		else if (club_levels[1]->addPlayer(p)) {
			cout << player_name << " was registered on the team."<<endl;
			cout << "He is now part of the Juveniles team."<<endl;
			club_levels[1]->makeTree();//constructs a new tree for this level
			club->addPlayerQueue(p);
			cout << "Press any keys to leave: ";
			string keys;
			getline(cin, keys);
		}
		else if (club_levels[2]->addPlayer(p)) {
			cout << player_name << " was registered on the team."<<endl;
			cout << "He is now part of the Juniors team."<<endl;
			club_levels[2]->makeTree();//constructs a new tree for this level
			club->addPlayerQueue(p);
			cout << "Press any keys to leave: ";
			string keys;
			getline(cin, keys);
		}
		else if (club_levels[3]->addPlayer(p)) {
			cout << player_name << " was registered on the team. "<<endl;
			cout << "He is now part of the Seniors team. "<<endl;
			club_levels[3]->makeTree();//constructs a new tree for this level
			club->addPlayerQueue(p);
			cout << "Press any keys to leave: ";
			string keys;
			getline(cin, keys);
		}
		else if (Club::getinstance()->addBirthday(p)){
			cout << player_name << " was registered on the club. " << endl;
			cout << "He is now in the old players database." << endl;
			cout << "Press any keys to leave: ";
			string keys;
			getline(cin,keys);
		}
		else {
			cout << "The player couldn't be registered on the team. He is too young" << endl;
			cout << "Press any keys to leave: ";
			string keys;
			getline(cin, keys);
		}

	}
}

/*
* displays the menu with information of the trainings
*/
void trainingsmenu(unsigned int level) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	bool backflag = false;//When set to true this boolean stop the main cycle in this function and make the program go back
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);// clears the screen
			club_levels[level]->showtrainings();
			if (errormessage) {
				cout << "\nThe ID you introduced is not valid " << endl;//tells the user the option he had previously introduced is not valid
			}
			cout << "\nType the ID of the Training you are interested in (or press b to go back): ";
			string id;//id to be typed by the user;
			cin.clear();
			getline(cin, id);
			if (id[0] == 'b' && id.size() == 1) {
				backflag = true;
				repeatmenu = false;
			}
			else {
				vector<Event *> vector_trainings = club_levels[level]->getTrainings();//gets vector of trainings of the chosen level
				Date current_date;//current date
				if (convint(id) <= vector_trainings.size() && convint(id) >= 1 && vector_trainings[convint(id)-1]->getDay()<current_date) {
					individualtrainingmenu(level, convint(id));
					repeatmenu = false;
				}
				else {
					errormessage = true;
				}

			}
		}
	} while (!backflag && !club->getleaveprogram());
}


/*
* displays the menu with information of the tournaments
*/
void tournamentsmenu(unsigned int level) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	bool backflag = false;//When set to true this boolean stop the main cycle in this function and make the program go back
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);// clears the screen
			club_levels[level]->showtournaments();
			if (errormessage) {
				cout << "\nThe ID you introduced is not valid " << endl;//tells the user the option he had previously introduced is not valid
			}
			cout << "\nType the ID of the Tournament you are interested in (or press b to go back): ";
			string id;//id to be typed by the user;
			cin.clear();
			getline(cin, id);
			if (id[0] == 'b' && id.size() == 1) {
				backflag = true;
				repeatmenu = false;
			}
			else {
				vector<Event *> vector_tournaments = club_levels[level]->getTournaments();//gets vector of tournaments of the chosen level
				Date current_date;//current date
				if (convint(id) <= vector_tournaments.size() && convint(id) >= 1 && vector_tournaments[convint(id) - 1]->getDay()<current_date) {
					individualtournamentmenu(level, convint(id));
					repeatmenu = false;
				}
				else {
					errormessage = true;
				}

			}
		}
	} while (!backflag && !club->getleaveprogram());
}

/*
*displays the menu with the individual information of a certain training
*/
void individualtrainingmenu(unsigned int level, unsigned int id) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	vector<Event *> vector_trainings = club_levels[level]->getTrainings();//gets vector of trainings of the chosen level
	Event * training = vector_trainings[id - 1];//gets pointer to the chosen training
	bool backflag = false;//When set to true this boolean stop the main cycle in this function and make the program go back
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);
			cout << "Training" << endl;
			cout << "Date: " << training->getDay() << endl;
			cout << "Level: ";
			printlevel(level);
			cout << "Training Game: ";
			if (training->isGame()) {
				cout << " Yes" << endl;
			}
			else {
				cout << " No" << endl;
			}
			cout << "\nPlayers that participated in this training:" << endl;
			vector<string> vector_presences = training->getPresences();
			for (unsigned int i = 0; i < vector_presences.size(); i++) {
				cout << vector_presences[i] << endl;
			}
			if (errormessage) {
				cout << "\nThe option you introduced is not valid " << endl;//tells the user the option he had previously introduced is not valid
			}
			cout << "\n1: Edit the players that participated in the training" << endl;
			cout << "2: Back" << endl;
			cout << "3: Leave" << endl;
			cout << "Type the option number: ";
			string option;//option to be chosen by the user
			cin.clear();
			getline(cin, option);
			switch (convint(option))
			{
			case 1:
				editplayerstraining(level, training);
				repeatmenu = false;
				break;
			case 2:
				backflag = true;
				repeatmenu = false;
				break;
			case 3:
				club->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
				repeatmenu = false;
				break;
			default:
				errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
			}
		}
	} while (!backflag && !club->getleaveprogram());


}

void editplayerstraining(unsigned int level, Event * ev){
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	vector<Player *> vector_players = club_levels[level]->getPlayers();//gets vector of players of the chosen level
	vector<bool> alreadychosen(vector_players.size(), false); //each entry of this vector will be set to true if the player that is in the same position of that entry was already chosen
	bool repeatquestion = true;//if set to true it will repeat the question asking the user to select a player
	vector<string > participant_players;//vector with the players that participated in the tournament
	system(CLEAR);
	cout << "Edit Players that participated in the Training" << endl;
	club_levels[level]->showplayers();//shows players that participated in the training
	while (repeatquestion)
	{
		cout << "\nType the ID of the player a that was present in the training (or press f if you have already chosen all the players that participated in the training): ";
		string id;//product typed by the user
		cin.clear();
		getline(cin, id);
		if (id=="f") {
			repeatquestion = false;
		}
		else if (convint(id) <= 0 || (unsigned int)(convint(id))>vector_players.size()) {//checks if it was typed a valid player
			cout << "The player you selected is not valid" << endl;
		}
		else if (alreadychosen[convint(id) - 1]) {//checks if the product has already been chosen
			cout << "You have already selected that player" << endl;
		}
		else {
			alreadychosen[convint(id) - 1] = true;
			participant_players.push_back(vector_players[convint(id)-1]->getName());
		}
	}
	Date current_date;//current date
	if (ev->getDay().getMonth() == current_date.getMonth() && ev->getDay().getYear() == current_date.getYear()) {
		club_levels[level]->raiseassiduity_curr(participant_players, 1);
		club_levels[level]->raiseassiduity_curr(ev->getPresences(), -1);
	}
	if (ev->isGame()) {
		club_levels[level]->lowerpgames(ev->getPresences());
		club_levels[level]->raisepgames(participant_players);
		ev->setPresences(participant_players);
	}
	else {
		club_levels[level]->lowerassiduity(ev->getPresences());
		club_levels[level]->raiseassiduity(participant_players);
		club_levels[level]->makeTree();//constructs a new tree for this level
		ev->setPresences(participant_players);
	}


}
/*
*displays the menu with the individual information of a certain tournament
*/
void individualtournamentmenu(unsigned int level, unsigned int id) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	vector<Event *> vector_tournaments = club_levels[level]->getTournaments();//gets vector of trainings of the chosen level
	Event * tournament = vector_tournaments[id - 1];//gets pointer to the chosen training
	bool backflag = false;//When set to true this boolean stop the main cycle in this function and make the program go back
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);
			cout << "Tournament" << endl;
			cout << "Date: " << tournament->getDay() << endl;
			cout << "Level: ";
			printlevel(level);
			cout << "Rank: " << tournament->getRank()<<endl;
			cout << "Tournament Major: ";
			if (tournament->isMajor()) {
				cout << " Yes" << endl;
			}
			else {
				cout << " No" << endl;
			}
			cout << "\nTournament Games:" << endl;
			cout << "           This Team |             Adversary | Result" << endl;
			vector<pair<pair<unsigned int, unsigned int>, string >> vector_results = tournament->getResults();
			for (unsigned int i = 0; i < vector_results.size(); i++) {
				cout << setw(20) << club->getname() << " |  " << setw(20) << vector_results[i].second << " | " << vector_results[i].first.first << " - " << vector_results[i].first.second << endl;
			}
			cout << "\nPlayers that participated in this training:" << endl;
			vector<string> vector_presences = tournament->getPresences();
			for (unsigned int i = 0; i < vector_presences.size(); i++) {
				cout << vector_presences[i] << endl;
			}
			if (errormessage) {
				cout << "\nThe option you introduced is not valid " << endl;//tells the user the option he had previously introduced is not valid
			}
			if (!tournament->isMajor()) {
				cout << "\n1: Edit the players that participated in the tournament" << endl;
				cout << "2: Edit this team rank" << endl;
				cout << "3: Edit the games of this tournament" << endl;
				cout << "4: Back" << endl;
				cout << "5: Leave" << endl;
				cout << "Type the option number: ";
				string option;//option to be chosen by the user
				cin.clear();
				getline(cin, option);
				switch (convint(option))
				{
				case 1:
					editplayerstournament(level, tournament);
					repeatmenu = false;
					break;
				case 2:
					editranktournament(level, tournament);
					repeatmenu = false;
					break;
				case 3:
					editresultstournament(level, tournament);
					repeatmenu = false;
					break;
				case 4:
					backflag = true;
					repeatmenu = false;
					break;
				case 5:
					club->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
					repeatmenu = false;
					break;
				default:
					errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
				}
			}
			else {
				cout << "\n1: Edit this team rank" << endl;
				cout << "2: Edit the games of this tournament" << endl;
				cout << "3: Back" << endl;
				cout << "4: Leave" << endl;
				cout << "Type the option number: ";
				string option;//option to be chosen by the user
				cin.clear();
				getline(cin, option);
				switch (convint(option))
				{
				case 1:
					editranktournament(level, tournament);
					repeatmenu = false;
					break;
				case 2:
					editresultstournament(level, tournament);
					repeatmenu = false;
					break;
				case 3:
					backflag = true;
					repeatmenu = false;
					break;
				case 4:
					club->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
					repeatmenu = false;
					break;
				default:
					errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
				}
			}
		}
	} while (!backflag && !club->getleaveprogram());
}

/*
* Shows the user the menu that allows him to edit the players that participated in a tournament
*/
void editplayerstournament(unsigned int level, Event * ev) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	vector<Player *> vector_players = club_levels[level]->getPlayers();//gets vector of players of the chosen level
	vector<bool> alreadychosen(vector_players.size(), false); //each entry of this vector will be set to true if the player that is in the same position of that entry was already chosen
	bool repeatquestion = true;//if set to true it will repeat the question asking the user to select a player
	vector<string > participant_players;//vector with the players that participated in the tournament
	system(CLEAR);
	cout << "Edit Players that participated in the Tournament" << endl;
	club_levels[level]->showplayers();//shows players that participated in the training
	while (repeatquestion)
	{
		cout << "\nType the ID of the player a that was present in the tournament (or press f if you have already chosen all the players that participated in the training): ";
		string id;//product typed by the user
		cin.clear();
		getline(cin, id);
		if (id == "f") {
			repeatquestion = false;
		}
		else if (convint(id) <= 0 || (unsigned int)(convint(id))>vector_players.size()) {//checks if it was typed a valid player
			cout << "The player you selected is not valid" << endl;
		}
		else if (alreadychosen[convint(id) - 1]) {//checks if the product has already been chosen
			cout << "You have already selected that player" << endl;
		}
		else if (!vector_players[convint(id)-1]->checkECG(ev->getDay())) {
			cout << "That player didn't have the ECG in order in the date of the tournament" << endl;
		}
		else {
			alreadychosen[convint(id) - 1] = true;
			participant_players.push_back(vector_players[convint(id) - 1]->getName());
		}
	}

	club_levels[level]->lowerptournaments(ev->getPresences());
	club_levels[level]->raiseptournaments(participant_players);
	vector<pair<pair<unsigned int, unsigned int>, string>> results = ev->getResults();//vector with the old results of the tournament
	vector<string> players_name = ev->getPresences();//vector with the names of the players present in the tournament
	Date current_date;//current date
	if (ev->getDay().getMonth() == current_date.getMonth() && ev->getDay().getYear() == current_date.getYear()) {

		club_levels[level]->raisegames_won(players_name, -1, results);
		club_levels[level]->raisegames_won(participant_players, 1, results);
		club_levels[level]->makeTree();//constructs a new tree for this level
	}
	ev->setPresences(participant_players);

}


/*
* Asks the user for the rank of his team in the tournament
*/
void editranktournament(unsigned int level, Event * tournament) {
	Club *club = Club::getinstance();//gets intance of class Club
	bool backflag = false;//When set to true this boolean stop the main cycle in this function and make the program go back
	bool successflag = false;//if true it means that the user was able to type the input correctly
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);
			cout << "Tournament" << endl;
			cout << "Date: " << tournament->getDay() << endl;
			cout << "Level: ";
			printlevel(level);
			cout << "Tournament Major: ";
			if (tournament->isMajor()) {
				cout << " Yes" << endl;
			}
			else {
				cout << " No" << endl;
			}
			cout << "\nTournament Games:" << endl;
			cout << "   This Team| Adversary | Result" << endl;
			vector<pair<pair<unsigned int, unsigned int>, string >> vector_results = tournament->getResults();
			for (unsigned int i = 0; i < vector_results.size(); i++) {
				cout << setw(12) << club->getname() << "|  " << setw(12) << vector_results[i].second << "| " << vector_results[i].first.first << " - " << vector_results[i].first.second << endl;
			}
			cout << "\nPlayers that participated in this training:" << endl;
			vector<string> vector_presences = tournament->getPresences();
			for (unsigned int i = 0; i < vector_presences.size(); i++) {
				cout << vector_presences[i] << endl;
			}
			if (errormessage) {
				cout << "\nYou didn't introduce a valid rank" << endl;//tells the user the rank he had previously introduced is not valid
			}
			cout << "Type this team rank(or press b to go back): ";
			string rank;
			getline(cin, rank);
			if (rank == "b") {
				backflag = true;
				repeatmenu = false;
			}
			else if (convint(rank) >= 1) {
				tournament->setRank(convint(rank));
				successflag = true;
				repeatmenu = false;
			}
			else {
				errormessage = true;
			}
		}
	} while (!backflag && !successflag);
}
/*
* Shows the user the menu that allows him to edit the results a tournament
*/
void editresultstournament(unsigned int level, Event * tournament) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	bool repeatloop = true;//if set to true it will repeat the question asking the user to type the results of a game
	vector<pair<pair<unsigned int, unsigned int>,string>> results;//vector that will store the results typed by the user
	unsigned int game_counter = 1;//counts the number of games already typed by the user
	system(CLEAR);
	cout << "Edit Tournament Results" << endl;
	while (repeatloop) {
		cout << "\nGame " << game_counter << endl;
		string first_score, second_score;//variables that will store the results of the game
		string opposite_team;//name of the team that played against this club
		bool repeatquestion = true;
		while (repeatquestion && repeatloop) {
			cout << "Type the name of the opposite team (or press f if you have already finished typing the results of all the games): "<<endl;
			getline(cin, opposite_team);
			if (opposite_team == "f") {
				repeatloop = false;
			}
			else if (opposite_team.size() <= 3) {
				cout << "The name you typed is not valid. It must have at least 4 letters." << endl;
			}
			else if (opposite_team.size() > 20) {
				cout << "The name you typed is not valid. It must have at most 20 letters." << endl;
			}
			else if (opposite_team.find(';')!=string::npos) {
				cout << "The name you typed is not valid. It can't have any semicolons (;) ." << endl;
			}
			else {
				repeatquestion = false;
			}
		}
		repeatquestion = true;
		while (repeatquestion && repeatloop) {
			cout << "Type this team score (or press f if you have already finished typing the results of all the games): ";
			getline(cin, first_score);
			if (first_score == "f") {
				repeatloop = false;
			}
			else if (convint(first_score) < 0) {
				cout << "The score you typed is not valid" << endl;
			}
			else {
				repeatquestion = false;
			}
		}
		repeatquestion = true;
		while (repeatquestion && repeatloop) {
			cout << "Type the opponent team score (or press f if you have already finished typing the results of all the games): ";
			getline(cin, second_score);
			if (second_score == "f") {
				repeatloop = false;
			}
			else if (convint(second_score) < 0) {
				cout << "The score you typed is not valid" << endl;
			}
			else {
				repeatquestion = false;
				results.push_back(pair<pair<unsigned int, unsigned int>,string>(pair<unsigned int, unsigned int>(convint(first_score), convint(second_score)),opposite_team));
			}
		}
		game_counter++;
	}
	vector<pair<pair<unsigned int, unsigned int>, string>> old_results=tournament->getResults();//vector with the old results of the tournament
	vector<string> players_name = tournament->getPresences();//vector with the names of the players present in the tournament
	Date current_date;//current date
	if (tournament->getDay().getMonth() == current_date.getMonth() && tournament->getDay().getYear() == current_date.getYear()) {
		club_levels[level]->raisegames_won(players_name, -1, old_results);
		club_levels[level]->raisegames_won(players_name, 1,results);
		club_levels[level]->makeTree();//constructs a new tree for this level
	}
	tournament->setResults(results);
}


/*
* This function displays the next events menu that shows the next events on the calendar
*
*/
void calendarmenu(unsigned int level) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	bool backflag = false;//When set to true this boolean stop the main cycle in this function and make the program go back
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);// clears the screen
			club_levels[level]->showevents();
			if (errormessage) {
				cout << "The ID you introduced is not valid " << endl;//tells the user the option he had previously introduced is not valid
			}
			cout << "\nType the ID of the Event you are interested in (or press b to go back): ";
			string id;//id to be typed by the user;
			cin.clear();
			getline(cin, id);
			if (id=="b") {
				backflag = true;
				repeatmenu = false;
			}
			else {
				vector<Event *> vector_events = club_levels[level]->getFutureEvents();//gets vector of players of the chosen level
				if (convint(id) <= vector_events.size() && convint(id) >= 1) {
					individualeventmenu(level,convint(id));
					repeatmenu = false;
				}
				else {
					errormessage = true;
				}

			}
		}
	} while (!backflag && !club->getleaveprogram());

}

/*
*displays the menu with the individual information of a certain event that is still going to happen
*
*/
void individualeventmenu(unsigned int level,unsigned int id) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	vector<Event *> vector_events = club_levels[level]->getFutureEvents();//gets vector of events of the chosen level
	Event * ev = vector_events[id - 1];//gets pointer to the chosen event
	bool backflag = false;//When set to true this boolean stop the main cycle in this function and make the program go back
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);
			cout << "Event" << endl;
			cout << "Scheduled Date: " << ev->getDay() << endl;
			cout << "Level: ";
			printlevel(level);
			cout << "Type: ";
			if (ev->Istraining()) {
				if (ev->isGame()) {
					cout << "Training Game" << endl;
				}
				else {
					cout << "Normal Training" << endl;
				}
			}
			else {
				if (ev->isMajor()) {
					cout << "Major Tournament" << endl;
				}
				else {
					cout << "Small Tournament" << endl;
				}

			}
			if (!ev->Istraining() && ev->isMajor()) {
				cout << "\nPlayers called for the Tournament:" << endl;
				vector<string> vector_presences = ev->getPresences();
				for (unsigned int i = 0; i < vector_presences.size(); i++) {
					cout << vector_presences[i] << endl;
				}
			}
			if (errormessage) {
				cout << "\nThe option you introduced is not valid \n" << endl;//tells the user the option he had previously introduced is not valid
			}
			cout << "\n1: Remove event" << endl;
			cout << "2: Back" << endl;
			cout << "3: Leave" << endl;
			cout << "Type the option number: ";
			string option;//option to be chosen by the user
			cin.clear();
			getline(cin, option);
			switch (convint(option))
			{
			case 1:
				removeevent(level,id);
				repeatmenu = false;
				backflag = true;
				break;
			case 2:
				backflag = true;
				repeatmenu = false;
				break;
			case 3:
				club->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
				repeatmenu = false;
				break;
			default:
				errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
			}
		}
	} while (!backflag && !club->getleaveprogram());


}


/*
Removes a event from the list of scheduled events
*/
void removeevent(unsigned int level, unsigned int id) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club

	system(CLEAR);
	cout << "Are you sure you want to cancel this event ?" << endl;
	cout << "Press y for yes and any other key for no: ";
	string key;
	getline(cin, key);
	if (key == "y") {
		club_levels[level]->removeEvent(id);
	}
}


/*
*This functions shows the user a menu that allows to schedule a new event
*
*/
void scheduleeventmenu(unsigned int level) {
	Club *club = Club::getinstance();//gets intance of class Club
	bool backflag = false;//if true it will make the program go back
	do {
		bool errormessage = false;//If true will display an error message
		bool repeatmenu = true;//If true will keep showing the initial menu to the user and asking him to type an option
		while (repeatmenu) {
			system(CLEAR);// clears the screen
			cout << "Shedule an Event - ";
			printlevel(level);
			cout << "\n";
			if (errormessage) {
				cout << "The option you introduced is not valid \n" << endl;//tells the user the option he had previously introduced is not valid
			}
			cout << "1: Normal Training" << endl;
			cout << "2: Game Training" << endl;
			cout << "3: Small Tournament" << endl;
			cout << "4: Major Tournament" << endl;
			cout << "5: Back" << endl;
			cout << "6: Leave" << endl;
			cout << "Select the type of event you want to schedule: ";
			string option;//option to be chosen by the user
			cin.clear();
			getline(cin, option);
			switch (convint(option))
			{
			case 1:
				askeventdate(level, 0);
				repeatmenu = false;
				break;
			case 2:
				askeventdate(level,1);
				repeatmenu = false;
				break;
			case 3:
				askeventdate(level, 2);
				repeatmenu = false;
				break;
			case 4:
				askeventdate(level, 3);
				repeatmenu = false;
				break;
			case 5:
				backflag = true;
				repeatmenu = false;
				break;
			case 6:
				repeatmenu = false;
				club->setleaveprogram(true);//sets leaveprogram to true so that the program can end when it leaves this function
				break;
			default:
				errormessage = true;//sets errormessage to true to show an error message to the user when this cycle is repeated
			}
		}
	} while (!club->getleaveprogram() && !backflag);
}

/*
This menu asks the user for the date of an event
parameter: event - type of event (0-> Normal
*/
void askeventdate(unsigned int level, unsigned int ev) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	Date date_event(0, 0, 0);//date of the event
	Date current_date;//current_date
	bool successflag = false;//if date was typed successfully this variable will be set to true
	bool cancel_flag = false;//if the user intends to cancel the submission of the date it will be set to true
	cout << "Introduce the date of the event" << endl;
	while (!successflag && !cancel_flag) {
		date_event = askfordate();
		if (date_event.getDay() == 0) {
			cancel_flag = true;
		}
		else if (date_event < current_date) {
			cout << "You can not schedule an event for a date before today.\nPlease choose another date" << endl;
		}
		else {
			successflag = true;
		}
	}
	if (successflag == true) {
		switch (ev) {
		case 0:
		{Event * training0 = new Training(date_event, false);
		club_levels[level]->addEvent(training0); }
			break;
		case 1:
		{Event * training1 = new Training(date_event, true);
		club_levels[level]->addEvent(training1); }
			break;
		case 2:
		{Event * tournament2 = new Tournament(date_event, false);
		club_levels[level]->addEvent(tournament2); }
			break;
		case 3:
		{Event * tournament3 = new Tournament(date_event, true);
		makecall(level, tournament3); }
			break;
		default:
			;
		}
	}
}

/*
* This function asks the user the number of players that he wants to select for a tournament and then makes the call of those players
*
*/
void makecall(unsigned int level, Event * tournament) {
	Club *club = Club::getinstance();//gets intance of class Club
	vector<Level *> club_levels = club->getLevels();//gets pointers to levels of the club
	bool successflag = false;//if true it will make the program go back
	bool errormessage = false;//if true it will display an error message
	unsigned int size;//size of the call
	while (!successflag) {
		system(CLEAR);
		if (errormessage) {
			cout << "The number you selected is not valid" << endl;
		}
		cout << "Introduce the number of players you want to call for the tournament: ";
		string number;
		getline(cin, number);
		if (convint(number) < 0) {
			errormessage = true;
		}
		else {
			successflag = true;
			size = convint(number);
		}
	}
	vector<string> tournament_call = club_levels[level]->getCall(size);
	tournament->setPresences(tournament_call);
	if (tournament_call.size() < size) {
		cout<<"The team does not have enough players for the size of the call you selected" << endl;
	}
	cout << "The players selected by their presences in the trainings, game trainings and small tournaments were " << endl;
	cout << "by order of value: " << endl;
	for (unsigned int i = 0; i < tournament_call.size(); i++) {
		cout << tournament_call[i] << endl;
	}
	club_levels[level]->addEvent(tournament);
	cout << "\nPress any keys to go back: ";
	string keys;
	getline(cin, keys);
}
